factorial(0, 1).
factorial(N, Result) :-
	N > 0,
	Next is N - 1,
	factorial(Next, Total),
	Result is N * Total.

fib(0, 0).
fib(1, 1).
fib(N, Result) :-
	N > 1,
	X is N - 1,
	Y is N - 2,
	fib(X, Total1),
	fib(Y, Total2),
	Result is Total1 + Total2.

myBetween(Lo, Hi, Lo) :-
	Lo =< Hi.
myBetween(Lo, Hi, X) :-
	Lo =< Hi,
	NewLo is Lo + 1,
	myBetween(NewLo, Hi, X).
