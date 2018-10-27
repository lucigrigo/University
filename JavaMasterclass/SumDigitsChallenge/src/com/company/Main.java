package com.company;

public class Main {

    public static void main(String[] args) {
        System.out.println(sumDigits(125));
        System.out.println(sumDigits(2));
        System.out.println(sumDigits(129837));
        System.out.println(sumDigits(-100));

    }

    public static int sumDigits(int n) {
        if (n < 10) {
            return -1;
        } else {
            int sum = 0;
            while (n != 0) {
                sum += (n % 10);
                n /= 10;
            }
            return sum;
        }
    }
}

