%% this is prolog code

isInteger(1).	%% it is true that 1 is an integer
isInteger(2).	%% these are called facts
isInteger(3).	%% multiple facts are a procedure

%% this is the start of a procedure
isName(alice).	%% it is true that alice is a name
isName(bob).
%% this is the end of a procedure

%% variables start with a capital letter
%% atoms start with a lowercase letter and refer to data

areEqual(X, X).

tripleEqual(X, X, X).

% this is a rule that is identical to the first procedure
isInteger2(X) :-
	X = 1;
	X = 2;
	X = 3.
