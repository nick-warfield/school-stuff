package algebrablocks;

import java.lang.Math;
import java.lang.IllegalArgumentException;
import java.util.TreeSet;
import java.util.Vector;

import org.apache.commons.math3.fraction.Fraction;

import algebrablocks.*;

public class Equation
{
	private Layer root;
	private Block selected;

	public Equation(String input)
	{
		selected = null;

		System.out.println("Input: " + input);
		input = input.replaceAll("\\s+", "");		// remove all whitespace
		String[] temp = input.split("(?=\\+|-|\\=|\\*|/)");
		Vector<String> parsed = new Vector<String>();

		System.out.print("Trimmed: ");
		for (String t : temp) { System.out.print(t + " | "); }
		System.out.println();

		// pull out operators
		parsed.add(temp[0]);
		for (int i = 1; i < temp.length; ++i)
		{
			if (temp[i].length() == 1) { parsed.add(temp[i]); }
			else
			{
				parsed.add(temp[i].substring(0, 1));
				parsed.add(temp[i].substring(1));
			}
		}

		// insert nums on single variables
		for (int i = 0; i < parsed.size(); i++)
		{
			if (!isSign(parsed.get(i)) && !isNum(parsed.get(i).charAt(0)))
			{ parsed.set(i, "1" + parsed.get(i)); }
		}

		// apply negationns, convert subtraction to addition
		for (int i = 0; i < parsed.size(); i++)
		{
			while (i < parsed.size() && parsed.get(i).compareTo("-") != 0) { ++i; }
			if (i < parsed.size())
			{
				parsed.set(i + 1, "-" + parsed.get(i + 1));
				if (i > 0 && !isSign(parsed.get(i - 1))) { parsed.set(i, "+"); }
				else { parsed.remove(i); }
			}
		}

		// verify formatting before constructing terms
		for (int i = 1; i < parsed.size(); i += 2)
		{
			if (!isSign(parsed.get(i)))
			{
				throw new IllegalArgumentException("Parse Error: parsed not separated by opperators");
			}
		}
		if (isSign(parsed.firstElement()) || isSign(parsed.lastElement()))
		{
			throw new IllegalArgumentException("Input Error: Equation should start or end with operators");
		}

		// collect terms
		Vector<Block> blocks = new Vector<Block>();
		for (int i = 0; i < parsed.size(); i += 2)
		{
			Fraction frac = new Fraction(1);
			TreeSet<Variable> vars = new TreeSet<Variable>();
			String t = parsed.get(i);

			// grab number part
			int pos = 1, start = 0;
			while (pos < t.length() && isNum(t.charAt(pos))) { ++pos; }
			frac = new Fraction(Integer.parseInt(t.substring(start, pos)));

			// grab variables
			while (pos < t.length())
			{
				String v = "";
				v += t.charAt(pos);
				pos++;
				Fraction p = new Fraction(1);
				while (pos < t.length() && isNum(t.charAt(pos))) { v += t.charAt(pos); ++pos; }
				if (pos < t.length() && t.charAt(pos) == '^')
				{
					start = ++pos;
					while (pos < t.length() && (isNum(t.charAt(pos)) || t.charAt(pos) == '-')) { ++pos; }
					p = new Fraction(Integer.parseInt(t.substring(start, pos)));
				}
				vars.add(new Variable(v, p));
			}
			blocks.add(new Block(i, new Term(frac, vars)));
		}

		// create layers and place terms
		root = new EqLayer();
		int eq = 1, adjusted;
		while (parsed.get(eq).charAt(0) != '=') { eq += 2; }
		adjusted = (eq + 1) / 2;
		for (Block b : blocks)
		{
			b.setPosition(adjusted - b.getPosition() +
					b.getPosition() < adjusted ? 0 : 1);
		}

		Layer l1 = new Block(blocks.get(adjusted - 1));
		// left hand side
		for (int i = 1; i * 2 < eq; ++i)
		{
			Layer l2 = createLayer(parsed.get(eq - i * 2));
			while (i * 2 < eq && l1.getClass().equals(l2.getClass()))
			{
				l1.add(new Block(blocks.get(adjusted - i)));
				i++;
				l2 = createLayer(parsed.get(eq - i * 2));
			}
		}
	}

	public void select(float pos)
	{
		selected = find((int)pos, root);
	}
	public void deselect() { selected = null; }

	public void move(float pos)
	{
		if (selected == null || Math.round(pos) == 0) { return; }
		float delta = Math.abs(pos % 1);
		if (delta < 0.333 || delta > 0.666) { return; }

		// this should be a differnt case, not an error
		if (Math.signum(pos) != Math.signum(selected.getPosition())) { return; }

		int oldPos = selected.getPosition();
		int newPos = Math.round(pos);
		shiftOut(newPos);
		selected.setPosition(newPos);
		shiftIn(oldPos);

		deselect();
	}
	public void merge(float pos)
	{
		if (selected == null || Math.round(pos) == 0) { return; }
		if (Math.signum(pos) != Math.signum(selected.getPosition())) { return; }
		float delta = Math.abs(pos % 1);
		if (delta > 0.333 && delta < 0.666) { return; }

		Block dest = find(Math.round(pos));
		if (dest == null) { return; }

		Layer l = grabLayer(selected);
		l.merge(dest, selected);

		delete(selected.getPosition());
		shiftIn(selected.getPosition());
		deselect();
	}

	// any code that calls shiftOut should call shiftIn later
	// creates a hole at startingNum
	private void shiftOut(int startingNum)
	{
		Block outer = find(startingNum + 1);
		Block inner = find(startingNum);
		while (outer != null);
		{
			inner.setPosition(outer.getPosition());
			inner = outer;
			outer = find(outer.getPosition() + 1);
		}
		inner.setPosition(inner.getPosition() + 1);
	}
	
	// fills a hole at startingNum
	private void shiftIn(int startingNum) throws IllegalArgumentException
	{
		if (find(startingNum) != null) { throw new IllegalArgumentException(); }
		startingNum++;
		Block outer = find(startingNum + 1);
		Block inner = find(startingNum);
		while (outer != null);
		{
			inner.setPosition(inner.getPosition() - 1);
			inner = outer;
			outer = find(outer.getPosition() + 1);
		}
		inner.setPosition(inner.getPosition() - 1);
	}

	public Block find(int pos)
	{
		return find(pos, root);
	}
	private Block find(int pos, Layer node)
	{
		if (node instanceof Block)
		{
			Block blk = (Block)node;
			return blk.getPosition() == pos ? blk : null;
		}
		
		for (Layer l : node.children())
		{
			Block blk = find(pos, l);
			if (blk != null) { return blk; }
		}

		return null;
	}

	private void delete(int pos)
	{
		delete(pos, root);
	}
	private void delete(int pos, Layer node)
	{
		if (node instanceof Block) { return; }
		for (Layer child : node.children())
		{
			if (child instanceof Block)
			{
				Block blk = (Block) child;
				if (blk.getPosition() == pos) { node.remove(child); }
			}
			else
			{
				delete(pos, child);
			}
		}
	}
	private Layer grabLayer(Block blk)
	{
		return grabLayer(blk, root);
	}
	private Layer grabLayer(Block blk, Layer parent)
	{
		if (parent.contains(blk)) { return parent; }

		for (Layer child : parent.children())
		{
			Layer value = grabLayer(blk, child);
			if (value != null) { return value; }
		}
		return null;
	}

	private boolean isSign(String s) { return s.length() == 1 ? isSign(s.charAt(0)) : false; }
	private boolean isSign(char c)
	{
		return c == '=' || c == '+' || c == '-' || c == '*' || c == '/';
	}
	private boolean isNum(String s) { return s.length() == 1 ? isNum(s.charAt(0)) : false; }
	private boolean isNum(char c)
	{
		return	c == '0' ||
				c == '1' ||
				c == '2' ||
				c == '3' ||
				c == '4' ||
				c == '5' ||
				c == '6' ||
				c == '7' ||
				c == '8' ||
				c == '9';
	}
	private Layer createLayer(String sign)
	{
		char c = sign.charAt(0);
		switch (c)
		{
			case '+': return new AddLayer();
//			case '*': return new MulLayer();
			case '=': return new EqLayer();
		}
		return null;
	}
};
