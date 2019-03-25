package com.luciangrigore;

public class Main {

    public static int multiplier = 7;

    public static void main(String[] args) {

//        StaticTest firstInstance = new StaticTest("First instance");
//        System.out.println(firstInstance.getName() + " is instance number " +
//                StaticTest.getNumInstances());
//
//        StaticTest secondInstance = new StaticTest("Second instance");
//        System.out.println(secondInstance.getName() + " is instance number " +
//                StaticTest.getNumInstances());
//
//        StaticTest thirdInstance = new StaticTest("Third instance");
//        System.out.println(thirdInstance.getName() + " is instance number " +
//                StaticTest.getNumInstances());

        //  java com.company_static.Main

        int answer = multiply(6);
        System.out.println("The answer is " + answer);
        System.out.println("Multiplier is " + multiplier);
    }

    public static int multiply(int x) {
        return x * multiplier;
    }
}
