import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertArrayEquals;
import org.junit.Test;

public class LinkedListTest {
    // TODO: write tests for getElementAt, length, and toArray

    
    @Test
    public void testMysteryLength0() {
        final LinkedList list = new LinkedList();
        list.mysteryOperation();
        assertArrayEquals(new int[0], list.toArray());
    }

    @Test
    public void testMysteryLength1() {
        final LinkedList list = new LinkedList();
        list.addFront(1);
        list.mysteryOperation();
        assertArrayEquals(new int[]{ 1 }, list.toArray());
    }

    @Test
    public void testMysteryLength2() {
        final LinkedList list = new LinkedList();
        list.addFront(2);
        list.addFront(1);
        list.mysteryOperation();
        assertArrayEquals(new int[]{ 2, 1 }, list.toArray());
    }

    @Test
    public void testMysteryLength3() {
        final LinkedList list = new LinkedList();
        list.addFront(3);
        list.addFront(2);
        list.addFront(1);
        list.mysteryOperation();
        assertArrayEquals(new int[]{ 3, 2, 1 }, list.toArray());
    }
}
