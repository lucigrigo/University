package com.luciangrigore;

import java.util.ArrayList;

public class Account {

    private String accountName;
    private double balance = 0;
    private ArrayList<Double> transactions;

    public Account(String accountName) {
        this.accountName = accountName;
        this.transactions = new ArrayList<Double>();
    }

    public double getBalance() {
        return balance;
    }

    public void deposit(double amount) {
        if (amount > 0) {
            this.transactions.add(amount);
            this.balance += amount;
            System.out.println(amount + " deposited . Balance is now " +
                    this.balance);
        } else {
            System.out.println("Cannot deposit negative sums!");
        }
    }

    public void withdraw(double amount) {
        if (amount > 0) {
            this.transactions.add((-1) * amount);
            this.balance -= amount;
            System.out.println(amount + " withdrawn . Balance is now " +
                    this.balance);
        } else {
            System.out.println("Cannot withdraw negative sums!");
        }
    }

    public void calculateBalance() {
        this.balance = 0;
        for (double i : this.transactions) {
            this.balance += i;
        }
        System.out.println("Calculated balance is " + this.balance);
    }
}
