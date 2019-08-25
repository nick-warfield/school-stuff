package algebrablocks;

import org.apache.commons.math3.fraction.Fraction;

public class Variable implements Comparable<Variable>
{
	public Variable(String letter)
	{
		m_id = letter;
		m_power = new Fraction(1);
	}
	public Variable(String letter, Fraction power)
	{
		m_id = letter;
		m_power = power;
	}
	public Variable(Variable other)
	{
		m_id = other.m_id;
		m_power = other.m_power;
	}

	public Variable combine(Variable other)
	{
		if (!m_id.equals(other.m_id))
		{
			throw new ArithmeticException(
					"Cannot combine variables with different letters");
		}
		Variable temp = new Variable(this);
		temp.m_power = temp.m_power.add(other.m_power);
		return temp;
	}

	public void negate() { m_power = m_power.negate(); }

	public boolean isLike(Variable other)
	{
		return m_id.equals(other.m_id);
	}

	public int compareTo(Variable other)
	{
		return m_id.compareTo(other.m_id);
	}

	public String letter() { return m_id; }
	public Fraction power() { return m_power; }

	private String m_id;
	private Fraction m_power;
};
