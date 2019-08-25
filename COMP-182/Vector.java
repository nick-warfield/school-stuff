public class Vector
{
	private Integer[] array;

	// Constructor
	public Vector(int size)
	{
		this.array = new Integer[size];
	}

	// Get element of array
	public Integer GetValue(int index)
	{
		if (index >= 0 && index < array.length)
		{
			return array[index];
		}
		System.out.println("ERROR: Array Index Out of Bounds. null returned.");
		return null;
	}
	// Set element of array, return old value
	public Integer SetValue(int index, Integer value)
	{
		Integer oldValue = null;
		if (index >= 0 && index < array.length)
		{
			oldValue = array[index];
			array[index] = value;
		}
		else
		{
			System.out.println("ERROR: Array Index Out of Bounds. null returned.");
		}
		return oldValue;
	}

	// Return the length of the array
	public int Length()
	{
		return array.length;
	}

	// Change the size of the array
	public void Resize(int newSize)
	{
		// Don't bother doing anything if nothing is changing
		if (newSize == array.length) { return; }
		else if (newSize <= 0)
		{
			System.out.println("ERROR: Array Size Must be Greater Than Zero");
			return;
		}

		Integer[] newArray = new Integer[newSize];
		for (int index = 0; index < newSize && index < array.length; index++)
		{
			newArray[index] = array[index];
		}
		array = newArray;
	}

	// Sorts Array using Insertion Sort
	public void Sort()
	{
		Integer sorting;
		int index, compare;
		for (index = 1; index < array.length; index++)
		{
			sorting = array[index];
			compare = index;
			while(compare > 0 && array[compare - 1] > sorting)
			{
				array[compare] = array[compare - 1];
				compare--;
			}
			array[compare] = sorting;
		}
	}

	//retrurns all the elements as a string
	public String toString()
	{
		return toString(", ");
	}
	public String toString(String separator)
	{
		String output = array[0].toString();
		for (int index = 1; index < array.length; index++)
		{
			output += separator + array[index].toString();
		}
		return output;
	}

	// main method for testing purposes
	public static void main(String[] args)
	{
		Vector v = new Vector(15);
		for (int i = 0; i < v.Length(); i++)
		{
			v.SetValue(i, v.Length() - i);
		}
		System.out.println(v.toString());

		v.Sort();
		System.out.println(v.toString());
	}
}
