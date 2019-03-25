package com.company;

import java.util.concurrent.atomic.AtomicInteger;

public class Main {

    public static void main(String[] args) {

        final Worker w1 = new Worker("Worker 1", true);
        final Worker w2 = new Worker("Worker 2", true);

        final SharedResource sharedResource = new SharedResource(w1);

        new Thread(new Runnable() {
            @Override
            public void run() {
                w1.work(sharedResource, w2);
            }
        }).start();

        new Thread(new Runnable() {
            @Override
            public void run() {
                w2.work(sharedResource, w1);
            }
        }).start();

//        AtomicInteger atomicInteger = new AtomicInteger();
//        atomicInteger.set(10);
//        System.out.println(atomicInteger.incrementAndGet());
    }
}
