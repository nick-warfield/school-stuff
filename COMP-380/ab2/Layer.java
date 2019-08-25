package algebrablocks;

import java.util.Vector;
import algebrablocks.Term;

public abstract class Layer
{
	private Vector<Layer> m_children;

	public Layer() { m_children = new Vector<Layer>(); }

	public abstract void merge(Block dest, Block src);

	public Vector<Layer> children() { return m_children; }
	public void remove(Layer child) { m_children.remove(child); }
	public void add(Layer child) { m_children.add(child); }
	public boolean contains(Layer child) { return m_children.contains(child); }
};
