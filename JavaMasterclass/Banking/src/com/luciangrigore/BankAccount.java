package com.luciangrigore;

public class BankAccount {

    private String firstName;
    private String lastName;
    private double balance;

    public static final int CHEKING = 1;
    public static final int SAVING = 2;
    private int accountType;

    public BankAccount(String firstName, String lastName, double balance, int typeOfAccount) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.balance = balance;
        this.accountType = typeOfAccount;
    }

    //  branch = true if the customer is performing the transaction at a branch,
    //  with a teller
    //  branch = false if the transaction takes place at an ATm
    public double deposit(double amount, boolean branch) {
        balance += amount;
        return balance;
    }

    //  branch = true if the customer is performing the transaction at a branch,
    //  with a teller
    //  branch = false if the transaction takes place at an ATm
    public double withdraw(double amount, boolean branch) {
        if ((amount > 500) && !branch) {
            throw new IllegalArgumentException();
        }
        balance -= amount;
        return balance;
    }

    public double getBalance() {
        return balance;
    }

    public boolean isChecking() {
        return accountType == CHEKING;
    }

    //  more methods that use firstName, lastName, and perform other actions
}
