package com.luciangrigore;

public class ScopeCheck {

    public int publicVar = 0;
    private int varOne = 1;

    public ScopeCheck() {
        System.out.println("ScopeCheck created!\n" +
                "publicVar=" + publicVar + '\n' +
                "varOne=" + varOne);
    }

    public int getVarOne() {
        return varOne;
    }

    public void timesTwo() {
        int varTwo = 2;
        for (int i = 0; i < 10; i++) {
            System.out.println(i + " times two is " + i * this.varOne);
        }
    }

    public void useInner() {
        innerClass innerClass = new innerClass();
        System.out.println("varThree from outer class is " + innerClass.varThree);
    }

    public class innerClass {

        private int varThree = 3;

        public innerClass() {
            System.out.println("Inner class created!\n" +
                    "varThree=" + varThree);
            System.out.println("varOne=" + varOne);
        }

        public void timesTwo() {
            int privateVar = 2;
            System.out.println("varOne is still available here = " + varOne);
            for (int i = 0; i < 10; i++) {
                System.out.println(i + " times two is " + i * privateVar);
            }
        }
    }
}
