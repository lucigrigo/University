package com.company;

public class Main {

    public static void main(String[] args) {
        // 8 primitive data types in java = int, short, byte, long, float, double, char, boolean
        // + STRING ( 9th )
        String myString = " This is a String ! ";
        System.out.println(myString);
        myString = myString + " And it's fun ! ";
        System.out.println(myString);
        myString = myString + " \u00A9 2019 ";
        System.out.println(myString);

        String numberString = "250.55";
        numberString = numberString + " 49.95";
        System.out.println(numberString);

        String lastString = "10";
        int myInt = 50;
        lastString = lastString + myInt;
        System.out.println(lastString);
        double doubleNumber = 120.47d;
        lastString = lastString + doubleNumber;
        System.out.println(lastString);
    }
}
