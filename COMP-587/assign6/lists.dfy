// Nil: empty list
// Cons: non-empty list (Node)
datatype List<A> = Nil | Cons(head: A, tail: List<A>)

datatype Pair<A, B> = Pair(fst: A, snd: B)

// []: Nil
// [1]: Cons(1, Nil)
// [1, 2]: Cons(1, Cons(2, Nil))
// [1, 2, 3]: Cons(1, Cons(2, Cons(3, Nil)))

// Nil: 0
// Cons(_, tail): length(tail) + 1
function method length<A>(list: List<A>): int
	ensures length(list) >= 0;
	ensures has_length(list, length(list));
{
	if (list.Nil?) then 0 else length(list.tail) + 1
}

predicate has_length<A>(list: List<A>, len: int)
{
	(list.Nil? ==> len == 0) &&
  (list.Cons? ==> exists restLen :: has_length(list.tail, restLen) && len == restLen + 1)
}

ghost method length_works_correctly()
{
	var nil: List<int> := Nil;
	assert length(nil) == 0;
	assert length(Cons(0, Nil)) == 1;
	assert length(Cons(0, Cons(1, Nil))) ==  2;
	assert length(Cons(0, Cons(1, Cons(2, Nil)))) == 3;
}

// issues:
//   -index could get negative
//   -index could be too big
//
// getElementAtIndex(Nil, 0)
// getElementAtIndex(Cons(1, Cons(2, Nil)), 5)
//
function method getElementAtIndex<A>(list: List<A>, index: int): A
	requires 0 <= index < length(list);
	ensures is_element_at_index(list, index, getElementAtIndex(list, index));
{
	if (index == 0) then list.head else getElementAtIndex(list.tail, index - 1)
}

predicate is_element_at_index<A>(list: List<A>, index: int, element: A)
	requires 0 <= index < length(list);
{
	(index == 0 ==> list.head == element) &&
  (index > 0 ==> is_element_at_index(list.tail, index - 1, element))
}

ghost method testGetElementAtIndex() {
	assert getElementAtIndex(Cons(1, Nil), 0) == 1;
	assert getElementAtIndex(Cons(2, Cons(1, Nil)), 1) == 1;
	assert getElementAtIndex(Cons(2, Cons(1, Nil)), 0) == 2;
}

function method listToSeq<A>(list: List<A>): seq<A>
  ensures length(list) == |listToSeq(list)|;
{
	if (list.Nil?) then [] else [list.head] + listToSeq(list.tail)
}
  
// Cons(1, Cons(2, Cons(3, Nil))): [1, 2, 3]
// take([1, 2, 3], 0) == []
// take([1, 2, 3], 1) == [1]
// take([1, 2, 3], 2) == [1, 2]
// take([5, 6, 3], 2) == [5, 6]
// take([5, 6, 2], 3) == [5, 6, 2]
//
// take([2, 1, 3], -1) == <<INVALID>>
// take([9, 3, 4], 5) == <<INVALID>>
//
function method take<A>(list: List<A>, amount: int): List<A>
	requires 0 <= amount <= length(list);
	ensures length(take(list, amount)) == amount;
	ensures forall i :: 0 <= i < amount ==>
		getElementAtIndex(list, i) == getElementAtIndex(take(list, amount), i);
{
	if (amount == 0) then Nil else Cons(list.head, take(list.tail, amount - 1))
}

// drop([10, 11, 12], 0) == [10, 11, 12];
// drop([10, 11, 12], 1) == [11, 12];
// drop([10, 11, 12], 2) == [12];
// drop([10, 11, 12], 3) == [];
//
// drop([10, 11, 12], -1) == <<INVALID>>
// drop([10, 11, 12], 4) == <<INVALID>>
//
// The preconditions and postconditions are already provided.
function method drop<A>(list: List<A>, amount: int): List<A>
  requires 0 <= amount <= length(list);
  ensures length(drop(list, amount)) == length(list) - amount;
  ensures listToSeq(list)[amount..] == listToSeq(drop(list, amount));
{
  // TODO: implement drop's body.  You'll need recursion.
  // As a hint, dropping no elements results in the same list.
	if (amount == 0) then list else drop(list.tail, amount - 1)
}

// append([], [1, 2, 3]) == [1, 2, 3];
// append([1, 2, 3], []) == [1, 2, 3];
// append([1], [2, 3]) == [1, 2, 3];
// append([1, 2], [3, 4]) == [1, 2, 3, 4];
//
// TODO: implement postconditions on append.  You should have three:
// -The length of the result should be the same as the sum of the lengths
//  of the inputs
// -The first elements of the result should be the same as the first input list.
//  It's recommended to use listToSeq for this and slice the result, similar
//  to drop.
// -The last elements of the result should be the same as the second input list.
//  It's again recommended to use listToSeq for this.
function method append<A>(l1: List<A>, l2: List<A>): List<A>
  // TODO: write postconditions here
  ensures length(l1) + length(l2) == length(append(l1, l2));
  ensures listToSeq(l1) == listToSeq(append(l1, l2))[..length(l1)];
  ensures listToSeq(l2) == listToSeq(append(l1, l2))[length(l1)..];
{
  if (l1.Nil?) then l2 else Cons(l1.head, append(l1.tail, l2))
}

// zip([], []) == [];
// zip([1, 2, 3], [true, true, false]) == [Pair(1, true), Pair(2, true), Pair(3, false)];
// zip([false, true], [4, 3]) == [Pair(false, 4), Pair(true, 3)];
// zip([1, 2], [true]) == <<INVALID>>;
// zip([false], [3]) == [Pair(false, 3)];
//
// TODO: implement zip.
// Hints for pre/postconditions:
// -The two lists need to be of the same length.
// -The output should be the same length as the input.
// -The index of each output element corresponds to the index of both inputs.
//  Specifically, the first (fst) element of the output pair comes from the first list,
//  and the second (snd) element of the output pair comes from the second list.
//  This may be more easily phrased as two postconditions (one referring to fst and the
//  other to snd).  It's recommended to use getElementAtIndex for this, similar to take
// Hints for the implementation:
// -You should return either Nil or a Cons with a recursive call to zip, similar to
//  take and append

function method zip<A, B>(l1: List<A>, l2: List<B>): List<Pair<A, B>>
  requires length(l1) == length(l2);
  ensures length(l1) == length(l2) == length(zip(l1, l2));
  ensures forall i :: 0 <= i < length(l1) ==>
	getElementAtIndex(l1, i) == getElementAtIndex(zip(l1, l2), i).fst;
  ensures forall i :: 0 <= i < length(l2) ==>
	getElementAtIndex(l2, i) == getElementAtIndex(zip(l1, l2), i).snd;

{
	if l1 == Nil then Nil else Cons(Pair(l1.head, l2.head), zip(l1.tail, l2.tail))
}

