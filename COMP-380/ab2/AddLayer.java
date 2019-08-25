package algebrablocks;

import java.lang.IllegalArgumentException;
import algebrablocks.Layer;

public class AddLayer extends Layer
{
	public void merge(Block dest, Block src) throws IllegalArgumentException
	{
		if (!contains(dest) || !contains(src))
		{ throw new IllegalArgumentException("Blocks must be in this layer to merge"); }

		dest.setTerm(dest.getTerm().add(src.getTerm()));
		remove(src);
	}
};
