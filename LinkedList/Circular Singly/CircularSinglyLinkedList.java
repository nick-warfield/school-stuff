public class CircularSinglyLinkedList
{
	private Node head;

	public CircularSinglyLinkedList(int data)
	{
		head = new Node(data);
	}

	public void InsertFront(int data)	{ head = Insert(head, data, 0);	}
	public void Insert(int data, int pos)
	{
		Insert(head, data, pos);
	}
	private Node Insert(Node node, int data, int pos)
	{
		if (pos == 0)
		{
			Node newNode = new Node(data, node.GetNext());
			node.SetNext(newNode);
			return newNode;
		}
		return Insert(node.GetNext(), data, pos - 1);
	}

	public int Remove(int pos)
	{
		return Remove(head, pos);
	}
	private int Remove(Node node, int pos)
	{
		if (pos == 0)
		{
			int data = node.GetNext().GetData();
			node.GetNext().SetNext(null);
			node.SetNext(head);
			return data;
		}
		return Remove(node.GetNext(), pos - 1);
	}
}
