package com.company;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;

public class BankAccount2 {

    private double balance;
    private String accountNumber;
    final private ReentrantLock lock;

    //    public BankAccount2(double balance, String accountNumber, ReentrantLock lock) {
    public BankAccount2(double balance, String accountNumber) {
        this.balance = balance;
        this.accountNumber = accountNumber;
//        this.lock = lock;
        this.lock = new ReentrantLock();
    }

//    public synchronized void deposit(double amount) {
//        balance += amount;
//    }
//
//    public synchronized void withdraw(double amount) {
//        balance -= amount;
//    }

    //  using synchronized methods
//    public void deposit(double amount) {
//        synchronized (this) {
//            balance += amount;
//        }
//    }
//
//    public void withdraw(double amount) {
//        synchronized (this) {
//            balance -= amount;
//        }
//    }

    //  using a ReentrantLock
    public void deposit(double amount) {
//        lock.lock();
//        try {
//            balance += amount;
//        } finally {
//            lock.unlock();
//        }

        boolean status = false;
        try {
            if (lock.tryLock(1000, TimeUnit.MILLISECONDS)) {
                try {
                    balance += amount;
                    status = true;
                } finally {
                    lock.unlock();
                }
            } else {
                System.out.println("Could not get the lock!");
            }
        } catch (InterruptedException ie) {
            System.out.println("Exception encountered");
        }
        System.out.println("Transaction status = " + status);

    }

    public void withdraw(double amount) {
//        lock.lock();
//        try {
//            balance -= amount;
//        } finally {
//            lock.unlock();
//        }

        //  status variable IS ALWAYS THREAD-SAFE because it is a local variable
        //  that means it is stored on the thread stack ( not the heap )
        boolean status = false;
        try {
            if (lock.tryLock(1000, TimeUnit.MILLISECONDS)) {
                try {
                    balance -= amount;
                    status = true;
                } finally {
                    lock.unlock();
                }
            } else {
                System.out.println("Could not get the lock!");
            }
        } catch (InterruptedException ie) {
            System.out.println("Exception encountered");
        }
        System.out.println("Transaction status = " + status);

    }

    public double getBalance() {
        return balance;
    }

    public String getAccountNumber() {
        return this.accountNumber;
    }

    public void printAccountNumber() {
        System.out.println("Account number = " + this.accountNumber);
    }
}
