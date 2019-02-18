package com.company;

import static com.company.Main.lock1;

public class Main {

    public static Object lock1 = new Object();
    public static Object lock2 = new Object();

    public static void main(String[] args) {
        new Thread1().start();
        new Thread2().start();
    }

    private static class Thread1 extends Thread {
        @Override
        public void run() {
            synchronized (lock1) {
                System.out.println("Thread1 has lock1");
                try {
                    Thread.sleep(100);
                } catch (InterruptedException ie) {

                }
                System.out.println("Thread1 waiting for lock2");
                synchronized (lock2) {
                    System.out.println("Thread1 has lock1 and lock2");
                }
                System.out.println("Thread1 released lock2");
            }
            System.out.println("Thread1 released lock1. Exiting...");
        }
    }

    private static class Thread2 extends Thread {
        @Override
        public void run() {
            synchronized (lock1) {
                System.out.println("Thread2 has lock1");
                try {
                    Thread.sleep(100);
                } catch (InterruptedException ie) {

                }
                System.out.println("Thread2 waiting for lock2");
                synchronized (lock2) {
                    System.out.println("Thread2 has lock1 and lock2");
                }
                System.out.println("Thread2 released lock2");
            }
            System.out.println("Thread2 released lock1. Exiting...");
        }
    }
}


