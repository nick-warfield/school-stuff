public class TimeSort
{
	private static long insertionTime = 0, quickTime = 0, heapTime = 0, timeStamp = 0;
		
	public static void main(String[] args)
	{
		Sort sort = new Sort();
		String log = "";

		for (int i = 2; i <= 5; i++)
		{
			int size = (int)Math.pow(10, i);
			Object[] testArray1 = new Object[size];
			Object[] testArray2 = new Object[size];
			Object[] testArray3 = new Object[size];
			
			for (int j = 0; j < size; j++)
			{
				Integer num = (Integer)(int)(Math.random() * 10000);
				testArray1[j] = num;
				testArray2[j] = num;
				testArray3[j] = num;
			}
			HeapSort heap = new HeapSort(testArray3);
			log += "Array Size: " + Integer.toString(size) + "\n";

			timeStamp = System.nanoTime();
			sort.insertion(testArray1);
			log += "Insertion Sort Time:\t" + Long.toString(delta()) + " microSeconds\n";
			insertionTime += delta();

			timeStamp = System.nanoTime();
			sort.quick(testArray2);
			log += "Quick Sort Time:\t" + Long.toString(delta()) + " microSeconds\n";
			quickTime += delta();

			timeStamp = System.nanoTime();
			heap.sort();
			log += "Heap Sort Time:\t\t" + Long.toString(delta()) + " microSeconds\n\n";
			heapTime += delta();
		}
		log += "Total Sorting Times:\n";
		log += "Insertion Sort Time:\t" + Long.toString(insertionTime) + " microSeconds\n";
		log += "Quick Sort Time:\t" + Long.toString(quickTime) + " microSeconds\n";
		log += "Heap Sort Time:\t\t" + Long.toString(heapTime) + " microSeconds\n\n";

		System.out.print(log);
	}

	private static long delta() { return (System.nanoTime() - timeStamp) / 1000; }
	private static void print(Object[] arr)
	{
		String s = "[ " + arr[0].toString();
		for (int i = 1; i < arr.length; i++)
		{
			s += ", " + arr[i].toString();
		}
		System.out.println(s + " ]");
	}
}
