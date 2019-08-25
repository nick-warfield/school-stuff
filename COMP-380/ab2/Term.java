package algebrablocks;

import java.util.TreeSet;
import org.apache.commons.math3.fraction.Fraction;
import algebrablocks.Variable;

public class Term
{
	private Fraction m_coefficient;
	private TreeSet<Variable> m_variables;

	public Term(Fraction coefficient, TreeSet<Variable> variables)
	{
		m_coefficient = coefficient;
		m_variables = variables;
	}
	public Term(Term other)
	{
		m_coefficient = other.m_coefficient;
		m_variables = other.m_variables;
	}

	public void flip()
	{
		m_coefficient = m_coefficient.reciprocal();
		for (Variable v : m_variables) { v.negate(); }
	}

	public Term add(Term other) throws ArithmeticException
	{
		if (!this.isLike(other))
		{
			throw new ArithmeticException("Cannot add unlike terms");
		}
		Term value = new Term(this);
		value.m_coefficient =
			value.m_coefficient.add(other.m_coefficient);
		return value;
	}

	public Term multiply(Term other)
	{
		Fraction coeff = m_coefficient.multiply(other.m_coefficient);

		TreeSet<Variable> vars = new TreeSet<Variable>();
		for (Variable v1 : m_variables)
		{
			Variable v0 = new Variable(v1);
			for (Variable v2 : other.m_variables)
			{
				if (v0.isLike(v2)) { v0 = v0.combine(v2); }
			}
			if (v0.power() != new Fraction(0)) { vars.add(v0); }
		}
		
		return new Term(coeff, vars);
	}

	public boolean isLike(Term other)
	{
		for (Variable v : m_variables)
		{
			if (!other.m_variables.contains(v)) { return false; }
		}
		return true;
	}
	public String toString()
	{
		if (m_variables.isEmpty()) { return m_coefficient.toString(); }

		int n = m_coefficient.getNumerator();
		int d = m_coefficient.getDenominator();

		String top = "", bot = "";
		if (n != 1) { top += Integer.toString(n); }
		if (d != 1) { bot += Integer.toString(d); }
		
		for (Variable v : m_variables)
		{
			String vs = v.letter();
			if (v.power().abs().compareTo(new Fraction(1)) != 0)
			{
				vs += "^(" + v.power().abs().toString() + ")";
			}

			if (v.power().compareTo(new Fraction(0)) > 0)
			{ top += vs; } else { bot += vs; }
		}

		if (bot.compareTo("") == 0) { return top; } 
		return top + " / " + bot;
	}
};
