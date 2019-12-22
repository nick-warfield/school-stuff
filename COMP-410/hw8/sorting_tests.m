:- module sorting_tests.

:- interface.

:- import_module io.

:- pred main(io::di, io::uo) is det.

:- implementation.

:- import_module solutions.
:- import_module int.
:- import_module list.
:- import_module sorting.

:- type bound == int.
:- type failing_test ---> failing_test(list(int),  % input
				       list(int),  % expected
				       list(int)). % received

:- pred list_element(int).
:- mode list_element(out) is multi.
list_element(0).
list_element(1).
list_element(2).

:- pred decBound(bound, bound).
:- mode decBound(in, out) is semidet.
decBound(In, In - 1) :-
    In > 0.

:- pred make_list(bound, list(int)).
:- mode make_list(in, out) is multi.
make_list(_, []).
make_list(Bound, [H|T]) :-
    decBound(Bound, NewBound),
    list_element(H),
    make_list(NewBound, T).

:- pred failing_tests(bound, pred(list(int), list(int)), list(failing_test)).
:- mode failing_tests(in, in(pred(in, out) is det), out) is det.
failing_tests(Bound, Sort, Failures) :-
    solutions((pred(failing_test(List, Expected, Received)::out) is nondet :-
		   make_list(Bound, List),
		   sort(List, Expected),
		   call(Sort, List, Received),
		   Expected \= Received),
	      Failures).

:- pred write_failure(failing_test, io, io).
:- mode write_failure(in, di, uo) is det.
write_failure(failing_test(Input, Expected, Received), !IO) :-
    io.write_string("\tTest input: ", !IO),
    io.write(Input, !IO),
    io.write_string("\n\tExpected: ", !IO),
    io.write(Expected, !IO),
    io.write_string("\n\tReceived: ", !IO),
    io.write(Received, !IO),
    io.write_string("\n\t------\n", !IO).

:- pred write_failures(list(failing_test), io, io).
:- mode write_failures(in, di, uo) is det.
write_failures([], !IO).
write_failures([H|T], !IO) :-
    write_failure(H, !IO),
    write_failures(T, !IO).

:- pred run_suite(string, pred(list(int), list(int)), io, io).
:- mode run_suite(in, in(pred(in, out) is det), di, uo) is det.
run_suite(SuiteName, SortingRoutine, !IO) :-
    io.write_string(SuiteName, !IO),
    io.write_string(": ", !IO),
    failing_tests(3, SortingRoutine, Failures),
    (if Failures = [] then
         io.write_string("all passed\n", !IO)
     else
         (io.write_int(length(Failures), !IO),
          io.write_string(" FAILURES\n", !IO),
          write_failures(Failures, !IO))).

main(!IO) :-
    run_suite("Insertion Sort (insertion_sort)",
	      insertion_sort,
	      !IO),
    run_suite("Merge Sort (merge_sort)",
	      merge_sort,
	      !IO),
    run_suite("Quicksort (quick_sort)",
	      quick_sort,
	      !IO).
