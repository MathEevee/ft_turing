open Type

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

let print_Alphabet alphabet =
	print_string "\x1b[38;5;103mAlphabet : [ ";
	let rec print_Letter alphabet =
		match alphabet with
		| [] -> print_endline "]\x1b[0m"
		| head :: [] -> print_char head;
						print_endline " ]\x1b[0m"
		| head :: tail -> print_char head;
							print_string ", ";
							print_Letter tail
	in print_Letter alphabet

let print_States states =
	print_string "\x1b[38;5;103mStates : [ ";
	let rec print_State states =
		match states with
		| [] -> print_endline "]\x1b[0m"
		| head :: [] -> print_endline (head ^ " ]\x1b[0m")
		| head :: tail -> print_string (head ^ ", ");
							print_State tail
	in print_State states

let print_Initial initial =
	print_endline ("\x1b[38;5;103mInitial : " ^ initial ^ "\x1b[0m")

let print_Finals finals =
	print_string "\x1b[38;5;103mFinals : [ ";
	let rec print_Final finals =
		match finals with
		| [] -> print_endline "]\x1b[0m"
		| head :: [] -> print_endline (head ^ " ]\x1b[0m")
		| head :: tail -> print_string (head ^ ", ");
							print_Final tail
	in print_Final finals

let print_Transition (transition : transition) =
	print_string "\x1b[38;5;74m";
	print_string transition.current_state;
	print_string ", ";
	print_char transition.read;
	print_string "\x1b[0m\x1b[38;5;216m -> \x1b[38;5;140m";
	print_string transition.to_state;
	print_string ", ";
	print_char transition.write;
	print_string "\x1b[0m | \x1b[38;5;109m";
	if transition.move = RIGHT then
		print_endline "RIGHT\x1b[0m"
	else
		print_endline "LEFT\x1b[0m"

let print_Transitions transitions =
	print_endline "\x1b[38;5;103mTransitions :\x1b[0m";
	let rec print_Transitions_List transitions =
		match transitions with
		| [] -> ()
		| head :: tail -> print_Transition head;
							print_Transitions_List tail
	in print_Transitions_List transitions


let get_start_position display_size head =
	if head - (display_size / 2) <= 0 then
		0
	else
		head - (display_size / 2)

let print_Tape machine next_transition =
	print_char '[';
	let rec loop_print_Tape machine move start size_end =
		if start <> size_end then
			begin
				if start = machine.head then
					print_string ("\x1b[38;5;74m" ^ (String.make 1 machine.tape.(start)) ^ "\x1b[0m")
				else if start = machine.head + move then
					print_string ("\x1b[38;5;140m" ^ (String.make 1 machine.tape.(start)) ^ "\x1b[0m")
				else
					print_string (String.make 1 machine.tape.(start));
				loop_print_Tape machine move (start + 1) size_end
			end
		else
			()
	in loop_print_Tape machine (Machine.get_direction next_transition.move) (get_start_position 21 machine.head) ((get_start_position 21 machine.head) + 21);
	print_char ']'
