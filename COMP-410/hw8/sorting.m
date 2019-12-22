:- module sorting.

:- interface.
:- import_module list.

:- pred insertion_sort(list(int), list(int)).
:- mode insertion_sort(in, out) is det.

:- pred merge_sort(list(int), list(int)).
:- mode merge_sort(in, out) is det.

:- pred quick_sort(list(int), list(int)).
:- mode quick_sort(in, out) is det.

:- implementation.
:- import_module int.

% TODO: write your implementation code below.
% Stubs have been provided which compile, but fail tests.
% The only restriction is that you CANNOT use the sort
% procedures already available in the Mercury libraries
% (e.g., list.sort).  However, you can use anything else
% you want, including things like list.merge.


% INSERTION SORT HINTS:
% You had to implement this in Prolog as part of assignment 5.
% Porting this code to Mercury is likely the path of least
% resistance.
insertion_sort(Unsorted, Sorted) :-
	insertion_sort([], Unsorted, Sorted).

:- pred insert_sorted(list(int), int, list(int)).
:- mode insert_sorted(in, in, out) is det.
insert_sorted([], Integer, [Integer]).
insert_sorted([Head|Tail], Integer, Output) :-
	Integer > Head ->
		(Output = [Head|Result],
		insert_sorted(Tail, Integer, Result)) ;
		Output = [Integer, Head|Tail].

:- pred insertion_sort(list(int), list(int), list(int)).
:- mode insertion_sort(in, in, out) is det.
insertion_sort(Sorted, [], Sorted).
insertion_sort(Accum, [Head|Tail], Sorted) :-
	insert_sorted(Accum, Head, NextAccum),
	insertion_sort(NextAccum, Tail, Sorted).

% MERGE SORT HINTS:
% You will need to split the input list into two portions of
% approximately the same length.  You can either do this yourself,
% or make use of some of the routines in Mercury's list library
% (https://www.mercurylang.org/information/doc-release/mercury_library/list.html).
% Your split must operate in O(n) or less for merge sort to have the
% final time complexity of O(nlg(n)).
%
% You can either write your own merge, or use the one from Mercury's
% list library.
merge_sort(Unsorted, Sorted) :-
	merge_sort([], Unsorted, Sorted).

:- pred merge_sort(list(int), list(int), list(int)).
:- mode merge_sort(in, in, out) is det.
merge_sort([], [], []).
merge_sort([H|T], [], Sorted) :-
	List1 = [H|T],
	(T = [] -> Sorted = [H] ;
	list.det_split_list(list.length(List1) / 2, List1, Left1, Right1),
	merge_sort(Left1, Right1, Sorted)).
merge_sort([], [H|T], Sorted) :-
	List1 = [H|T],
	(T = [] -> Sorted = [H] ;
	list.det_split_list(list.length(List1) / 2, List1, Left1, Right1),
	merge_sort(Left1, Right1, Sorted)).

merge_sort([H1|T1], [H2|T2], Sorted) :-
	List1 = [H1|T1],
	list.det_split_list(list.length(List1) / 2, List1, Left1, Right1),
	merge_sort(Left1, Right1, LeftSorted),

	List2 = [H2|T2],
	list.det_split_list(list.length(List2) / 2, List2, Left2, Right2),
	merge_sort(Left2, Right2, RightSorted),

	list.merge(LeftSorted, RightSorted) = Sorted.

% :- pred mymerge(list(int), list(int), list(int)).
% :- mode mymerge(in, in, out) is det.
% mymerge([], [], []).
% mymerge([LeftHead|LeftTail], [RightHead|RightTail], Output) :-
% 	LeftHead > RightHead ->
% 		(mymerge([LeftHead|LeftTail], RightTail, Result),
% 		Output = [RightHead|Result]) ;
% 		(mymerge(LeftTail, [RightHead|RightTail], Result),
% 			Output = [LeftHead|Result]).

% QUICK SORT HINTS:
% You do not need to be smart about choosing a pivot value; you can,
% for example, always pick the first value in the input list.
%
% It is possible to partition the list using procedures in Mercury's
% list library, or you can write your own.  It's ideal, though not
% required, to only perform a single pass through the list for
% the partitioning.  Whatever approach you take, your partitioning
% should operate in O(n) or less.
%
% A basic append will work for joining lists together at the end.
% Whatever method you pick, this should operate in O(n) or less.
quick_sort([], []).
quick_sort([Pivot|List], Sorted) :-
	quick_sort_helper(Pivot, List, Smalls, Bigs),
	quick_sort(Smalls, Left),
	quick_sort(Bigs, Right),
	list.append(Left, [Pivot|Right]) = Sorted.

:- pred quick_sort_helper(int, list(int), list(int), list(int)).
:- mode quick_sort_helper(in, in, out, out) is det.
quick_sort_helper(_, [], [], []).
quick_sort_helper(Pivot, [Head|Tail], Smalls, Bigs) :-
	Head < Pivot ->
		(Smalls = [Head|Next],
		quick_sort_helper(Pivot, Tail, Next, Bigs)) ;
		Bigs = [Head|Next],
		quick_sort_helper(Pivot, Tail, Smalls, Next).
