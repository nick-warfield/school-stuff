public class Node
{
	private int data;
	private Node next;

	public Node(int data)
	{
		this.data = data;
		next = null;
	}
	public Node(int data, Node next)
	{
		this.data = data;
		this.next = next;
	}

	public int GetData() { return data; }
	public void SetData(int data) { this.data = data; }
	public Node GetNext() { return next; }
	public void SetNext(Node next) { this.next = next; } 
}
