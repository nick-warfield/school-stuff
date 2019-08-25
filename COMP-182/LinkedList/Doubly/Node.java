public class Node
{
	private int data;
	private Node next, prev;

	public Node(int data)
	{
		this.data = data;
		next = null;
		prev = null;
	}
	public Node(int data, Node prev, Node next)
	{
		this.data = data;
		this.next = next;
		this.prev = prev;
	}

	public int GetData() { return data;	}
	public void SetData(int data) { this.data = data; }

	public Node GetNext() { return next;	}
	public void SetNext(Node next) { this.next = next; }

	public Node GetPrev() { return prev;	}
	public void SetPrev(Node prev) { this.prev = prev; }
}
