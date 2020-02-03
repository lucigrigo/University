package com.company.gril;

public class SampleClass {

    public int nr_ord = 55;
    public static double con = 2.0d;

    public static void doStuff() {
        System.out.println("i'm doing it");
    }

    public void doSS() {
        System.out.println("ss");
    }

    public static class Ext extends SampleClass{

        public void doSmth() {
            super.doSS();
            super.nr_ord = 100;

            SampleClass.doStuff();
        }
    }
}
