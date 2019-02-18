package com.company;

public class AnotherThread extends Thread {

    @Override
    public void run() {
        System.out.println("Hello from " + currentThread().getName());

        try {
            Thread.sleep(5000);
        } catch (InterruptedException ie) {
            System.out.println("I was woken up from " + currentThread().getName());
            return;
        }

        System.out.println("Hello from " + currentThread().getName() + " again !");
    }
}
