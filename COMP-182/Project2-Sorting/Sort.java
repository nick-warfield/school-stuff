// sorts in descending order
public class Sort
{
	public static Object[] insertion(Object[] data)
	{
		for (int start = 0; start < data.length - 1; start++)
		{
			for (int index = start + 1; index > 0; index--)
			{
				Comparable a = (Comparable) data[index];
				Comparable b = (Comparable) data[index - 1];
				if (a.compareTo(b) <= 0)
				{
					swap(data, index, index - 1);
				}
			}
		}

		return data;
	}

	public static Object[] quick(Object[] data)
	{
		quickSort(data, 0, data.length - 1);
		return data;
	}
	private static void quickSort(Object[] data, int first, int last)
	{
		// move smaller numbers to left of pivot,
		// and bigger numbers to the right
		int pivot = first;
		for (int index = first + 1; index <= last; index++)
		{
			Comparable a = (Comparable) data[pivot];
			Comparable b = (Comparable) data[index];
			if (a.compareTo(b) >= 0)
			{
				int next = pivot + 1;
				if (index != next) { swap(data, index, next); }
				swap(data, pivot, next);
				pivot++;
			}
		}

		// detect new arrays, then sort left to right
		if (first != last)
		{
			if (pivot - 1 > first) { quickSort(data, first, pivot - 1); }
			if (pivot + 1 < last)  { quickSort(data, pivot + 1, last);  }
		}
	}

	private static void swap(Object[] arr, int index1, int index2)
	{
		Object temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}
}
