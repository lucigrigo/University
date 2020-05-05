package com.oop_pub.exceptions.ex2_3;

import java.util.List;

public class MainEx2 {
    public static void main(String[] args) {
        // TODO: Initialize the calculator
        DoubleCalc calculator = new DoubleCalc();

        System.out.println(calculator.add(2d, 3d));
        System.out.println(calculator.divide(9d, 4d));
        System.out.println(calculator.average(List.of(1d, 2d, 3d, 4d)));

        // TODO: Test edge cases that would throw exceptions

//        System.out.println(calculator.add(5d, null));
//        System.out.println(calculator.add(10d, Double.POSITIVE_INFINITY));
//        System.out.println(calculator.add(-1d, Double.NEGATIVE_INFINITY));

//        System.out.println(calculator.divide(2d, null));
        System.out.println(calculator.divide(2d, 0d));

//        System.out.println(calculator.average(List.of(2d, 3d, 5d, null)));

        // EX 3
        // Alegerea fireasca ar trebui sa fie exceptii checked astfel incat desfasurarea
        // de calcule executate de un utilizator sa nu fie intrerupta in cazul unui input gresit.
    }
}
