package com.company;

public class Main {
//    public static ReentrantLock lock = new ReentrantLock();

    public static void main(String[] args) {
//        final BankAccount2 account = new BankAccount2(1000.00,
//                "12345-678", lock);
        final BankAccount2 account = new BankAccount2(1000.00,
                "12345-678");

        new Thread(new Runnable() {
            @Override
            public void run() {
                account.deposit(300.00);
                account.withdraw(50.00);
//                System.out.println("Current balance is " + account.getBalance());
            }
        }).start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                account.deposit(203.75);
                account.withdraw(100.00);
//                System.out.println("Current balance is " + account.getBalance());
            }
        }).start();

        try {
            Thread.sleep(3000);
        } catch (InterruptedException ie) {
            System.out.println("Good morning");
        }
        System.out.println("Current balance is " + account.getBalance());
    }
}
