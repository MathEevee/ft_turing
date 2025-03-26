let print_Help () =
	print_endline "usage: ft_turing [-h] jsonfile input";
	print_endline "positional arguments:";
	print_endline "\tjsonfile\tjson description of the machine";
	print_endline "\tinput\t\tinput of the machine";
	print_endline "optional arguments:";
	print_endline "\t-h, --help\tshow this help message and exit"

let print_Error error_message =
	print_endline error_message;
	false
