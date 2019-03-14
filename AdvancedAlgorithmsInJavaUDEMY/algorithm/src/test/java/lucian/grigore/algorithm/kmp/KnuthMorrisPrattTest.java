package lucian.grigore.algorithm.kmp;

import org.junit.Assert;
import org.junit.Test;

public class KnuthMorrisPrattTest {

    @Test
    public void computeLSPTableTest() {
        KnuthMorrisPratt knuthMorrisPratt = new KnuthMorrisPratt();

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
}
