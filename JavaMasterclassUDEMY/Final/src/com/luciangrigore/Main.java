package com.luciangrigore;

public class Main {

    public static void main(String[] args) {

////        SomeClass one = new SomeClass("One");
////        SomeClass two = new SomeClass("Two");
////        SomeClass three = new SomeClass("Three");
////
////        System.out.println(one.getInstanceNumber());
////        System.out.println(two.getInstanceNumber());
////        System.out.println(three.getInstanceNumber());
//
////        one.instanceNumber = 4;   ->  error
//
////        System.out.println(Math.PI);
////        Math m = new Math();  ->  error
//
//        int pw = 674312;
//        ExtendedPassword password = new ExtendedPassword(pw);
//        password.storePassword();
//
//        password.letMeIn(1);
//        password.letMeIn(523266);
//        password.letMeIn(12355);
//        password.letMeIn(-1);
//        password.letMeIn(0);
//        password.letMeIn(pw);

        System.out.println("Main method called !");
        SIBTest test = new SIBTest();
        test.someMethod();
        System.out.println("Owner is " + SIBTest.owner);
    }
}
