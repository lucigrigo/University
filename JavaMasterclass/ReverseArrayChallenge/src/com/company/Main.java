package com.company;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        int[] array = new int[]{1, 2, 3, 4, 5};
        System.out.println("Initial array was " + Arrays.toString(array));
        reverse(array);
        System.out.println("Final array is " + Arrays.toString(array));
    }

    public static void reverse(int[] array) {
        for (int i = 0; i < array.length / 2; i++) {
            int copy = array[i];
            array[i] = array[array.length - i - 1];
            array[array.length - i - 1] = copy;
        }
    }
}
