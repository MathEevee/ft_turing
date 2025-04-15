open Type

let display_len = 21

let get_direction move =
    match move with
    | LEFT -> (-1)
    | RIGHT -> 1
	| NONE -> 0

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

let print_Name name =
	print_endline ("\x1b[38;5;103mName : " ^ name ^ "\x1b[0m")

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

let print_Blank blank =
	print_string "\x1b[38;5;103mBlank : ";
	print_char blank;
	print_endline "\x1b[0m"

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

let rec print_Decorator repeat str =
	if repeat <= 0 then
		begin
			print_endline str;
			print_endline ""
		end
	else
		begin
			print_string str;
			print_Decorator (repeat - 1) str
		end

let get_Start_Position display_size head =
	if head - (display_size / 2) <= 0 then
		0
	else
		head - (display_size / 2)

let print_Colored_Char color character =
	print_string color;
	print_char character;
	print_string "\x1b[0m"

let print_Tape machine next_transition =
	print_char '[';

	let move = get_direction next_transition.move in
	let start = get_Start_Position display_len machine.head in
	let the_end = start + display_len - (display_len mod 2) in

	let rec loop_Print_Tape machine index the_end move =
		if index <> the_end then
			begin
				if index = machine.head then
					print_Colored_Char "\x1b[38;5;74m" machine.tape.(index)
				else if index = (machine.head + move) then
					begin
						if (machine.head + move) >= machine.size then
							print_Colored_Char "\x1b[38;5;140m" machine.blank
						else
							print_Colored_Char "\x1b[38;5;140m" machine.tape.(index)
					end
				else if index >= machine.size then
					print_Colored_Char "\x1b[38;5;145m" machine.blank
				else
					print_Colored_Char "\x1b[38;5;145m" machine.tape.(index);
				loop_Print_Tape machine (index + 1) the_end move
			end
		else
			()
	in loop_Print_Tape machine start the_end move; 
	print_string "] | ";
	print_Transition next_transition

let print_End machine = 
	let start = get_Start_Position display_len machine.head in
	let the_end = start + display_len - (display_len mod 2) in

	print_char '[';
	let rec loop_Print_Tape machine index the_end =
		if index <> the_end then
			begin
				if index = machine.head then
					print_Colored_Char "\x1b[38;5;74m" machine.tape.(index)
				else if index >= machine.size then
					print_Colored_Char "\x1b[38;5;145m" machine.blank
				else
					print_Colored_Char "\x1b[38;5;145m" machine.tape.(index);
				loop_Print_Tape machine (index + 1) the_end
			end
		else
			()
	in loop_Print_Tape machine start the_end; 
	print_string "] | ";
	print_string "\x1b[38;5;203m";
	print_string machine.current_state;
	print_endline "\x1b[0m";
