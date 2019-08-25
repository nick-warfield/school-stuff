public class TimeVector
{
	public static void main(String[] args)
	{
		long time = 0, dTime = 0, iTime = 0;
		Vector v = new Vector();
		String output = "";

		for (int count = 2; count < 6; count++)
		{
			int num = (int)Math.pow(10, count);
			output += "Loops: " + Integer.toString(num);

			for (int method = 0; method < 4; method++)
			{
				time = System.nanoTime();

				for (int loop = 0; loop < num; loop++)
				{
					switch (method)
					{
						case 0: v.insertFront(loop); break;
						case 1: v.removeFront(); break;
						case 2: v.insertBack(loop); break;
						case 3: v.removeBack(); break;
					}
				}

				long delta = delta(time);
				switch (method)
				{
					case 0:
						output += "\tMethod: insertFront()\tTime: " + (delta  / 1000);
						iTime += delta;
						break;
					case 1:
						output += "\tMethod: removeFront()\tTime: " + (delta  / 1000) + '\n';
						dTime += delta;
						break;
					case 2:
						output += "\t\tMethod: insertBack()\tTime: " + (delta  / 1000);
						iTime += delta;
						break;
					case 3:
						output += "\tMethod: removeBack()\tTime: " + (delta  / 1000) + '\n';
						dTime += delta;
						break;
				}
			}
			output += '\n';
		}

		dTime /= 1000;
		iTime /= 1000;
		output += "Total Insertion Time: " + iTime + "\t\t";
		output += "Total Deletion Time: " + dTime;
		System.out.println(output);
	}

	private static long delta(long time)
	{
		return System.nanoTime() - time;
	}
}
