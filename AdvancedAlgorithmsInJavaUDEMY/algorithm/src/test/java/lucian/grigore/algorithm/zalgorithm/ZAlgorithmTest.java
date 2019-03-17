package lucian.grigore.algorithm.zalgorithm;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class ZAlgorithmTest {

    ZAlgorithm z;

    @Before
    public void init() {
        z = new ZAlgorithm();
    }

    @Test
    public void createLongStringTest() {
        Assert.assertArrayEquals("abc$edfabc".toCharArray(), z.createLongString("abc".toCharArray(), "edfabc".toCharArray()));
    }

    @Test
    public void createZTableTest() {
        // ab$aabb
        // 0001200
        Assert.assertArrayEquals(new int[]{0, 0, 0, 1, 2, 0, 0}, z.createZTable("ab".toCharArray(), "aabb".toCharArray()));
    }

    @Test
    public void searchTest() {
        Assert.assertEquals(-1, z.search("cc".toCharArray(), "dfabfabds".toCharArray()));
        Assert.assertEquals(2, z.search("ab".toCharArray(), "dfabfabds".toCharArray()));
        Assert.assertEquals(12, z.search("name".toCharArray(), "I knew your name already.".toCharArray()));
    }

    @Test
    public void searchAllTest() {
        Assert.assertArrayEquals(new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0}, z.searchAll("cc".toCharArray(), "dfabfabds".toCharArray()));
        Assert.assertArrayEquals(new int[]{0, 0, 2, 0, 0, 2, 0, 0, 0}, z.searchAll("ab".toCharArray(), "dfabfabds".toCharArray()));
        Assert.assertArrayEquals(new int[]{0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0}, z.searchAll("name".toCharArray(), "My name is my name.".toCharArray()));
    }
}
