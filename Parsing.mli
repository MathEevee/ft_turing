val check_Arg : int -> string array -> bool

val open_File : string -> string

val parse_File : string -> bool * Type.json

val check_File_Format : string -> bool

val get_Index_Not_In_Quotes : int -> string -> char -> int

val loop_check_double : 'a -> 'a list -> bool

val check_lst_double : 'a list -> bool

val get_String : string -> int ref -> string

val get_List_String : string -> int ref -> string list

val check_Alphabet : Type.alphabet -> bool

val check_Blank : Type.blank -> Type.alphabet -> bool

val check_States : Type.states -> bool

val check_Initial : Type.state -> Type.states -> bool

val check_Finals : Type.states -> Type.states -> bool

(* val check_Blank : string -> Type.alphabet -> bool * Type.blank *)

(* val check_State : string list -> bool * Type.states *)

(* val check_Initial : string -> Type.states -> bool * Type.state *)

(* val check_Finals : string list -> bool * Type.finals *)

(* val check_Transitions : string list -> bool * Type.transitions *) (* ? *)

(* val check_Parameter : string list -> Type.alphabet *)

(* val create_Transtition : Type.state -> Type.letter -> Type.state -> Type.letter -> Type.move -> Type.transition *)
