package com.company;

import java.util.Scanner;

public class Main {

    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {

        int[] A = getIntegers(5);
        A = sortArray(A);
        printArray(A);

    }

    public static int[] getIntegers(int number) {

        int[] array = new int[number];
        System.out.println("Enter your " + number + " numbers:");

        for (int i = 0; i < array.length; i++) {
            array[i] = scanner.nextInt();
            scanner.nextLine();
        }

        return array;
    }

    public static void printArray(int[] array) {

        System.out.println("The elements of the given array are");

        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i] + " ");
        }

    }

    public static int[] sortArray(int[] array) {

//        for (int i = 0; i < array.length - 1; i++) {
//            if (array[i] < array[i + 1]) {
//                int switchValue = array[i];
//                array[i] = array[i + 1];
//                array[i + 1] = switchValue;
//            }
//        }

        boolean swapped;
        for (int i = 0; i < array.length - 1; i++)
        {
            swapped = false;
            for (int j = 0; j < array.length - i - 1; j++)
            {
                if (array[j] < array[j + 1])
                {
                    // swap arr[j] and arr[j+1]
                    int temp;
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    swapped = true;
                }
            }

            // IF no two elements were
            // swapped by inner loop, then break
            if (swapped == false)
                break;
        }

        //      sunt un bou
        return array;
    }
}
