package lucian.grigore.algorithm.euclid;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class EuclidTest {

    private Euclid e = null;

    @Before
    public void init() {
        e = new Euclid();
    }

    @Test
    public void gcdTest() {
        Assert.assertEquals(2, e.gcd(22, 6));
        Assert.assertEquals(2, e.gcd(10, 2));
    }

    @Test
    public void gcd2Test() {
        Assert.assertEquals(2, e.gcd2(22, 6));
        Assert.assertEquals(2, e.gcd2(10, 2));
    }

    @Test
    public void gcdVsgcd2Test() {
        Assert.assertEquals(e.gcd(22, 6), e.gcd2(22, 6));
        Assert.assertEquals(e.gcd(182, 23), e.gcd2(182, 23));
    }
}
