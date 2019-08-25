public class SortTest
{
	public static void main(String[] args)
	{
		int[] arr = { 0, 10, -3, 6, 9, -1, 80, -9, 9, 2 };

		System.out.print("\nInitial Array:\t" + Sort.PrintArray(arr) + "\n\n");
		Sort.MergeSort(arr);
		System.out.print("\nSorted Array:\t" + Sort.PrintArray(arr) + "\n");
	}
}
