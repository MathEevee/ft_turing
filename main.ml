open Parsing
open Machine
open Print
open Type

let () =
	let argc = Array.length Sys.argv in
	let argv = Sys.argv in

	if not (check_Arg argc argv) then
		exit 1;

	let filecontent = (open_File argv.(1)) in
	if filecontent = "" then
		exit 1
	else
		print_string filecontent;

	let parse_bool = (parse_File filecontent) in
	if parse_bool = false then
		exit 1
	else
		print_endline "UWU It's working"

(*	let alphabet = ['1'; '.'; '-'; '='] in
	print_Alphabet alphabet;

	let states = [ "scanright"; "eraseone"; "subone"; "skip"; "HALT" ] in
	print_States states;

	let initial = "scanright" in 
	print_Initial initial;

	let finals = [ "HALT" ] in
	print_Finals finals;

	let transitions = [
	{ current_state = "scanright"; read = '.'; to_state = "scanright"; write = '.'; move = RIGHT };
	{ current_state = "scanright"; read = '1'; to_state = "scanright"; write = '1'; move = RIGHT };
	{ current_state = "scanright"; read = '-'; to_state = "scanright"; write = '-'; move = RIGHT };
	{ current_state = "scanright"; read = '='; to_state = "eraseone"; write = '.'; move = LEFT };
	{ current_state = "eraseone"; read = '1'; to_state = "subone"; write = '='; move = LEFT };
	{ current_state = "eraseone"; read = '-'; to_state = "HALT"; write = '.'; move = LEFT };
	{ current_state = "subone"; read = '1'; to_state = "subone"; write = '1'; move = LEFT };
	{ current_state = "subone"; read = '-'; to_state = "skip"; write = '-'; move = LEFT };
	{ current_state = "skip"; read = '.'; to_state = "skip"; write = '.'; move = LEFT };
	{ current_state = "skip"; read = '1'; to_state = "scanright"; write = '.'; move = RIGHT };
	]	in print_Transitions transitions;

	print_endline "";
	print_Decorator 21 "-*";

	let machine = {
		tape = [|'1'; '1'; '1'; '-'; '1'; '1'; '='|];
		head = 0;
		size = 7;
		blank = '.';
		current_state = "scanright";
		finals = [ "HALT" ];
		transitions = transitions;
	} in ft_Turing machine *)
