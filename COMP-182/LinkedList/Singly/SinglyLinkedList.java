//need to check for memory leaks

public class SinglyLinkedList
{
	private Node head;
	private int numOfElements = 0;

	public SinglyLinkedList()
	{
		this.head = null;
	}
	public SinglyLinkedList(int data)
	{
		this.head = new Node(data);
		numOfElements++;
	}

	public boolean isEmpty()
	{
		return head == null;
	}
	public int Length()
	{
		return numOfElements;
	}

	public int GetData(int index)
	{
		 return GetData(head, 0, index);
	}
	private int GetData(Node node, int counter, int index)
	{
		if (counter >= index || node.GetNext() == null)
		{
			return node.GetData();
		}
		else
		{
			return GetData(node.GetNext(), counter + 1, index);
		}
	}

	public void Prepend(int data)
	{
		Insert(0, data);
	}

	public void Append(int data)
	{
		Insert(numOfElements, data);
	}

	public void Insert(int index, int data) throws IndexOutOfBoundsException
	{
		if (index < 0 || index > numOfElements)
		{
			throw new IndexOutOfBoundsException();
		}
		else if (isEmpty())
		{
			head = new Node(data);
		}
		else if (index == 0)
		{
			Node front = new Node(data, head);
			head = front;
		}
		else
		{
			Insert(head, index - 1, data);
		}
		numOfElements++;
	}
	private void Insert(Node node, int index, int data)
	{
		if (index <= 0 || node.GetNext() == null)
		{
			Node insertion = new Node(data, node.GetNext());
			node.SetNext(insertion);
		}
		else
		{
			Insert(node.GetNext(), index - 1, data);
		}
	}

	public int Remove(int index) throws IndexOutOfBoundsException
	{
		if (index < 0 || index >= numOfElements)
		{
			throw new IndexOutOfBoundsException();
		}
		else if (index == 0)
		{
			Node temp = head;
			int value = temp.GetData();
			head = head.GetNext();
			temp = null;
			return value;
		}
		else
		{
			numOfElements--;
			return Remove(index - 1, head);
		}
	}
	private int Remove(int index, Node node)
	{
		if (index == 0)
		{
			Node temp = node.GetNext();
			int value = temp.GetData();
			node.SetNext(node.GetNext().GetNext());
			temp = null;
			return value;
		}
		else
		{
			return Remove(index - 1, node.GetNext());
		}
	}
	public int RemoveFront()
	{
		return Remove(0);
	}
	public int RemoveBack()
	{
		//needs fixing
		return Remove(numOfElements);
	}

	public void Merge(SinglyLinkedList list)
	{
		if (list == null || list.isEmpty())
		{
			return;
		}
		else if (isEmpty())
		{
			head = list.head;
		}
		else
		{
			Merge(list.head, head);
		}

		numOfElements += list.numOfElements;
		list.numOfElements = 0;
		list.head = null;
	}
	private void Merge(Node listHead, Node node)
	{
		if (node.GetNext() == null)
		{
			node.SetNext(listHead);
		}
		else
		{
			Merge(listHead, node.GetNext());
		}
	}

	public void Split(SinglyLinkedList destination, int index)
	{
		if (isEmpty())
		{
			return;
		}
		else if (index < 0 || index > numOfElements)
		{
			return;
		}
		destination = new SinglyLinkedList();
		Split(head, destination.head, index);
		destination.numOfElements = numOfElements - index + 1;
		numOfElements = index + 1;
	}
	private void Split(Node node, Node destHead, int index)
	{
		if (index <= 0 || node.GetNext() == null)
		{
			destHead = Node.GetNext;
			node.SetNext(null);
		}
		else
		{
			Split(node.GetNext(), destHead, index - 1);
		}
	}

	public String toString()
	{
		Node n = head;
		String s = n.toString();

		while (n.GetNext() != null)
		{
			n = n.GetNext();
			s += ", " + n.toString();
		}

		return s;
	}
}
