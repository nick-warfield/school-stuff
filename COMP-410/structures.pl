% List: cons(Element, List) | nil

% Length: calculates length of a linked list
myLength(nil, 0).
myLength(cons(_, Rest), Result) :-
	myLength(Rest, RestLength),
	Result is RestLength + 1.

myLength1([], 0).
myLength1([_|Tail], Length) :-
	myLength2(Tail, TLength),
	Length is TLength + 1.

% tail recursive length procedure
myLenght2(List, Length) :-
	myLength2(List, 0, Length).

myLength2([], Accum, Accum).
myLength2([_|Tail], Accum, Result) :-
	NewAccum is Accum + 1,
	myLength2(Tail, NewAccum, Result).


% Append: List1, List2, Output
myAppend([], List, List).
myAppend([Head|Tail], Input2, [Head|Output]) :-
	myAppend(Tail, Input2, Output).

selectOne([Head|Tail], Head, Tail).
selectOne([Head|Tail], Selected, [Head|TailRemainder]) :-
	selectOne(Tail, Selected, TailRemainder).

allPairs([], []).
allPairs(List, [[FirstItem, SecondItem]|RestResult]) :-
	selectOne(List, FirstItem, RestItems1),
	selectOne(RestItems1, SecondItem, RestItems2),
	allPairs(RestItems2, RestResult).
