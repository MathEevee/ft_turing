open Parsing
open Utils
open Machine
open Print
open Type

let () =
	let argc = Array.length Sys.argv in
	let argv = Sys.argv in

	if not (check_Arg argc argv) then
		exit 1;

	let filecontent = open_File argv.(1) in
	if filecontent = "" then
		exit 1;

	let (parse_bool, rec_json) = parse_File filecontent in
	if parse_bool = false then
		exit 1
	else if not (check_Arg_Alphabet argv.(2) rec_json.alphabet rec_json.blank) then
		exit 1
	else
		begin
			print_Name rec_json.name;
			print_Alphabet rec_json.alphabet;
			print_Blank rec_json.blank;
			print_States rec_json.states;
			print_Initial rec_json.initial;
			print_Finals rec_json.finals;
			print_Transitions rec_json.transitions;
			print_Decorator 50 "*";
			let machine = init_Machine rec_json (transform_Arg argv.(2))
			in
			ft_Turing machine
		end
