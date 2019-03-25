package com.company;

public class Main {

    public static void main(String[] args) {

        System.out.println("Hello from the main thread.");

//        Runnable thread2 = new Runnable() {
//            @Override
//            public void run() {
//                System.out.println("Hello from the other thread!");
//            }
//        };
//
//        Thread.sleep(10000);
//        new Thread(thread2).start();

        Thread anotherThread = new AnotherThread();
        anotherThread.setName("== Another Thread ==");
        anotherThread.start();
//        anotherThread.run();  //  MISTAKE

        new Thread() {
            public void run() {
                System.out.println("Hello from the anonymous thread.");
                try {
                    anotherThread.join(2000);
                    System.out.println("we are back here after all");
                } catch (InterruptedException ie) {
                    System.out.println("I couldn't wait after all. I was interrupted");
                }
            }
        }.start();

//        Thread myRunnableThread = new Thread(new MyRunnable());
        Thread myRunnableThread = new Thread(new MyRunnable() {
            @Override
            public void run() {
                System.out.println("HIIIIII");
                super.run();
            }
        });
        myRunnableThread.start();
//        anotherThread.interrupt();

        System.out.println("Hello again from the main thread.");
    }
}
