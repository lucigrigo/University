package lucian.grigore.algorithm.boyermoore;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class BoyerMooreTest {

    private BoyerMoore b;

    @Before
    public void init() {
        b = new BoyerMoore();
    }

    @Test
    public void isPrefixTest() {
        Assert.assertFalse(b.isPrefix("baibai".toCharArray(), 1));
        Assert.assertFalse(b.isPrefix("baibai".toCharArray(), 2));
        Assert.assertTrue(b.isPrefix("baibai".toCharArray(), 3));
        Assert.assertFalse(b.isPrefix("baibai".toCharArray(), 4));
        Assert.assertFalse(b.isPrefix("baibai".toCharArray(), 5));
        Assert.assertTrue(b.isPrefix("baibai".toCharArray(), 6));

        Assert.assertFalse(b.isPrefix("baidai".toCharArray(), 1));
        Assert.assertFalse(b.isPrefix("baidai".toCharArray(), 2));
        Assert.assertFalse(b.isPrefix("baidai".toCharArray(), 3));
        Assert.assertFalse(b.isPrefix("baidai".toCharArray(), 4));
        Assert.assertFalse(b.isPrefix("baidai".toCharArray(), 5));
        Assert.assertTrue(b.isPrefix("baidai".toCharArray(), 6));
    }

    @Test
    public void suffixLengthTest() {
        Assert.assertEquals(2, b.suffixLength("baidai".toCharArray(), 2));
        Assert.assertEquals(3, b.suffixLength("kaikai".toCharArray(), 2));
        Assert.assertEquals(1, b.suffixLength("mytestmytest".toCharArray(), 2));
        Assert.assertEquals(6, b.suffixLength("mytestmytest".toCharArray(), 5));
    }

    @Test
    public void computePrefixTest() {
        int[] table = new int[6];
        b.computePrefix("baidai".toCharArray(), table);
        Assert.assertArrayEquals(new int[]{6, 7, 8, 9, 10, 11}, table);
    }

    @Test
    public void computeSuffixTest() {
        int[] table = new int[6];
        b.computeSuffix("baidai".toCharArray(), table);
        Assert.assertArrayEquals(new int[]{1, 0, 5, 0, 0, 0}, table);
    }

    @Test
    public void preprocessSuffixTableTest() {
        int[] table = b.preprocessSuffixTable("baidai".toCharArray());
        Assert.assertArrayEquals(new int[]{1, 7, 5, 9, 10, 11}, table);
    }

    @Test
    public void searchTest() {
        Assert.assertEquals(14, b.search("thisisour firsttest".toCharArray(), "tt".toCharArray()));
        Assert.assertEquals(6, b.search("abcdbabaidai".toCharArray(), "baidai".toCharArray()));
        Assert.assertEquals(0, b.search("abcdbabaidai".toCharArray(), "a".toCharArray()));
        Assert.assertEquals(0, b.search("abcdbabaidai".toCharArray(), "ab".toCharArray()));
        Assert.assertEquals(1, b.search("abcdbabaidai".toCharArray(), "b".toCharArray()));
        Assert.assertEquals(9, b.search("abcdbabaidai".toCharArray(), "dai".toCharArray()));
        Assert.assertEquals(3, b.search("asdz".toCharArray(), "z".toCharArray()));
        Assert.assertEquals(0, b.search("asdz".toCharArray(), "".toCharArray()));
        Assert.assertEquals(0, b.search("asdz".toCharArray(), null));
        Assert.assertEquals(-1, b.search(null, "z".toCharArray()));
        Assert.assertEquals(-1, b.search("abcdbabaidai".toCharArray(), "baidaiz".toCharArray()));

    }
}
