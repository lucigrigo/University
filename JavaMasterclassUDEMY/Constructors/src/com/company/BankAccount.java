package com.company;

public class BankAccount {
    private int accountNumber, balance;
    private String email, phoneNumber, customerName;

    public BankAccount(){
        this(0,0,"noEmailGiven",
                "noPhoneNumberGiven","noNameGiven");
        System.out.println("Empty constructor called");
    }

    public BankAccount(int accountNumber, int balance, String email,
                       String phoneNumber, String customerName) {
        this.balance = balance;
        this.accountNumber = accountNumber;
        this.email = email;
        this.phoneNumber = phoneNumber;
        this.customerName = customerName;

        System.out.println("Welcome to our bank, " + customerName);
    }

    public void setAccountNumber(int accountNumber) {
        this.accountNumber = accountNumber;
    }

    public void setBalance(int balance) {
        this.balance = balance;
    }

    public void setEmail(String emailGiven) {
        this.email = emailGiven;
    }

    public void setPhoneNumber(String phoneGiven) {
        this.phoneNumber = phoneGiven;
    }

    public void setCustomerName(String nameGiven) {
        this.customerName = nameGiven;
    }

    public int getAccountNumber() {
        return accountNumber;
    }

    public int getBalance() {
        return balance;
    }

    public String getEmail() {
        return email;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public String getCustomerName() {
        return customerName;
    }

    public void depositFunds(int moneyDeposited) {
        this.balance += moneyDeposited;
        System.out.println("Money deposited succesfully!");
        System.out.println("Current balance are " + this.balance);
    }

    public void withdrawFunds(int moneyWithdrawn) {
        if ((this.balance - moneyWithdrawn) < 0) {
            System.out.println("Not enough funds!");
            System.out.println("Current funds are " + this.balance);
        } else {
            this.balance -= moneyWithdrawn;
            System.out.println("Withdraw succeded!");
            System.out.println("Remaining funds are " + this.balance);
        }

    }
}
