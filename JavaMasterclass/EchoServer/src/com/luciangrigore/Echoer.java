package com.luciangrigore;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Echoer extends Thread {
    private Socket socket;

    public Echoer(Socket s) {
        this.socket = s;
    }

    @Override
    public void run() {
        try {
            BufferedReader input = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));
            PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);

            while (true) {
                String echoString = input.readLine();
                System.out.println("Received client input: " + echoString);

                if (echoString.equals("exit")) {
                    break;
                }

                try {
                    Thread.sleep(15000);
                } catch (InterruptedException e) {
                    System.out.println("Thread interrupted!");
                }

                writer.println(echoString);
            }
        } catch (IOException e) {
            System.out.println("oops! " + e.getMessage());
        } finally {
            try {
                socket.close();
            } catch (IOException e1) {
                // oh, well
            }
        }
    }
}
