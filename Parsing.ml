open Utils
open Print
open Str

let ws = "[ \n\r\x0c\t]*"
let en = ws ^ "," ^ ws
let wd = "\"[^\"^\n]+\""
let one = "\"[^\"^\n]\""
let dot = ws ^ ":" ^ ws

let tl = "\\[\\(\\(" ^ ws ^ one ^ ws ^ ",\\)*" ^ ws ^ one ^ ws ^ "\\)" ^ ws ^ "\\]"
let ts = "\\[\\(\\(" ^ ws ^ wd ^ ws ^ ",\\)*" ^ ws ^ wd ^ ws ^ "\\)" ^ ws ^ "\\]"

let tr = ws ^ "{" ^ ws ^ "\"read\"" ^ dot ^ one ^ ws ^ "," ^ ws ^
		 "\"to_state\"" ^ dot ^ wd ^ ws ^ "," ^ ws ^
		 "\"write\"" ^ dot ^ one ^ ws ^ "," ^ ws ^
		 "\"action\"" ^ dot ^ "\"\\(RIGHT\\|LEFT\\)\"" ^ ws ^
		 "}" ^ ws
let trr = "\\(\\(" ^ tr ^ ",\\)*" ^ tr ^ "\\)"

let ls = ws ^ wd ^ ws ^ dot ^ ws ^ "[" ^ ws ^ trr ^ ws ^ "]" ^ ws
let lss = "\\(\\(" ^ ls ^ ",\\)*" ^ ls ^ "\\)"
 
let reg_file = "\\{" ^ ws ^ "\"name\"" ^ dot ^ wd ^ en ^ 
			"\"alphabet\"" ^ dot ^ tl ^ en ^
			"\"blank\"" ^ dot ^ "\"[^\"^\n]\"" ^ en ^
			"\"states\"" ^ dot ^ ts ^ en ^
			"\"initial\"" ^ dot ^ wd ^ en ^
			"\"finals\"" ^ dot ^ ts ^ en ^
			"\"transitions\"" ^ dot ^ "{" ^ lss ^
			"\\}" ^ ws ^
			"\\}"

let regex_tab = "\\(\"\\)?" ^ ws ^ "\\(,\\)?" ^ ws ^ "\"" ^ ws

let check_Arg argc argv =
	if argc = 2 && (argv.(1) = "--help" || argv.(1) = "-h") then
		begin
			print_Help ();
			false
		end
	else if argc <> 3 then
		print_Error "Error : Not enough or too many parameters provided"
	else if (String.length argv.(1)) = 0 then
		print_Error "Error : First argument is empty"
	else if (String.length argv.(2)) = 0 then
		print_Error "Error : Second argument is empty"
	else if not (String.ends_with ~suffix:".json" argv.(1)) then
		print_Error "Error : First argument must be a .json"
	else
		true

let check_File_Format file_content =
	let regex = Str.regexp reg_file in
	if Str.string_match regex file_content 0 then
		true
	else
		print_Error "Error : Bad file format"

let check_Alphabet alphabet =
	if check_Lst_Has_Double alphabet then
		print_Error "Error double in alphabet"
	else
		true

let check_Blank blank alphabet =
	if is_In blank alphabet then
		true
	else
		print_Error "Blank not found in alphabet"

let check_States states =
	if check_Lst_Has_Double states then
		print_Error "Error double in States"
	else
		true

let check_Initial initial states =
	if is_In initial states then
		true
	else
		print_Error "Initial state not found in states"

let check_Finals finals states =
	if check_Lst_Has_Double finals then
		print_Error "Error double in finals"
	else
		begin
			let rec check_Finals_In_States finals states =
				match finals with
				| [] -> true;
				| head :: tail -> 
					if not (is_In head states) then
						print_Error "Final state not found in states"
					else
						check_Finals_In_States tail states
			in check_Finals_In_States finals states
		end

let rec check_Transitions (transitions : Type.transitions) states alphabet =
	match transitions with
	| [] -> true
	| head :: tail ->
		if not (is_In head.current_state states) then
			print_Error "Error : current_state not found in State lists"
		else if not (is_In head.read alphabet) then
			print_Error "Error : read not found in Alphabet"
		else if not (is_In head.to_state states) then
			print_Error "Error : to_state not found in State lists"
		else if not (is_In head.write alphabet) then
			print_Error "Error : write not found in Alphabet"
		else
			check_Transitions tail states alphabet

let parse_File file_content =
	let (rec_json : Type.json) = {
			name = "";
			alphabet = [];
			blank = '\000' ;
			states = [] ;
			initial = "";
			finals = [];
			transitions = [];
	} in
	if (check_File_Format file_content) = false then
		(false, rec_json)
	else
		let i = ref 0 in
		rec_json.name <- get_String file_content i;
		rec_json.alphabet <- List.map (fun s -> s.[0]) (get_List_String file_content i);
		rec_json.blank <- (get_String file_content i).[0];
		rec_json.states <- get_List_String file_content i;
		rec_json.initial <- get_String file_content i;
		rec_json.finals <- get_List_String file_content i;
		rec_json.transitions <- get_Transitions file_content i; (*create transitions*)
		if check_Alphabet rec_json.alphabet = false then
			(false, rec_json)
		else if check_Blank rec_json.blank rec_json.alphabet = false then
			(false, rec_json)
		else if check_States rec_json.states = false then
			(false, rec_json)
		else if check_Initial rec_json.initial rec_json.states = false then
			(false, rec_json)
		else if check_Finals rec_json.finals rec_json.states = false then
			(false, rec_json)
		else if check_Transitions rec_json.transitions rec_json.states rec_json.alphabet = false then
			(false, rec_json)
		else
			(true, rec_json)

(* val check_Transitions : string list -> bool * Type.Transitions *) (* ? *)

(* val check_Parameter : string list -> Type.Alphabet *)

(* val create_Transtition : Type.State -> Type.Letter -> Type.State -> Type.Letter -> Type.Move -> Transtion *)
