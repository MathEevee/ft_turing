val print_Help : unit -> unit

val print_Error : string -> bool

val print_Alphabet : Type.alphabet -> unit

val print_States : Type.states -> unit

val print_Initial : Type.state -> unit

val print_Finals : Type.finals -> unit

val print_Transitions : Type.transitions -> unit

val print_Transition : Type.transition -> unit

val print_Decorator : int -> string -> unit

val get_Start_Position : int -> int -> int

val print_Colored_Char : string -> Type.letter -> unit

val print_Tape : Type.machine -> Type.transition -> unit
