public class Vector
{
	private Object[] array;
	private int elementCount = 0;

	public boolean isFull()	{	return elementCount == array.length; }
	public boolean isHalfEmpty() { return elementCount * 4 <= array.length; }
	public boolean isEmpty() { return elementCount == 0; }
	public int length() { return elementCount; }

	public Vector()
	{
		array = new Object[1];
	}
	public Vector(Object data)
	{
		array = new Object[] { data };
		elementCount = 1;
	}

	public void insertFront(Object data) { insert(data, 0); }
	public void insertBack(Object data) {	insert(data, elementCount);	}
	public void insert(Object data, int index)
	{
		// bounds check
		if (index < 0 || index > elementCount) { return; }

		//Shift elements right to prep for insertion, then insert
		shiftRight(index);
		array[index] = data;
		elementCount++;

		if (isFull()) { Expand(); }
	}

	public Object removeFront()	{	return remove(0);	}
	public Object removeBack() { return remove(elementCount - 1);	}
	public Object remove(int index)
	{
		// Check bounds & check if array has something to remove
		if (index < 0 || index >= elementCount || isEmpty()) { return null;	}

		// Save old value, then shift array left to remove
		Object removed = array[index];
		shiftLeft(index);
		elementCount--;

		if (isHalfEmpty()) { Shrink(); }
		return removed;
	}

	private void Expand()
	{
		Object[] newArray = new Object[array.length * 2];
		for (int index = 0; index < elementCount; index++)
		{
			newArray[index] = array[index];
		}
		array = newArray;
	}
	private void Shrink()
	{
		Object[] newArray = new Object[array.length / 2];
		for (int index = 0; index < elementCount; index++)
		{
			newArray[index] = array[index];
		}
		array = newArray;
	}

	// shifts array by 1, assumes inputs account for array bounds
	private void shiftLeft(int start)
	{
		for (int index = start; index < elementCount; index++)
		{
			array[index] = array[index + 1];
		}
	}
	private void shiftRight(int start)
	{
		for (int index = elementCount; index > start; index--)
		{
			array[index] = array[index - 1];
		}
	}

	public String toString()
	{
		String s = "";

		for (int i = 0; i < elementCount; i++)
		{
			s += array[i].toString() + ", ";
		}

		if (s != "") { s = s.substring(0, s.length() - 2); }

		return s;
	}
}
