% sum all the numbers in a list
sumAll([], 0).
sumAll([Head|Tail], Sum) :-
	sumAll(Tail, NewSum),
	Sum is NewSum + Head.

sumAllAccum(List, Sum) :-
	sumAllAccum(0, List, Sum).

sumAllAccum(Sum, [], Sum).
sumAllAccum(Accum, [Head|Tail], Sum) :-
	NewAccum is Accum + Head,
	sumAllAccum(NewAccum, Tail, Sum).

myReverse(List, Reversed) :-
	myReverse([], List, Reversed).

myReverse(List, [], List).
myReverse(Accum, [Head|Tail], Output) :-
	myReverse([Head|Accum], Tail, Output).

powerSet([], []).
powerSet([Head|Tail], [Head|Rest]) :-
	powerSet(Tail, Rest).
powerSet([_|Tail], Result) :-
	powerSet(Tail, Result).
