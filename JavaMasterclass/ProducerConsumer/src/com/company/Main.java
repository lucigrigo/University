package com.company;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.*;
import java.util.concurrent.locks.ReentrantLock;

import static com.company.Main.EOF;

public class Main {
    public static final String EOF = "EOF";

    public static void main(String[] args) {
        // ArrayBlockingQueue is type FIFO ( first in first out )
        ArrayBlockingQueue<String> buffer = new ArrayBlockingQueue<String>(6);
//        ReentrantLock bufferLock = new ReentrantLock();

        ExecutorService executorService = Executors.newFixedThreadPool(5);

//        MyProducer producer = new MyProducer(buffer, ThreadColor.ANSI_CYAN, bufferLock);
//        MyConsumer consumer1 = new MyConsumer(buffer, ThreadColor.ANSI_BLUE, bufferLock);
//        MyConsumer consumer2 = new MyConsumer(buffer, ThreadColor.ANSI_GREEN, bufferLock);
        MyProducer producer = new MyProducer(buffer, ThreadColor.ANSI_CYAN);
        MyConsumer consumer1 = new MyConsumer(buffer, ThreadColor.ANSI_BLUE);
        MyConsumer consumer2 = new MyConsumer(buffer, ThreadColor.ANSI_GREEN);

//        new Thread(producer).start();
//        new Thread(consumer1).start();
//        new Thread(consumer2).start();
        executorService.execute(producer);
        executorService.execute(consumer1);
        executorService.execute(consumer2);

        Future<String> future = executorService.submit(new Callable<String>() {
            @Override
            public String call() throws Exception {
                System.out.println(ThreadColor.ANSI_WHITE + "I'm being printed from the callable class");
                return ThreadColor.ANSI_WHITE + "This is the callable Result";
            }
        });
        try {
            System.out.println(future.get());
        } catch (ExecutionException ee) {
            System.out.println("Something went wrong");
        } catch (InterruptedException ie) {
            System.out.println("Thread running the task was interrupted ");
        }

        executorService.shutdown();
    }
}

class MyProducer implements Runnable {
    private ArrayBlockingQueue<String> buffer;
    private String color;
//    private ReentrantLock bufferLock;

    public MyProducer(ArrayBlockingQueue<String> buffer, String color) {
        this.buffer = buffer;
        this.color = color;
//        this.bufferLock = lock;
    }

    @Override
    public void run() {
        Random random = new Random();
        String[] nums = {"1", "2", "3", "4", "5"};

        for (String num : nums) {
            try {
                System.out.println(color + "Adding " + num);
                buffer.put(num);
//                bufferLock.lock();
//                try {
//                    buffer.add(num);
//                } finally {
////                    bufferLock.unlock();
//                }

                Thread.sleep(random.nextInt(1000));
            } catch (InterruptedException ie) {
                System.out.println("Producer was interrupted!");
            }
        }

        System.out.println(color + "Adding EOF. Exiting...");
//        bufferLock.lock();
        try {
            buffer.put("EOF");
        } catch (InterruptedException ie) {

        }
//        finally {
////            bufferLock.unlock();
//        }
    }
}

class MyConsumer implements Runnable {
    private ArrayBlockingQueue<String> buffer;
    private String color;
//    private ReentrantLock bufferLock;

    public MyConsumer(ArrayBlockingQueue<String> buffer, String color) {
        this.buffer = buffer;
        this.color = color;
//        this.bufferLock = lock;
    }

    @Override
    public void run() {

//        int counter = 0;

        while (true) {
            synchronized (buffer) {
//            if (bufferLock.tryLock()) {
                try {
                    if (buffer.isEmpty()) {
                        continue;
                    }
//                System.out.println(color + "counter = " + counter);
                    if (buffer.peek().equals(EOF)) {
                        System.out.println(color + "Exiting ...");
                        break;
                    } else {
                        System.out.println(color + "Removed " + buffer.take());
                    }
                } catch (InterruptedException ie) {

                }
//            finally {
//                    bufferLock.unlock();
//            }
//            } else {
//                counter++;
//            }
            }
        }
    }
}