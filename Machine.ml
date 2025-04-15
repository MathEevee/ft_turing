open Type

let init_Machine (json : Type.json) tape = {
	tape = tape;
	head = 0;
	size = Array.length tape;
	blank = json.blank;
	current_state = json.initial;
	finals = json.finals;
	transitions = json.transitions
}

let default_transition = {
    current_state = "";
    to_state = "";
    read = '\000';
    write = '\000';
    move = RIGHT;
}

let get_direction move =
    match move with
    | LEFT -> (-1)
    | RIGHT -> 1
	| NONE -> 0

let rec is_Final_State c_state finals =
	match finals with
	| [] -> false
	| head :: tail when c_state = head -> true
	| head :: tail -> is_Final_State c_state tail

let rec get_Next_State c_state (transitions : transitions) r_letter =
	match transitions with	
	| [] -> (false, default_transition)
	| head :: tail when (head.current_state = c_state) && (head.read = r_letter) -> (true, head)
	| head :: tail -> get_Next_State c_state tail r_letter

let apply_Transition machine n_transtion =
	machine.current_state <- n_transtion.to_state;
	machine.tape.(machine.head) <- n_transtion.write;
	if (machine.head + (get_direction n_transtion.move)) >= machine.size then
		begin
			machine.tape <-  Array.append machine.tape [| machine.blank |];
			machine.size <- machine.size + 1;
			machine.head <- machine.head + 1
		end
	else if (machine.head + (get_direction n_transtion.move)) < 0 then
		begin
			machine.tape <-  Array.append [| machine.blank |] machine.tape;
			machine.size <- machine.size + 1
		end
	else
		machine.head <- machine.head + (get_direction n_transtion.move)


let rec ft_Turing m = 
	if (is_Final_State m.current_state m.finals) = true then
		Print.print_End m
	else
		begin
			let boolean, n_tran = (get_Next_State m.current_state m.transitions m.tape.(m.head)) in	
			if not boolean then
				print_endline "There is no next state, it's impossible to transition"
			else
				begin
					Print.print_Tape m n_tran;
					apply_Transition m n_tran;
					ft_Turing m
				end
		end
