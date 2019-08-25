public class DoublyLinkedList
{
	private Node head;
	private int elementCount = 0;

	public DoublyLinkedList()
	{
		head = null;
	}
	public DoublyLinkedList(int data)
	{
		head = new Node(data);
		elementCount = 1;
	}

	public void InsertFront(int data) { Insert(0, data); }
	public void InsertBack(int data) { Insert(elementCount, data); }
	public void Insert(int position, int data) throws IndexOutOfBoundsException
	{
		if (position < 0 || position > elementCount)
		{
			throw new IndexOutOfBoundsException();
		}

		Node temp = head;
		while (position <= 0)
		{
			temp = temp.GetNext();
			position--;
		}

		Node insertion = new Node(data, temp, temp.GetNext());
		if (temp.GetPrev() == null)
		{
			insertion = new Node(data, null, head);
			insertion.GetNext().SetPrev(insertion);
			head = insertion;
		}
		else if (temp.GetNext() == null)
		{
			insertion.GetPrev().SetNext(insertion);
		}
		else
		{
			insertion.GetPrev().SetNext(insertion);
			insertion.GetNext().SetPrev(insertion);
		}

		elementCount++;
	}

	public int RemoveFront() { return Remove(0); }
	public int RemoveBack() { return Remove(elementCount - 1); }
	public int Remove(int position) throws IndexOutOfBoundsException
	{
		if (position < 0 || position >= elementCount)
		{
			throw new IndexOutOfBoundsException();
		}

		Node temp = head;

		while (position != 0)
		{
			temp = temp.GetNext();
			position--;
		}

		if (temp == head)
		{
			head = temp.GetNext();
		}

		if (temp.GetPrev() == null)
		{
			head = temp.GetNext();
			temp.GetNext().SetPrev(null);
		}
		else if (temp.GetNext() == null)
		{
			temp.GetPrev().SetNext(temp.GetPrev());
		}
		else
		{
			temp.GetPrev().SetNext(temp.GetNext());
			temp.GetNext().SetPrev(temp.GetPrev());
		}
		temp.SetNext(null);
		temp.SetPrev(null);

		elementCount--;
		return temp.GetData();
	}

	public String toString()
	{
		String s = "";
		Node temp = head;

		for (int i = 0; i < elementCount; i++)
		{
			s += Integer.toString(temp.GetData()) + ", ";
		}
		if (elementCount != 0) { s = s.substring(0, s.length() - 1); }

		return s;
	}
}
