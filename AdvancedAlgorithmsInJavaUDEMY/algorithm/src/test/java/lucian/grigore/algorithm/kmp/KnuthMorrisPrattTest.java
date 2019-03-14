package lucian.grigore.algorithm.kmp;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class KnuthMorrisPrattTest {

    private KnuthMorrisPratt knuthMorrisPratt = null;

    @Before
    public void init() {
        knuthMorrisPratt = new KnuthMorrisPratt();
    }

    @Test
    public void computeLSPTableTest() {
        String s = "ababac";
        int[] actual = knuthMorrisPratt.computeLSPTable(s.toCharArray());
        int[] expect = new int[]{0, 0, 1, 2, 3, 0};
        Assert.assertArrayEquals(expect, actual);

        s = "aabac";
        actual = knuthMorrisPratt.computeLSPTable(s.toCharArray());
        expect = new int[]{0, 1, 0, 1, 0};
        Assert.assertArrayEquals(expect, actual);

        s = "abcdeabca";
        actual = knuthMorrisPratt.computeLSPTable(s.toCharArray());
        expect = new int[]{0, 0, 0, 0, 0, 1, 2, 3, 1};
        Assert.assertArrayEquals(expect, actual);

        s = "cfgcfa";
        actual = knuthMorrisPratt.computeLSPTable(s.toCharArray());
        expect = new int[]{0, 0, 0, 1, 2, 0};
        Assert.assertArrayEquals(expect, actual);

        s = "aabacaz";
        actual = knuthMorrisPratt.computeLSPTable(s.toCharArray());
        expect = new int[]{0, 1, 0, 1, 0, 1, 0};
        Assert.assertArrayEquals(expect, actual);

        s = "a";
        actual = knuthMorrisPratt.computeLSPTable(s.toCharArray());
        expect = new int[]{0};
        Assert.assertArrayEquals(expect, actual);

        s = "aa";
        actual = knuthMorrisPratt.computeLSPTable(s.toCharArray());
        expect = new int[]{0, 1};
        Assert.assertArrayEquals(expect, actual);

        s = "ab";
        actual = knuthMorrisPratt.computeLSPTable(s.toCharArray());
        expect = new int[]{0, 0};
        Assert.assertArrayEquals(expect, actual);
    }

    @Test
    public void searchTest() {
        String pattern = "ababac";
        String array = "abazacabababac";
        int index = knuthMorrisPratt.search(array.toCharArray(), pattern.toCharArray());
        Assert.assertEquals(8, index);

        pattern = "aabacaz";
        array = "aabaaabacaz";
        index = knuthMorrisPratt.search(array.toCharArray(), pattern.toCharArray());
        Assert.assertEquals(4, index);

        pattern = "is a";
        array = "this is a test";
        index = knuthMorrisPratt.search(array.toCharArray(), pattern.toCharArray());
        Assert.assertEquals(5, index);

        pattern = "foo";
        array = "can'tfindthetest";
        index = knuthMorrisPratt.search(array.toCharArray(), pattern.toCharArray());
        Assert.assertEquals(-1, index);
    }
}
