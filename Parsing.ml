open Print

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

(* val open_File : string -> string *)

(* val to_Json : string -> Yojson.Safe.t *)

(* val init_Json_Struct : Yojson.Safe.t -> Type.Json *)

(* val check_Alphabet : string -> bool * Type.Alphabet *)

(* val check_Blank : string -> Type.Alphabet -> bool * Type.Blank *)

(* val check_State : string list -> bool * Type.States *)

(* val check_Initial : string -> Type.States -> bool * Type.State *)

(* val check_Finals : string list -> bool * Type.Finals *)

(* val check_Transitions : string list -> bool * Type.Transitions *) (* ? *)

(* val check_Parameter : string list -> Type.Alphabet *)

(* val create_Transtition : Type.State -> Type.Letter -> Type.State -> Type.Letter -> Type.Move -> Transtion *)
