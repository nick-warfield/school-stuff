public class Sort
{
	// these all sort in ascending order

	public static void InsertionSort(int[] array)
	{
		for (int i = 0; i < array.length - 1; i++)
		{
			for (int j = i + 1; j > 0; j--)
			{
				if (array[j] < array[j - 1])
				{
					int temp = array[j];
					array[j] = array[j - 1];
					array[j - 1] = temp;
				}
			}
		}
	}

	public static void SelectionSort(int[] array)
	{
		for (int i = 0; i < array.length; i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < array.length; j++)
			{
				if (array[j] <= array[minIndex])
				{
					minIndex = j;
				}
			}
			int temp = array[i];
			array[i] = array[minIndex];
			array[minIndex] = temp;
		}
	}

	public static void BubbleSort(int[] array)
	{
		boolean swap = true;
		while (swap)
		{
			swap = false;
			for (int i = 1; i < array.length; i++)
			{
				if (array[i] < array[i - 1])
				{
					swap = true;
					int temp = array[i];
					array[i] = array[i - 1];
					array[i - 1] = temp;
				}
			}
		}
	}

	public static void QuickSort(int[] array)
	{
		QuickSort(array, 0, array.length - 1);
	}
	private static void QuickSort(int[] array, int first, int last)
	{
		String log = PrintArray(array, first, last);

		// pivot sorting
		int pivot = first;
		for (int i = first + 1; i <= last; i++)
		{
			if (array[pivot] > array[i])
			{
				int temp, next = pivot + 1;
				if (i != next)
				{
					temp = array[next];
					array[next] = array[i];
					array[i] = temp;
				}

				temp = array[pivot];
				array[pivot] = array[next];
				array[next] = temp;
				pivot++;
			}
		}
		
		log = "P=" + array[pivot] + '\t' + log + " --> " + PrintArray(array, first, last);
		System.out.println(log);

		// detect new arrays, then sort left to right
		if (first != last)
		{
			if (pivot - 1 > first)
			{
				QuickSort(array, first, pivot - 1);
			}
			if (pivot + 1 < last)
			{
				QuickSort(array, pivot + 1, last);
			}
		}
	}

	public static void HeapSort(int[] array)
	{
		String log = "Bubble Up:";
		System.out.println(log);

		// bubble up
		int partition = 1, temp;
		for (; partition < array.length; partition++)
		{
			log = PrintArray(array, 0, partition);
			int index = partition, parent = (partition - 1) / 2;
			while (array[index] > array[parent])
			{
				temp = array[index];
				array[index] = array[parent];
				array[parent] = temp;
				index = parent;
				parent = (index - 1) / 2;
				log += " --> " + PrintArray(array, 0, partition);
			}
			//log += " --> " + PrintArray(array, 0, partition);
			System.out.println(log);
		}

		System.out.println("\nBubble Down:");

		// bubble down
		partition--;
		for (; partition > 0; partition--)
		{
			log = PrintArray(array, 0, partition);

			// remove root from heap
			temp = array[0];
			array[0] = array[partition];
			array[partition] = temp;

			log += " --> " + PrintArray(array, 0, partition);
			System.out.println(log);

			// select smaller child and bubble down
			int index = 0, left, right, swap = 0;
			do
			{
				index = swap;
				left = (index * 2) + 1;
				right = left + 1;

				log = "P=" + array[index];

				if (left < partition)
				{
					log += "\tL=" + array[left];

					if (array[left] > array[index]) { swap = left; }
					if (right < partition && array[right] > array[swap])
					{
						swap = right;
					}
					if (right < partition)
					{
						log += "\tR=" + array[right];
					}
				}
				log += "\tS=" + array[swap];
				System.out.println(PrintArray(array, 0, partition - 1) + '\t' + log);

				temp = array[swap];
				array[swap] = array[index];
				array[index] = temp;
				
//				if (index != swap) {log += " --> " + PrintArray(array, 0, partition - 1);}
			} while (index != swap);

			System.out.println();
		}
	}

	public static void MergeSort(int[] array)
	{
		mergeSortRanges(0, array.length - 1, array);
	}

	private static void mergeSort(int[] array)
	{
		if (array.length == 1) { return; }
		else
		{
			int midpoint = array.length / 2;
			int[] left = new int[midpoint];
			int[] right = new int[array.length - midpoint];

			for(int i = 0; i < midpoint; i++)
			{
				left[i] = array[i];
				right[i] = array[midpoint + i];
			}
			right[right.length - 1] = array[array.length - 1];

			mergeSort(left);
			mergeSort(right);			
			merge(left, right, array);
		}
	}

	private static void mergeSortRanges(int front, int back, int[] array)
	{
		System.out.println(PrintArray(array, front, back));
		if (front != back)
		{
			int midpoint = (front + back) / 2;
			mergeSortRanges(front, midpoint, array);
			mergeSortRanges(midpoint + 1, back, array);

			System.out.print(PrintArray(array, front, midpoint) + " + " + PrintArray(array, midpoint + 1, back) + " ");
			mergeRanges(front, midpoint, midpoint + 1, back, array);
			System.out.println("--> " + PrintArray(array, front, back));
		}
	}
	private static void mergeRanges(int lFront, int lBack, int rFront, int rBack, int[] array)
	{
		int i = lFront, j = rFront, k = lFront;
		while (i <= lBack && j <= rBack && k <= rBack)
		{
			System.out.print("-C");
			if (array[i] < array[j])
			{
				if (i != k)
				{
					System.out.print("-S");
					int temp = array[k];
					array[k] = array[i];
					array[i] = temp;
				}
				i++;
			}
			else
			{
				if (j != k)
				{
					System.out.print("-S");
					int temp = array[k];
					array[k] = array[j];
					array[j] = temp;
				}
				j++;
			}
			k++;
		}
		while (i <= lBack && k <= rBack)
		{
			System.out.print("-L");
			if (i != k)
			{
				System.out.print("-S");
				int temp = array[k];
				array[k] = array[i];
				array[i] = temp;
			}
			i++;
			k++;
		}
		while (j <= rBack && k <= rBack)
		{
			System.out.print("-R");
			if (j != k)
			{
				System.out.print("-S");
				int temp = array[k];
				array[k] = array[j];
				array[j] = temp;
			}
			j++;
			k++;
		}
	}

	private static void merge(int[] left, int[] right, int[] dest)
	{
		int i = 0, j = 0, k = 0;
		while (i < left.length && j < right.length)
		{
			if (left[i] < right[j])
			{
				dest[k] = left[i];
				i++;
			}
			else
			{
				dest[k] = right[j];
				j++;
			}
			k++;
		}
		while (i < left.length)
		{
			dest[k] = left[i];
			i++;
			k++;
		}
		while (j < right.length)
		{
			dest[k] = right[j];
			j++;
			k++;
		}
	}


	public static String PrintArray(int[] array)
	{
		return PrintArray(array, 0, array.length - 1);
	}
	public static String PrintArray(int[] array, int first, int last)
	{
		String s = "[ ";
		for (int i = first; i <= last; i++)
		{
			s += Integer.toString(array[i]) + ", ";
		}
		return s.substring(0, s.length() - 2) + " ]";
	}
}
