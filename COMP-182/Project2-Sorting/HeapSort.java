// Uses min heap
// will sort descending order
public class HeapSort
{
	private Object[] data;
	private int partition;
	private boolean sorted;
	private final int root = 0;

	// constructors
	public HeapSort(Object[] data)
	{
		this.data = data;
	}
	public HeapSort(int size)
	{
		data = new Object[size];
		for (int i = 0; i < size; i++)
		{
			data[0] = (Integer)(int)(Math.random() * 100);
		}
	}

	public Object[] sort()
	{
		if (!sorted)
		{
			bubbleUp();
			bubbleDown();
		}
		return data;
	}

	// inserts in sorted order
	public void insert(Object item)
	{
		if (sorted) { insertInOrder(item); }
		else
		{
			Object[] arr = new Object[data.length + 1];
			for (int i = 0; i < data.length; i++)
			{
				arr[i] = data[i];
			}
			arr[arr.length - 1] = item;
			data = arr;
		}
	}
	private void insertInOrder(Object item)
	{
		Object[] arr = new Object[data.length + 1];
		int index = 0;

		Comparable item2 = (Comparable)item;
		while (index < data.length && item2.compareTo((Comparable)data[index]) < 0)
		{
			arr[index] = data[index];
			index++;
		}
		arr[index] = item;
		index++;
		while (index < arr.length)
		{
			arr[index] = data[index - 1];
			index++;
		}
		data = arr;
	}

	// returns and removes the smallest value
	public Object extractMin()
	{
		Object extracted;
		if (sorted)
		{
			extracted = data[last()];
			resize(0, last() - 1);
		}
		else
		{
			bubbleUp();
			extracted = data[0];
			resize(1, last());
		}
		return extracted;
	}

	private void bubbleUp()
	{
		partition = root + 1;
		for (; partition < data.length; partition++)
		{
			int index = partition, parent = getParent(index);
			while (((Comparable)data[index]).compareTo((Comparable)data[parent]) < 0)
			{
				swap(index, parent);
				index = parent;
				parent = getParent(index);
			}
		}
		sorted = false;
	}

	private void bubbleDown()
	{
		partition = last();
		for (; partition > root; partition--)
		{
			// remove root from heap
			swap(root, partition);

			int index = root, child;
			boolean swapping;

			do
			{
				swapping = false;
				child = minChildIndex(index);

				if (((Comparable)data[index]).compareTo((Comparable)data[child]) > 0)
				{
					swap(index, child);
					index = child;
					swapping = true;
				}
			} while (swapping && index < partition);
		}
		sorted = true;
	}


	private void swap(int index1, int index2)
	{
		Object temp = data[index1];
		data[index1] = data[index2];
		data[index2] = temp;
	}

	private void resize(int firstIndex, int lastIndex)
	{
		Object[] newArr = new Object[lastIndex - firstIndex + 1];
		for (int i = 0; i < newArr.length; i++)
		{
			newArr[i] = data[i + firstIndex];
		}
		data = newArr;
	}

	private int last() { return data.length - 1; }
	private int getParent(int index) { return (index - 1) / 2; }
	private int minChildIndex(int index)
	{
		int left = (index * 2) + 1, right = left + 1;
		if (left >= partition) { return index; }
		else if (right >= partition) { return left; }
		else if (((Comparable)data[left]).compareTo((Comparable)data[right]) < 0) { return left; }
		else { return right; }
	}
}
