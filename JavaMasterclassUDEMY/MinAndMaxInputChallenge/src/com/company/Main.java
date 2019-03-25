package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s;
        int min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;
        System.out.println("Type the numbers");
        while (true) {
            boolean hasNextInt = scanner.hasNextInt();
            if (hasNextInt) {
                int a = scanner.nextInt();
                if (a > max) {
                    max = a;
                }
                if (a < min) {
                    min = a;
                }
                scanner.nextLine();
            } else {
                break;
            }
        }

        System.out.println("The maximum number was " + max);
        System.out.println("The minimum number was " + min);
    }
}
