open Print
open Str

let reg_file = "\\{\\s*\"name\"\\s*:\\s*\"[^\"]*\",\\s*\"alphabet\"\\s*:\\s*\\[\\s*\"[^\"]*\"(?:\\s*,\\s*\"[^\"]*\")*\\s*\\]\\s*,\\s*\"blank\"\\s*:\\s*\"[^\"]\",\\s*\"states\"\\s*:\\s*\\[\\s*\"[^\"]*\"(?:\\s*,\\s*\"[^\"]*\")*\\s*\\]\\s*,\\s*\"initial\"\\s*:\\s*\"[^\"]*\",\\s*\"final\"\\s*:\\s*\\[\\s*\"[^\"]*\"(?:\\s*,\\s*\"[^\"]*\")*\\s*\\]\\s*,\\s*\"transitions\"\\s*:\\s*\\{(\\s*\"[^\"]*\"\\s*:\\s*\\[\\s*(\\{\\s*\"read\"\\s*:\\s*\"[^\"]*\"\\s*,\\s*\"to_state\"\\s*:\\s*\"[^\"]*\"\\s*,\\s*\"write\"\\s*:\\s*\"[^\"]*\"\\s*,\\s*\"action\"\\s*:\\s*(RIGHT|LEFT)\\s*\\}\\s*,\\s*)*)*\\s*\\]\\s*\\}\\s*\\}"

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
			begin
	      		print_endline "La chaîne correspond à la regex !";
				true
			end
    	else
			begin
	     		print_endline "La chaîne ne correspond pas à la regex.";
				false
			end


let parse_File file_content =
	if (check_File_Format file_content) = false then
		false
	else
		true
	

(* val to_Json : string -> Yojson.Safe.t *)

(* val init_Json_Struct : Yojson.Safe.t -> Type.Json *)

(* val check_Alphabet : string List -> bool * Type.Alphabet *)

(* val check_Blank : string -> Type.Alphabet -> bool * Type.Blank *)

(* val check_State : string list -> bool * Type.States *)

(* val check_Initial : string -> Type.States -> bool * Type.State *)

(* val check_Finals : string list -> bool * Type.Finals *)

(* val check_Transitions : string list -> bool * Type.Transitions *) (* ? *)

(* val check_Parameter : string list -> Type.Alphabet *)

(* val create_Transtition : Type.State -> Type.Letter -> Type.State -> Type.Letter -> Type.Move -> Transtion *)
