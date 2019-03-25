package com.company;

public class Main {

    public static void main(String[] args) {

        Bank bank = new Bank("Banca Transilvania");

        bank.addBranch("Buzau");

        bank.addCustomer("Lucian", "Buzau", 1988.23);
        bank.addCustomer("Caeraje", "Buzau", 888999.92);
        bank.addCustomer("Edward", "Buzau", 15.64);

        bank.addBranch("Bucharest");

        bank.addCustomer("Mike", "Bucharest", 20000.55);
        bank.addTransaction("Mike", "Bucharest", 200);
        bank.addTransaction("Mike", "Bucharest", 1200.23);

        bank.printCustomers("Buzau");
        bank.printCustomersAndTransactions("Buzau");

        bank.printCustomers("Bucharest");
        bank.printCustomersAndTransactions("Bucharest");
    }
}
