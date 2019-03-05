package com.luciangrigore;

import jdk.jshell.execution.Util;

import java.util.Arrays;

import static org.junit.Assert.*;

public class UtilitiesTest {

    private static Utilities utils;

    @org.junit.BeforeClass
    public static void setup() {
        utils = new Utilities();
    }

    @org.junit.Test
    public void everyNthChar() {
//        fail("this has yet to be completed");
//        Utilities utils = new Utilities();
        assertArrayEquals(new char[]{'e', 'l'}, utils.everyNthChar(new char[]
                {'h', 'e', 'l', 'l', 'o'}, 2));
        assertArrayEquals(new char[]{'h', 'e', 'l', 'l', 'o'}, utils.everyNthChar(new char[]
                {'h', 'e', 'l', 'l', 'o'}, 10));
    }

    @org.junit.Test
    public void removePairs() {
//        fail("this has yet to be completed");
//        Utilities utils = new Utilities();

        String input1 = "AABCDDEFF";
        String output1 = utils.removePairs(input1);

        String input2 = "ABCCABDEEF";
        String output2 = utils.removePairs(input2);

        assertEquals("ABCDEF", output1);
        assertEquals("ABCABDEF", output2);

        //  additional tests
        assertNull(null, utils.removePairs(null));
        assertEquals("A", utils.removePairs("A"));
        assertEquals("", utils.removePairs(""));
    }

    @org.junit.Test(expected = ArithmeticException.class)
    public void converter() {
//        fail("this has yet to be completed");
//        Utilities utils = new Utilities();
        assertEquals(300, utils.converter(10, 5));
        //  throws arithmetic exception (divide by 0)
        assertEquals(3000, utils.converter(10, 0));
    }

    @org.junit.Test
    public void nullIfOddLength() {
//        fail("this has yet to be completed");
//        Utilities utils = new Utilities();
        assertEquals("abcdefgh", utils.nullIfOddLength("abcdefgh"));
        assertNull(utils.nullIfOddLength("abc"));
    }
}