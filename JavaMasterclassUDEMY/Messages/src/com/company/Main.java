package com.company;

import java.util.Random;

public class Main {

    public static void main(String[] args) {
        Message message = new Message();
        (new Thread(new Writer(message))).start();
        (new Thread(new Reader(message))).start();
    }
}

class Message {
    private String message;
    private boolean empty = true;

    public synchronized String read() {
        while (empty) {
            try {
                //  we wanna call wait() within a loop
                //  (random wakes because of the OS)
                wait();
            } catch (InterruptedException ie) {
                System.out.println("GOOD MORNING");
            }
        }
        empty = true;
        notifyAll();
        return message;
    }

    public synchronized void write(String message) {
        while (!empty) {
            try {
                wait();
            } catch (InterruptedException ie) {
                System.out.println("GOOD MORNING");
            }
        }
        empty = false;
        this.message = message;
        notifyAll();
    }
}

class Writer implements Runnable {
    private Message message;

    public Writer(Message message) {
        this.message = message;
    }

    @Override
    public void run() {
        String[] messages = {
                "yolo smekerie",
                "stefania ma enerveaza",
                "dar eu tot o iub",
                "inca nu stiu de ce",
                "hai gata cu prostiile",
                "sa ne intoarcem la Java"
        };

        Random random = new Random();

        for (int i = 0; i < messages.length; i++) {
            message.write(messages[i]);
            try {
                Thread.sleep(random.nextInt(2000));
            } catch (InterruptedException ie) {
                System.out.println("GOOD MORNING");
            }
        }
        message.write("Finished");
    }
}

class Reader implements Runnable {
    private Message message;

    public Reader(Message message) {
        this.message = message;
    }

    @Override
    public void run() {
        Random random = new Random();
        for (String lastMessage = message.read(); !lastMessage.equals("Finished");
             lastMessage = message.read()) {
            System.out.println(lastMessage);
            try {
                Thread.sleep(random.nextInt(2000));
            } catch (InterruptedException ie) {
                System.out.println("GOOD MORNING");
            }
        }
    }
}