val check_Arg : int -> string array -> bool

val transform_Arg : string -> Type.letter array

val check_File_Format : string -> bool

val check_Alphabet : Type.alphabet -> bool

val check_Blank : Type.blank -> Type.alphabet -> bool

val check_States : Type.states -> bool

val check_Initial : Type.state -> Type.states -> bool

val check_Finals : Type.states -> Type.states -> bool

val check_Transitions : Type.transitions -> Type.states -> Type.alphabet -> Type.states -> bool -> bool

val parse_File : string -> bool * Type.json
