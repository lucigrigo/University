package com.company;

public class Main {

    public static void main(String[] args) {

        for (int i = 8; i >= 2; i--) {
            System.out.println(String.format("%.2f", calculateInterest(10000, i)));
        }

        //      CHALLENGE

        int primeNumber = 0;
        for (int i = 1231; i <= 10000; i++) {
            if (isPrime(i)) {
                System.out.println(i);
                primeNumber++;
            }
            if (primeNumber == 10) {
                System.out.println("10 prime numbers found! exiting...");
                break;
            }
        }
    }

    public static double calculateInterest(double amount, double interestRate) {
        return (amount * (interestRate / 100));
    }

    public static boolean isPrime(int n) {
        if (n == 1) {
            return false;
        }
        for (int i = 2; i < Math.sqrt(n); i++)
            if (n % i == 0) {
                return false;
            }
        return true;
    }
}
