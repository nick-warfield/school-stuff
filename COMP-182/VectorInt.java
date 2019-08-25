public class VectorInt
{
	private int[] array;
	private int indexCounter = 0;

	// Constructor
	public VectorInt(int size)
	{
		this.array = new int[size];
		indexCounter = 0;
	}
	public VectorInt(int[] data)
	{
		this.array = new int[data.length * 2];
		Copy(this.array, data);
		// User may want a different sized vector than the array they supply
		indexCounter = 0;
	}

	// Get Element of Array
	public int Retrieve(int index) throws IndexOutOfBoundsException
	{
		if (index < 0 || index >= indexCounter)
		{
			throw new IndexOutOfBoundsException("Element at index " + index + " not initialized.");
		}
		return array[index];
	}
	// Set Element of Array and return the previous value
	public void Insert(int value)
	{
		if (isFull())
		{
			Expand();
		}

		array[indexCounter] = value;
		indexCounter++;
	}
	public int Remove() throws IndexOutOfBoundsException
	{
		if (isEmpty())
		{
			throw new IndexOutOfBoundsException();
		}

		counter--;

		if (counter * 4 <= array.length)
		{
			Shrink();
		}

		return array[counter];
	}
	public int Length()
	{
		return array.length;
	}

	public boolean isFull()
	{
		if (indexCounter >= array.length)
		{
			return true;
		}
		return false;
	}
	public boolean isEmpty()
	{
		if (indexCounter == 0)
		{
			return true;
		}
		return false;
	}

	public void Sort()
	{

	}

	public void Search(int value)
	{

	}

	private int[] Copy(int[] destination, int[] source)
	{
		if (destination.length < source.length)
		{
			//System.out.println("HEY");
			return null;
		}

		for (int index = 0; index < source.length; index++)
		{
			destination[index] = source[index];
		}
		return destination;
	}
	private int[] Expand()
	{
		int[] newArray = new int[array.length * 2];
		array = Copy(newArray, array);
		return array;
	}
	private int[] Shrink()
	{
		int[] newArray = new int[indexCounter * 2 + 1];
		for (int index = 0; index < indexCounter; index++)
		{
			newArray[index] = array[index];
		}
		array = newArray;
		return array;
	}

	public String toString()
	{
		String s = Integer.toString(array[0]);
		for (int index = 1; index < indexCounter; index++)
		{
			s += ", " + Integer.toString(array[index]);
		}
		return s;
	}

	// main method for testing purposes
	public static void main(String[] args)
	{
		int[] nums = new int[5];
		nums[0] = -11;
		nums[1] = 17;
		VectorInt v = new VectorInt(nums);
		nums[4] = 111;

		System.out.println(v.toString());

		int num = 0;
		try
		{
			num = v.Retrieve(4);
		}
		catch (IndexOutOfBoundsException ev)
		{
			System.out.print(ev.toString());
		}
		System.out.println(Integer.toString(num));
	}
}
