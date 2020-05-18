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

    public void addBack(final int element) {
        if (root == null) {
            root = new Node(element, null);
        } else {
            Node current = root;
            while (current.tail != null) {
                current = current.tail;
            }
            current.tail = new Node(element, null);
        }
    }

    public int getElementAt(final int index) {
        if (index < 0) {
			return -1;
        }
        
        int curPos = 0;
        Node current = root;

        while (curPos < index && current != null) {
            current = current.tail;
            curPos++;
        }

        if (current == null) {
			return -1;
        } else {
            assert(curPos == index);
            return current.head;
        }
    }

    public int length() {
        int len = 0;
        Node current = root;
        while (current != null) {
            len++;
            current = current.tail;
        }
        return len;
    }

    public int[] toArray() {
        final int[] result = new int[1];
        Node current = root;
        int index = 0;
        while (current != null) {
            result[index] = current.head;
            current = current.tail;
            index++;
        }
        return result;
    }

    public void mysteryOperation() {
        // TODO: write implementation
    }

	public static void main(String[] args) {
		LinkedList ll = new LinkedList();
		ll.addFront(0);
		System.out.println(ll.toArray());
	}
}
