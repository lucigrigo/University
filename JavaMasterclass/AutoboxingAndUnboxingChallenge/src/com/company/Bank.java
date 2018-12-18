package com.company;

import java.util.ArrayList;

public class Bank {
    private ArrayList<Branch> branches = new ArrayList<Branch>();
    private String name;

    public Bank(String name) {
        this.name = name;
        this.branches = new ArrayList<Branch>();
    }

    public void addBranch(String name) {
        this.branches.add(new Branch(name));
    }

    public boolean printCustomers(String name) {
        for (int i = 0; i < branches.size(); i++) {
            Branch currentBranch = this.branches.get(i);
            if (currentBranch.getName().equals(name)) {
                currentBranch.printCustomers();
                return true;
            }
        }
        return false;
    }

    public boolean addCustomer(String name, String branchName, double amount) {
        for (int i = 0; i < this.branches.size(); i++) {
            Branch currentBranch = this.branches.get(i);
            if (currentBranch.getName().equals(branchName)) {
                currentBranch.newCustomer(name, amount);
                return true;
            }
        }
        return false;
    }

    public boolean addTransaction(String name, String branchName, double amount) {
        for (int i = 0; i < this.branches.size(); i++) {
            Branch currentBranch = this.branches.get(i);
            if (currentBranch.getName().equals(branchName)) {
                currentBranch.addCustomerTransaction(name, amount);
                return true;
            }
        }
        return false;
    }

    public boolean printCustomersAndTransactions(String branchName) {
        for (int i = 0; i < this.branches.size(); i++) {
            Branch currentBranch = this.branches.get(i);
            if (currentBranch.getName().equals(branchName)) {
                currentBranch.printCustomersAndTransactions();
                return true;
            }
        }
        return false;
    }
}
