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
		 "}"
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

let get_Index_Not_In_Quotes start src c =
	let rec loop_search src c i in_quotes =
		if (String.get src i) = c && not in_quotes then
			i
		else if (String.get src i) = '"' then
			loop_search src c (i + 1) (not in_quotes)
		else
			loop_search src c (i + 1) in_quotes
	in loop_search src c start false

let rec loop_check_double elem curr =
	match curr with
	| [] -> true
	| head::tail when elem = head -> false
	| head::tail -> loop_check_double elem tail

let rec check_lst_double lst =
	match lst with
	| [] -> true
	| head::tail ->
		if loop_check_double head tail = false then
			false
		else	
			check_lst_double tail

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

let open_File file_name =
	try
		let fd = open_in file_name in
		let file_content = "" in
			let rec read_line file_content =
				try
					read_line (file_content ^ (input_line fd) ^ "\n")
				with End_of_file -> close_in fd;
					if file_content = "" then
						begin
							ignore (print_Error "Error : Empty file");
							""
						end
					else
						file_content
			in read_line file_content
	with Sys_error msg ->
    	ignore (print_Error ("Error : " ^ msg));
		""

let check_File_Format file_content =
	let regex = Str.regexp reg_file in
	if Str.string_match regex file_content 0 then
		true
	else
		print_Error "Error : Bad file format"

let get_String str i =
	i := get_Index_Not_In_Quotes !i str ':';
	i := (get_Index_Not_In_Quotes !i str '"') + 1;
	let etmp = get_Index_Not_In_Quotes !i str '"' in
	let tmp = String.sub str !i (etmp - !i) in
	i := etmp + 1;
	tmp

let get_List_String str i =
	i := get_Index_Not_In_Quotes !i str ':';
	i := (get_Index_Not_In_Quotes !i str '"') + 1;
	let etmp = get_Index_Not_In_Quotes (!i - 1) str ']' in
	let regex = Str.regexp regex_tab in
	let tab_str = String.sub str !i (etmp - !i - 1) in
	let	lst =  Str.split regex tab_str in
	i := etmp + 1;
	lst

let check_Alphabet alphabet =
	if check_lst_double alphabet then
		true
	else
		print_Error "Error double in alphabet"

let check_Blank blank alphabet =
	if loop_check_double blank alphabet = false then
		true
	else
		print_Error "Blank not found in alphabet"

let check_States states =
	if check_lst_double states then
		true
	else
		print_Error "Error double in States"

let check_Initial initial states =
	if loop_check_double initial states = false then
		true
	else
		print_Error "Initial state not found in states"

let check_Finals finals states =
	if check_lst_double finals = false then
		print_Error "Error double in finals"
	else
		begin
			let rec check_Finals_In_States finals states =
				match finals with
				| [] -> true;
				| head :: tail -> 
					if loop_check_double head states = true then
						print_Error "Final state not found in states"
					else
						check_Finals_In_States tail states
			in check_Finals_In_States finals states
		end

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
		else
			(true, rec_json)

(* val check_Alphabet : string List -> bool * Type.Alphabet *)

(* val check_Blank : string -> Type.Alphabet -> bool * Type.Blank *)

(* val check_State : string list -> bool * Type.States *)

(* val check_Initial : string -> Type.States -> bool * Type.State *)

(* val check_Finals : string list -> bool * Type.Finals *)

(* val check_Transitions : string list -> bool * Type.Transitions *) (* ? *)

(* val check_Parameter : string list -> Type.Alphabet *)

(* val create_Transtition : Type.State -> Type.Letter -> Type.State -> Type.Letter -> Type.Move -> Transtion *)
