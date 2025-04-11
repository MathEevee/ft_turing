val init_Machine : Type.json -> Type.letter array -> Type.machine

val get_direction : Type.move -> int

val is_Final_State : Type.state -> Type.state list -> bool

val get_Next_State : Type.state -> Type.transitions -> Type.letter -> bool * Type.transition

val apply_Transition : Type.machine -> Type.transition -> unit

val ft_Turing : Type.machine -> unit
