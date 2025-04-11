val open_File : string -> string

val get_Index_Not_In_Quotes : int -> string -> char -> int

val is_In : 'a -> 'a list -> bool

val check_Lst_Has_Double : 'a list -> bool

val get_String : string -> int ref -> string

val get_List_String : string -> int ref -> string list

val get_Str_transition : string -> int ref -> string

val get_Move : string -> int ref -> Type.move

val create_Transition : string -> string -> int ref -> Type.transition

val loop_Transition : string -> int ref -> Type.transitions -> Type.state -> Type.transitions

val get_Transitions : string -> int ref -> Type.transitions
