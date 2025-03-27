open Type

let get_direction move =
    match move with
    | LEFT -> (-1)
    | RIGHT -> 1
