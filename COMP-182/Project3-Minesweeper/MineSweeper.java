import java.util.*;

public class MineSweeper
{
	private Cell[][] board;
	private int rows, cols, mines;

	public MineSweeper()
	{
		rows = 4;
		cols = 5;
		mines = 5;
		board = new Cell[cols][rows];
	}
	public MineSweeper(int rows, int cols, int mines)
	{
		this.rows = rows;
		this.cols = cols;
		this.mines = mines;
		board = new Cell[cols][rows];
	}

	public static void play()
	{
		Scanner scan = new Scanner(System.in);
		int r = 0, c = 0, m = 0;

		// prompt user for game parameters
		while (c <= 0)
		{
			print("Board Width: ");
			if (scan.hasNextInt()) { c = scan.nextInt(); }
			if (c <= 0) { println("Please Enter a Positive Number"); }
		}
		while (r <= 0)
		{
			print("Board Height: ");
			if (scan.hasNextInt()) { r = scan.nextInt(); }
			if (r <= 0) { println("Please Enter a Positive Number"); }
		}
		while (m <= 0)
		{
			print("Number of Mines: ");
			if (scan.hasNextInt()) { m = scan.nextInt(); }
			if (m <= 0) { println("Please Enter a Positive Number"); }
		}

		// start game
		MineSweeper mine = new MineSweeper(r, c, m);
		mine.game();
	}

	public void game()
	{
		// populate board
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{ board[i][j] = new Cell(); }
		}

		// adjust mine count if unreasonable
		if (mines >= rows * cols)
		{
			mines = (rows * cols) - 1;
		}

		// generate mines
		java.util.Random rand = new java.util.Random();
		for (int count = 0; count < mines;)
		{
			int x = rand.nextInt(cols);
			int y = rand.nextInt(rows);
			Cell candidate = board[x][y];
			if (!candidate.getMine())
			{
				candidate.setMine();
				count++;
			}
		}

		// calculate counts and fill cells
		for (int x = 0; x < cols; x++)
		{
			for (int y = 0; y < rows; y++)
			{
				if (!board[x][y].getMine())
				{ board[x][y].setCount(getAdjMineCount(x, y)); }
				else
				{ board[x][y].setCount(-1); }
			}
		}

		instructions();
		show();

		// game loop
		boolean exit = false;
		Scanner scan = new Scanner(System.in);
		while (!exit)
		{
			if (scan.hasNext())
			{
				String input = scan.next();
				boolean mineRevealed = false;

				if (input.equals("show"))
				{
					show();
				}
				else if (input.equals("u"))
				{
					mineRevealed = reveal(scan);
				}
				else if (input.equals("m"))
				{
					mark(scan);
				}
				else if (input.equals("q"))
				{
					println("Quitting MineSweeper");
					exit = true;
				}
				else
				{
					invalidInput();
				}

				// check game end conditions
				if (mineRevealed)
				{
					gameOver();
					exit = true;
				}
				else if (allMinesMarked() || allNonMinesUncovered())
				{
					gameWon();
					exit = true;
				}
			}
		}
		scan.close();
	}

	// toggle the mark of cell [x, y]
	private void mark(Scanner scan)
	{
		// get the desired location from user, reject invalid locations
		int[] pos = getPos(scan);
		if (pos.length != 2)
		{
			invalidInput();
			return;
		}

		// toggle mark, display different message depending on change
		boolean wasMarked = board[pos[0]][pos[1]].toggleMark();
		if (wasMarked)
		{
			print(cellMsg(pos));

			if (board[pos[0]][pos[1]].getMark())
			{
				println("has been marked");
			}
			else
			{
				println("has been unmarked");
			}
		}
		else
		{
			println("Cannot mark a revealed cell");
		}
		prompt();
	}

	// uncover cell [x, y], return true if mine was revealed
	private boolean reveal(Scanner scan)
	{
		// get desired location, reject invalid inputs
		int[] pos = getPos(scan);
		if (pos.length != 2)
		{
			invalidInput();
			return false;
		}

		// uncover cell, if count is 0 reveal more adjacent cells
		boolean wasRevealed = true;
		if (board[pos[0]][pos[1]].getCount() == 0)
		{
			autoReveal(pos[0], pos[1]);
			println("auto-reveal triggered");
		}
		else
		{
			wasRevealed = board[pos[0]][pos[1]].uncover();
		}

		// display different messages depending on if a cell was revealed
		print(cellMsg(pos));
		if (wasRevealed)
		{
			println("has been uncovered as : " + board[pos[0]][pos[1]].toString());
		}
		else if (board[pos[0]][pos[1]].getMark())
		{
			println("is marked");
		}
		else
		{
			println("is: " + board[pos[0]][pos[1]].toString());
		}
		prompt();

		// return mine status
		if (wasRevealed)
		{
			return board[pos[0]][pos[1]].getMine();
		}
		else
		{
			return false;
		}
	}

	// keep revealing cells if there is 0% chance of triggering a mine
	private void autoReveal(int x, int y)
	{
		// out of bounds base case
		if (isOOB(x, y)) { return; }

		boolean wasRevealed = board[x][y].uncover();
		int count = board[x][y].getCount();

		// > 0% base case and already revealed base case
		if (count != 0 || !wasRevealed) { return; }

		// reveal adjacent cells
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				autoReveal(x + i, y + j);
			}
		}
	}

	// prompt user for desired location
	private int[] getPos(Scanner scan)
	{
		int pos[] = new int[] { -1, -1 };

		print("> x: ");
		if (scan.hasNextInt())
		{
			pos[0] = scan.nextInt();
		}

		print("> y: ");
		if (scan.hasNextInt())
		{
			pos[1] = scan.nextInt();
		}

		if (isOOB(pos)) { return new int[0]; }
		else { return pos; }
	}

	private void gameOver()
	{
		uncoverAll();
		show();
		println("Game Over!");
	}
	private void gameWon()
	{
		uncoverAll();
		show();
		println("You Did It!");
	}

	// simple messages
	private void prompt() { System.out.print("> "); }
	private String cellMsg(int[] pos)
	{
		String s = "Cell [ " + Integer.toString(pos[0]);
		s += ", " + Integer.toString(pos[1]) + " ] ";
		return s;
	}
	private void instructions()
	{
		System.out.println("show: show board");
		prompt();
		System.out.println("u x y: uncover cell at (x, y)");
		prompt();
		System.out.println("m x y: mark cell at (x, y)");
		prompt();
		System.out.println("q: quit");
		prompt();
	}
	private void invalidInput()
	{
		println("Invalid Input");
		prompt();
	}
	private String numRow()
	{
		String s = "\t   ";
		for (int i = 0; i < cols; i++) { s += Integer.toString(i) + " "; }
		return s + "\n";
	}
	private String status()
	{
		String s = "   Status: " + Integer.toString(getMarkCount());
		s += "/" + Integer.toString(mines);
		return s;
	}

	// displays current state of the board
	public void show()
	{
		String s = numRow();

		for (int j = 0; j < rows; j++)
		{
			s += "\t" + Integer.toString(j) + "| ";
			for (int i = 0; i < cols; i++)
			{
				s += board[i][j].toString() + " ";
			}
			s += "|" + Integer.toString(j) + "\n";
		}

		s += numRow() + status();
		println(s);
		prompt();
	}

	// loops through board, revealing each cell
	private void uncoverAll()
	{
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				Cell c = board[i][j];
				if (c.getMark()) { c.toggleMark(); }
				c.uncover();
			}
		}
	}

	// loops through board, counts the number of marked cells
	private int getMarkCount()
	{
		int count = 0;
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (board[i][j].getMark())
				{
					count++;
				}
			}
		}
		return count;
	}

	// counts the number of mines adjacent to [x, y]
	private int getAdjMineCount(int x, int y)
	{
		int count = 0;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				Cell adj = getAdjCell(x, y, i, j);
				if (adj != null && adj.getMine()) { count++; }
			}
		}
		return count;
	}

	// adds [x, y] with [dirx, diry] and returns cell if in bounds
	private Cell getAdjCell(int x, int y, int dirx, int diry)
	{
		x += dirx;
		y += diry;
		if (x < 0 || x >= cols || y < 0 || y >= rows)
		{
			return null;
		}
		return board[x][y];
	}

	// return true if all mines, and only mines, have been marked
	private boolean allMinesMarked()
	{
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				Cell c = board[i][j];
				if (c.getMine() && !c.getMark())
				{ return false; }
				if (!c.getMine() && c.getMark())
				{ return false; }
			}
		}
		return true;
	}

	// returns true all unmined cells have been uncovered
	private boolean allNonMinesUncovered()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (board[j][i].getCover() && !board[j][i].getMine())
				{ return false; }
			}
		}
		return true;
	}

	private boolean isOOB(int x, int y)
	{
		if (x < 0 || x >= cols || y < 0 || y >= rows)
		{
			return true;
		}
		return false;
	}	
	private boolean isOOB(int[] pos)
	{
		return isOOB(pos[0], pos[1]);
	}

	public static void print(String s) { System.out.print(s); }
	public static void println(String s) { System.out.println(s); }
}

/*
public class Cell
{
	private int adjCount;
	private boolean isMined;
	private boolean isMarked;
	private boolean isCovered;

	public Cell()
	{
		adjCount = 0;
		isMined = false;
		isMarked = false;
		isCovered = true;
	}

	public int getCount() { return adjCount; }
	public void setCount(int count) { adjCount = count; }

	public boolean getMine() { return isMined; }
	public void setMine() { isMined = true; }

	public boolean getMark() { return isMarked; }
	public boolean toggleMark()
	{
		if (!isCovered) { return false; }
		isMarked = !isMarked;
		return true;
	}

	public boolean getCover() { return isCovered; }
	public boolean uncover()
	{
		if (isMarked || !isCovered) { return false; }
		isCovered = false;
		return true;
	}

	public String toString()
	{
		if (isMarked) { return "X"; }
		else if (isCovered) { return "?"; }
		else if (isMined) { return "*"; }
		else if (adjCount == 0) { return "_"; }
		else { return Integer.toString(adjCount); }
	}
}
*/
