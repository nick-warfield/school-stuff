% comment

evensBetween(N, End, Even) :-
	N =< End,
	Next is N + 1,
	evensBetween(Next, End, Even);
	0 is mod(N, 2),
	Even = N.

isPrime(X) :-
	Accum is X - 1,
	isPrime(Accum, X).

isPrime(1, _).
isPrime(Accum, X) :-
	Accum > 0,
	\+ 0 is mod(X, Accum),
	Next is Accum - 1,
	isPrime(Next, X).


myAppend([], L, L).
myAppend([H|T], L, [H|R]) :-
	myAppend(T, L, R).


interp3(true, _) :- !.
interp3( (A, B), Stack) :-
	!,
	interp3(A, Stack),
	interp3(B, Stack).
interp3(Call, Stack) :-
	format('Call (~w): ~w~n', [Stack, Call]),
	clause(Call, Body),
	Next is Stack + 1,
	interp3(Body, Next),
	format('Exit (~w): ~w~n', [Stack, Call]).

interp3(Call) :-
	interp3(Call, 0).

gen(literal(0)).
gen(literal(1)).
gen(plus(E1, E2)) :-
	gen(E1),
	gen(E2).
gen(negate(E)) :-
	gen(E).

myAppend3(nil, List, List).
myAppend3(Input, List, Result) :-
	Input = cons(Head, Tail),
	myAppend3(Tail, List, Rest),
	Result = cons(Head, Rest).

% reference solution
myAppend2(nil, List, List).
myAppend2(cons(Head, Tail), List, cons(Head, Rest)) :-
	myAppend2(Tail, List, Rest).

% my solution
myAppend4(Left, Right, Output) :-
	myAppend4(Output, Left, Right, Output).
myAppend4(Accum, Left, Right, Output) :-
	Left = cons(Head, Tail),
	Accum = cons(Head, NewAccum),
	myAppend4(NewAccum, Tail, Right, Output).
myAppend4(Right, nil, Right, _).

takeUpTo(N, _, []) :- N >= 0.
takeUpTo(Accum, [Head|Tail], Result) :-
	Accum > 0,
	Next is Accum - 1,
	Result = [Head|NewResult],
	takeUpTo(Next, Tail, NewResult).

allPairs([], []).
allPairs([One, Two|Tail], [P|Pairs]) :-
	P = pair(One, Two),
	allPairs(Tail, Pairs).
