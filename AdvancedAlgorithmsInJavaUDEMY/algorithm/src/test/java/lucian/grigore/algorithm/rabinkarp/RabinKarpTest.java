package lucian.grigore.algorithm.rabinkarp;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class RabinKarpTest {

    private RabinKarp rk = null;

    @Before
    public void init() {
        rk = new RabinKarp();
    }

    @Test
    public void searchTest() {
        Assert.assertEquals(3, rk.search("acbacc".toCharArray(), "acc".toCharArray()));
        Assert.assertEquals(4, rk.search("learning".toCharArray(), "nin".toCharArray()));
        Assert.assertEquals(-1, rk.search("learning".toCharArray(), "nina".toCharArray()));
        Assert.assertEquals(0, rk.search("learning".toCharArray(), "le".toCharArray()));
        Assert.assertEquals(0, rk.search("learning".toCharArray(), "l".toCharArray()));
        Assert.assertEquals(5, rk.search("learning".toCharArray(), "ing".toCharArray()));
        Assert.assertEquals(5, rk.search("learning".toCharArray(), "in".toCharArray()));
        Assert.assertEquals(6, rk.search("learning".toCharArray(), "ng".toCharArray()));
        Assert.assertEquals(7, rk.search("learning".toCharArray(), "g".toCharArray()));
        Assert.assertEquals(-1, rk.search("learning".toCharArray(), null));
        Assert.assertEquals(-1, rk.search(null, "ing".toCharArray()));
        Assert.assertEquals(-1, rk.search(null, null));
        Assert.assertEquals(-1, rk.search(null, null));
    }

    @Test
    public void matchTest() {
        Assert.assertTrue(rk.match("learning".toCharArray(), "nin".toCharArray(), 4));
        Assert.assertTrue(rk.match("learning".toCharArray(), "le".toCharArray(), 0));
        Assert.assertTrue(rk.match("learning".toCharArray(), "g".toCharArray(), 7));

        Assert.assertFalse(rk.match("learning".toCharArray(), "ing".toCharArray(), 4));
        Assert.assertFalse(rk.match("learning".toCharArray(), "l".toCharArray(), 1));
    }

    @Test
    public void calculateHashTest() {
        Assert.assertEquals(28L, rk.calculateHash("acbacc".toCharArray(), 3));
    }

    @Test
    public void recalculateHashTest() {
        Assert.assertEquals(18L, rk.recalculateHash(28L, 'a', 'a', 3));
    }

    @Test
    public void characterValueTest() {
        Assert.assertEquals(97, (int) 'a');
        Assert.assertEquals(1, rk.characterValue('a'));
    }
}
