package com.company;

import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;

public class Branch {
    private ArrayList<Customer> customers;
    private String name;

    public Branch(String name) {
        this.customers = new ArrayList<Customer>();
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public boolean newCustomer(String name, double inAmount) {
        if (findCustomer(name) == null) {
            this.customers.add(new Customer(name, inAmount));
            return true;
        }
        return false;
    }

    public boolean addCustomerTransaction(String name, double amount) {
        Customer existingCustomer = findCustomer(name);
        if (existingCustomer != null) {
            existingCustomer.addTransaction(amount);
            return true;
        }
        return false;
    }

    private Customer findCustomer(String name) {

        for (int i = 0; i < this.customers.size(); i++) {
            Customer currentCustomer = this.customers.get(i);
            if (currentCustomer.getName().equals(name)) {
                return currentCustomer;
            }
        }

        return null;
    }

    public void printCustomers() {
        for (int i = 0; i < this.customers.size(); i++) {
            Customer currentCustomer = this.customers.get(i);
            System.out.println("#" + (i + 1) + " " + currentCustomer.getName());
        }
    }

    public void printCustomersAndTransactions() {
        for (int i = 0; i < this.customers.size(); i++) {
            Customer currentCustomer = this.customers.get(i);
            System.out.println(currentCustomer.getName() + " has transactions:");
            currentCustomer.printTransactions();
        }
    }
}
