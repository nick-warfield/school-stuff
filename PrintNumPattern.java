public class PrintNumPattern
{
	public static String AddSpaces(int number)
	{
		String s = "";
		for (int i = 0; i < number; i++)
		{
			s += " ";
		}
		return s;
	}

	public static String AddNumbersRecursively(String s, int number)
	{
		for (int i = number; i > 0; i--)
		{
			s = Integer.toString(i) + s + Integer.toString(i);
		}
		return s;
	}

	public static void main (String []args)
	{
		int num = 3;
		int spaceCount = 3;
		String output = AddNumbersRecursively(" ", num) + "\n";

		while (num > 0)
		{
			num--;
			String line = AddNumbersRecursively(AddSpaces(spaceCount), num) + "\n";
			output = line + output + line;
			spaceCount += 2;
		}

		System.out.println(output);
	}
}
