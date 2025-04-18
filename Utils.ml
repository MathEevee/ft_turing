open Print
open Str

let ws = "[ \n\r\x0c\t]*"
let regex_tab = "\\(\"\\)?" ^ ws ^ "\\(,\\)?" ^ ws ^ "\"" ^ ws

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

let get_Index_Not_In_Quotes start src c =
	let rec loop_search src c i in_quotes =
        if i >= (String.length src) then
            (-1)
		else if (String.get src i) = c && not in_quotes then
			i
		else if (String.get src i) = '"' then
			loop_search src c (i + 1) (not in_quotes)
		else
			loop_search src c (i + 1) in_quotes
	in loop_search src c start false

let rec is_In elem curr =
	match curr with
	| [] -> false
	| head::tail when elem = head -> true
	| head::tail -> is_In elem tail

let rec check_Lst_Has_Double lst =
	match lst with
	| [] -> false
	| head::tail ->
		if is_In head tail then
			true
		else
			check_Lst_Has_Double tail

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

let get_Str_transition str i =
    i := get_Index_Not_In_Quotes !i str '"';
    if !i = (-1) then
        ""
    else
        begin
            i := (get_Index_Not_In_Quotes !i str '"') + 1;
            let etmp = get_Index_Not_In_Quotes !i str '"' in
            let tmp = String.sub str !i (etmp - !i) in
            i := etmp + 1;
            tmp
        end

let get_Move str i =
	let tmp = get_String str i in
	if tmp = "RIGHT" then
		Type.RIGHT
    else if tmp = "LEFT" then
		Type.LEFT
	else
		Type.NONE

let create_Transition name str i =
	let tmp = get_Index_Not_In_Quotes !i str '{' in
	if (tmp >= (get_Index_Not_In_Quotes !i str ']' ) || tmp = -1) then
		begin
			i := get_Index_Not_In_Quotes !i str '}';
			let (transition_record : Type.transition) = {
				current_state = "";
				read = '\000';
				to_state = "";
				write = '\000';
				move = LEFT
			} in
			transition_record
		end
	else
		begin
			i := tmp;
			let read = ((get_String str i).[0]) in
			let to_state = (get_String str i) in
			let write = (get_String str i).[0] in
			let move = get_Move str i in
			let (transition_record : Type.transition) = {
				current_state = name;
				read = read;
				to_state = to_state;
				write = write;
				move = move
			} in transition_record
		end

let rec loop_Transition str i lst name =
    let tran = create_Transition name str i in
    if tran.read = '\000' then
        lst
    else
        loop_Transition str i (lst @ [tran]) name

let get_Transitions str i =
    i := get_Index_Not_In_Quotes !i str '{';
    let rec loop_Transitions str i lst =
        let transition_name = get_Str_transition str i in
        if transition_name = "" then
            lst
        else
            loop_Transitions str i (loop_Transition str i lst transition_name)
    in loop_Transitions str i []
