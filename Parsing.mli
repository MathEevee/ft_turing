val check_Arg : int -> string array -> bool

val check_File_Format : string -> bool

val check_Alphabet : Type.alphabet -> bool

val check_Blank : Type.blank -> Type.alphabet -> bool

val check_States : Type.states -> bool

val check_Initial : Type.state -> Type.states -> bool

val check_Finals : Type.states -> Type.states -> bool

val parse_File : string -> bool * Type.json

(* val check_Transitions : string list -> bool * Type.transitions *) (* ? *)

(* val check_Parameter : string list -> Type.alphabet *)

(* val create_Transtition : Type.state -> Type.letter -> Type.state -> Type.letter -> Type.move -> Type.transition *)
