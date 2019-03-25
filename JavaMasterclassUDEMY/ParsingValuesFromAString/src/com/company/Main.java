package com.company;

public class Main {

    public static void main(String[] args) {
        String myStringNumber = "2018";
        String myDoubleStringNumber = "2017.2993";
        System.out.println("Number as string = " + myStringNumber);
        System.out.println("Double number as a string =" + myDoubleStringNumber);

        int myIntNumber = Integer.parseInt(myStringNumber);
        System.out.println(myIntNumber + " as an int");

        double myDoubleNumber = Double.parseDouble(myDoubleStringNumber);
        System.out.println(myDoubleNumber + " as a double");

    }

}
