public class CircularDoublyLinkedList
{
	private Node head;
	private int elementCount = 0;

	public CircularDoublyLinkedList(int data)
	{
		head = new Node(data);
		elementCount = 1;
	}

	public void InsertFront(int data)	{	head = Insert(head.GetPrev(), data, 0);	}
	public void InsertBack(int data) { Insert(head.GetPrev(), data, 0);	}
	public void Insert(int data, int pos)
	{
		if (pos < 0 || pos > elementCount) { return; }
		else if (pos == 0) { InsertFront(data); }
		else if (pos == elementCount) {	InsertBack(data);	}
		else { Insert(head, data, pos - 1);	}
	}
	private Node Insert(Node node, int data, int pos)
	{
		if (pos == 0)
		{
			Node newNode = new Node(data, node.GetNext(), node);
			newNode.GetPrev().SetNext(newNode);
			newNode.GetNext().SetPrev(newNode);
			return newNode;
		}
		return Insert(node.GetNext(), data, pos - 1);
	}

	public int Remove(int pos)
	{
		Node temp = head;
		for (; pos != 0; pos--)
		{
			temp = temp.GetNext();
		}

		temp.GetPrev().SetNext(temp.GetNext());
		temp.GetNext().SetPrev(temp.GetPrev());
		temp.SetNext(null);
		temp.SetPrev(null);
		return temp.GetData();
	}
}
