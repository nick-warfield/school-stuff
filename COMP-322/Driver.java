import java.lang.Thread;

class Sum
{
	private long sum;
	public long get() { return sum; }
	public void set(long sum) { this.sum = sum; }
}

// An alternative is to subclass Thread
class Summation implements Runnable
{
	private long upper;
	private Sum sumValue;
	
	public Summation(long upper, Sum sumValue)
	{
		if (upper < 0)
		throw new IllegalArgumentException();
		this.upper = upper;
		this.sumValue = sumValue;
	}

	public void run()
	{
		try { Thread.sleep(1000); } catch (Exception e) { }
		long sum = 0;
		for (long i = 0; i <= upper; i++)
		sum += i;
		sumValue.set(sum);
	}
}

public class Driver
{
	public static void main(String[] args)
	{
		if (args.length < 1)
		{
			System.err.println("Usage Driver <long> <long> ... <long>");
			System.exit(0);
		}

		Thread[] workers = new Thread[args.length];
		Sum[] sums = new Sum[args.length];
		for (int i = 0; i < args.length; i++)
		{
			long upper = Long.parseLong(args[i]);
			sums[i] = new Sum();
			workers[i] = new Thread(new Summation(upper, sums[i]));
			workers[i].start();
		}
		try
		{
			// wait worker to be done
			for (Thread worker : workers) { worker.join(); }
		}
		catch (InterruptedException ie) { }
		
		for (int i = 0; i < args.length; i++)
		{
			System.out.println("The sum of " + args[i] + " is " + sums[i].get());
		}
	}
}
