public class Tester
{
	public static void main(String[] args)
	{
			SinglyLinkedList list1 = new SinglyLinkedList(5);
			list1.Append(4);
			list1.Append(3);
			list1.Append(2);
			list1.Append(1);
			list1.Append(0);

			SinglyLinkedList list2 = new SinglyLinkedList(-1);
			list2.Append(-2);
			list2.Append(-3);
			list2.Append(-4);
			list2.Append(-5);

			SinglyLinkedList list3 = new SinglyLinkedList();
			list1.Merge(list2);
			list1.Split(list2, 1);

			list3.Append(100);

			System.out.println(list1.toString());
			System.out.println(list2.toString());
			System.out.println(list3.toString());
	}
}
