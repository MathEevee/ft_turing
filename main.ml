open Parsing

let () =
	let argc = Array.length Sys.argv in
	let argv = Sys.argv in

	if not (check_Arg argc argv) then
		exit 1;
	print_endline "NICE"
