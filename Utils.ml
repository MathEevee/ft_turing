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
		if (String.get src i) = c && not in_quotes then
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

