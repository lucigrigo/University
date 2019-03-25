package com.company;

import java.util.Scanner;

public class Main {

    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int[] myIntegers = getIntegers(5);

        System.out.println("The elements are");
        for (int i = 0; i < myIntegers.length; i++) {
            System.out.print(myIntegers[i] + " ");
        }
        System.out.println();

        System.out.println("Average value is");
        System.out.println(getAverage(myIntegers));
    }

    public static int[] getIntegers(int max) {
        System.out.println("Enter " + max + " int values:\r");
        int[] values = new int[max];

        for (int i = 0; i < values.length; i++) {
            values[i] = scanner.nextInt();
            scanner.nextLine();
        }

        return values;
    }

    public static double getAverage(int[] array) {
        int sum = 0;
        for (int i = 0; i < array.length; i++) {
            sum += array[i];
        }
        sum /= array.length;
        return sum;
    }
}
