package lucian.grigore.algorithm.utils;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class SimpleUtilsTest {

    private SimpleUtils simpleUtils = null;

    @Before
    public void init() {
        simpleUtils = new SimpleUtils();
    }

    @Test
    public void stringToBooleanFalseTest() {
        Assert.assertFalse(simpleUtils.stringToBoolean("n"));
        Assert.assertFalse(simpleUtils.stringToBoolean("N"));
        Assert.assertFalse(simpleUtils.stringToBoolean("No"));
        Assert.assertFalse(simpleUtils.stringToBoolean("nO"));
        Assert.assertFalse(simpleUtils.stringToBoolean("FalSE"));
        Assert.assertFalse(simpleUtils.stringToBoolean("fALSe"));
        Assert.assertFalse(simpleUtils.stringToBoolean("NO"));
        Assert.assertFalse(simpleUtils.stringToBoolean("FALSE"));
        Assert.assertFalse(simpleUtils.stringToBoolean(null));
    }

    @Test
    public void stringToBooleanTrueTest() {
        Assert.assertTrue(simpleUtils.stringToBoolean("testingg"));
        Assert.assertTrue(simpleUtils.stringToBoolean("y"));
        Assert.assertTrue(simpleUtils.stringToBoolean("YES"));
        Assert.assertTrue(simpleUtils.stringToBoolean("KO"));
        Assert.assertTrue(simpleUtils.stringToBoolean("falss"));
    }

    @Test
    public void getFileTypeByCodeTest() {
        Assert.assertEquals(SimpleUtils.FileType.PDF, simpleUtils.getFileTypeByCode(3));
        Assert.assertEquals(SimpleUtils.FileType.JPEG, simpleUtils.getFileTypeByCode(1));
        Assert.assertNull(simpleUtils.getFileTypeByCode(999));
    }

    @Test
    public void getFileTypeByNameTest() {
        Assert.assertEquals(SimpleUtils.FileType.TEXT, simpleUtils.getFileTypeByName("text"));
        Assert.assertNull(simpleUtils.getFileTypeByName("alabala"));
        Assert.assertNull(simpleUtils.getFileTypeByName(null));
    }
}
