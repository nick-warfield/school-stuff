import java.net.*;
import java.io.*;

public class DateClient
{
	public static void main(String[] args)
	{
		try 
		{
			// this could be changed to an IP name or address other than the localhost
			Socket sock = new Socket("130.166.12.6",6030);
			System.out.println("HEY");
			InputStream in = sock.getInputStream();
			BufferedReader bin = new BufferedReader(new InputStreamReader(in));
			System.out.println("Fetching Date instance from " +
					sock.getInetAddress().toString() + ":" + sock.getPort());
			
			String line;
			while((line = bin.readLine()) != null) { System.out.println(line); }
			sock.close();
		}
		catch (IOException ioe)
		{
			System.err.println(ioe);
		}
	}
}
