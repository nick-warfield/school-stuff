public class PrintPattern
{
  public string AddChar(String input, String c, int number)
  {
    for (int i = 0; i < number; i++)
    {
      input += c;
    }
    return input;
  }

  public static void main(String []args)
  {
    String output = "";
    int num = 8;
    int halfNum = num / 2;

    for (int i = 0; i < halfNum; i++)
    {
      output = AddChar(output, " ", halfNum - 1);
      output = AddChar(output, "+", i + 1);
      output = AddChar(output, " ", halfNum + 1);
      output = AddChar(output, "+", 2 * i + 1);
    }
    for (int i = halfNum; i > 0; i--)
    {
      output = AddChar(output, "+", i);
    }

    System.out.println(output);
  }
}
