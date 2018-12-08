package com.company;

import java.util.ArrayList;

public class Customer {
    private ArrayList<Double> transactions = new ArrayList<Double>();
    private String name;

    public Customer() {
        this.name = null;
        this.transactions = new ArrayList<Double>();
    }

    public Customer(String name, double initialAmount) {
        this.name = name;
        this.transactions = new ArrayList<Double>();
        transactions.add(initialAmount);
    }

    public void addTransaction(double amount) {
        this.transactions.add(amount);
    }

    public ArrayList<Double> getTransactions() {
        return transactions;
    }

    public String getName() {
        return name;
    }

    public void printTransactions() {
        for (int i = 0; i < this.transactions.size(); i++) {
            System.out.println("#" + (i + 1) + " " + this.transactions.get(i));
        }
    }

}
