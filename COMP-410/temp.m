:- module temp.

:- interface.

:- import_module io.

:- implementation.

:- import_module int.
:- import_module solutions.

:- pred foo(int).
:- mode foo(in) is semidet.
:- mode foo(out) is multi.
foo(1).
foo(2).
foo(3).

:- pred first(list(int), int).
:- mode first(in, out) is semidet.
first([Head|_], Head).

% this is a comment
main(!IO) :-
	io.write("Hello World\n", !IO).
