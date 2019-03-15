package lucian.grigore.algorithm.boyermoore;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class BoyerMooreHorspoolTest {

    BoyerMooreHorspool bm = null;

    @Before
    public void init() {
        bm = new BoyerMooreHorspool();
    }

    @Test
    public void searchTest() {
        Assert.assertEquals(4, bm.search("learning".toCharArray(), "nin".toCharArray()));
        Assert.assertEquals(7, bm.search("learning".toCharArray(), "g".toCharArray()));
        Assert.assertEquals(6, bm.search("learning".toCharArray(), "ng".toCharArray()));
        Assert.assertEquals(0, bm.search("learning".toCharArray(), "l".toCharArray()));
        Assert.assertEquals(0, bm.search("learning".toCharArray(), "le".toCharArray()));
        Assert.assertEquals(0, bm.search("learning".toCharArray(), "learning".toCharArray()));
        Assert.assertEquals(5, bm.search("learning".toCharArray(), "in".toCharArray()));
        Assert.assertEquals(-1, bm.search("learning".toCharArray(), "x".toCharArray()));
        Assert.assertEquals(0, bm.search("learning".toCharArray(), null));
        Assert.assertEquals(-1, bm.search(null, "abc".toCharArray()));
        Assert.assertEquals(0, bm.search(null, null));
    }

    @Test
    public void preprocessTableTest() {
        int[] table = bm.preprocessTable("test".toCharArray());
        Assert.assertEquals(1, table['t']);
        Assert.assertEquals(2, table['e']);
        Assert.assertEquals(1, table['s']);
        Assert.assertEquals(4, table['x']);

        table = bm.preprocessTable("abc".toCharArray());
        Assert.assertEquals(2, table['a']);
        Assert.assertEquals(1, table['b']);
        Assert.assertEquals(3, table['c']);
        Assert.assertEquals(3, table['g']);

        table = bm.preprocessTable("abcdb".toCharArray());
        Assert.assertEquals(4, table['a']);
        Assert.assertEquals(1, table['b']);
        Assert.assertEquals(2, table['c']);
        Assert.assertEquals(1, table['d']);
        Assert.assertEquals(5, table['j']);
    }
}
