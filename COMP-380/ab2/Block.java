package algebrablocks;

import algebrablocks.Term;
import algebrablocks.Layer;

public class Block extends Layer
{
	private Term m_term;
	private int m_pos;

	public Block(int position, Term term)
	{
		m_pos = position;
		m_term = term;
	}
	public Block(Block other)
	{
		m_pos = other.m_pos;
		m_term = other.m_term;
	}

	public int getPosition() { return m_pos; }
	public void setPosition(int position) { m_pos = position; }

	public Term getTerm() { return m_term; }
	public void setTerm(Term term) { m_term = term; }

	public void merge(Block dest, Block src) { }
};
