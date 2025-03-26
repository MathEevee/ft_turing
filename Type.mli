type letter = char

type alphabet = letter list

type blank = letter

type state = string

type states = state list

type finals = state list

type move = LEFT | RIGHT

type transition = {
	current_state : state;
	read : letter;	
	to_state : state;
	write : letter;
	move : move
}

type transitions = ( state * transition list ) list

type json = {
	mutable name : string;
	mutable alphabet : alphabet;
	mutable blank : letter;
	mutable states : state list;
	mutable initial : state;
	mutable finals : state list;
	mutable transitions : transitions;
}

type machine = {
	mutable tape : letter array;
	mutable head : int;
	blank : blank;
	mutable current_state : state;
	transtions : transitions;
}
