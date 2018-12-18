package com.example.PackageChallenge;

public class Series {

    public long nSum(int n) {
        long sum = 0;
        for (int i = 0; i <= n; i++) {
            sum += i;
        }
        return sum;
    }

    public long fibonacci(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 1;
        }
        return (fibonacci(n - 1) + fibonacci(n - 2));
    }

    public long factorial(int n) {
        long prod = 1;
        if (n == 0) {
            return 0;
        } else {
            for (int i = 1; i <= n; i++) {
                prod *= i;
            }
            return prod;
        }
    }
}
