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
