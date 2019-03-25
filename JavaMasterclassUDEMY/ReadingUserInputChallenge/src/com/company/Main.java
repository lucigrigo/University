package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        int sum = 0;
        System.out.println("Type 10 numbers:");
        for (int i = 0; i < 10;) {
            Scanner scanner = new Scanner(System.in);
            boolean hasNextInt = scanner.hasNextInt();
            if (hasNextInt) {
                int a = scanner.nextInt();
                sum += a;
                scanner.nextLine();
                i++;
            } else {
                System.out.println("Invalid Value");
            }
        }

        System.out.println("The sum of the 10 numbers is " + sum);
    }
}
