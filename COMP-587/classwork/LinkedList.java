public class LinkedList {
	private class Node {
		int head;
		Node tail;

		public Node(final int head, final Node tail) {
			this.head = head;
			this.tail = tail;
		}
	}

	private Node root;

	public LinkedList() {
		root = null;
	}

	public void addFront(final int element) {
		root = new Node(element, root);
	}

	public int getElementAt(final uint index)
	throws NoSuchElementException {
		int curPos = 0;
		Node current = root;

		while (curPos < index && current != null) {
			current = current.tail;
			curPos++;
		}

		if (current == null) {
			throw new NoSuchElementException();
		} else {
			assert(curPos == index);
			return current.head;
		}
	}
}

public class Tester
{
	LinkedList list = new LinkedList();
	list.addFront(5);
	list.addFront(17);
	list.addFront(42);

	@Test
	public void checkFront() {
		assertEquals(42, list.getElementAt(0));
	}

	@Test
	public void checkBack() {
		assertEquals(5, list.getElementAt(2));
	}

	@Test
	public void checkOverflow() {
		assertThrows(() -> list.getElementAt(3));
	}

	@Test
	public void checkEmpty() {
		LinkedList temp = new LinkedList();
		assertThrows(() -> temp.getElementAt(0));
	}
}
