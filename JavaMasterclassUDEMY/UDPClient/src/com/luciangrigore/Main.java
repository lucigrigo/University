package com.luciangrigore;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try {
            InetAddress address = InetAddress.getLocalHost();
            DatagramSocket datagramSocket = new DatagramSocket();

            Scanner scanner = new Scanner(System.in);
            String echoString;

            do {
                System.out.println("Enter string to be echoed:");
                echoString = scanner.nextLine();

                byte[] buffer = echoString.getBytes();
                DatagramPacket datagramPacket = new DatagramPacket(
                        buffer, buffer.length, address, 5000);
                datagramSocket.send(datagramPacket);

                byte[] buffer2 = new byte[50];
                datagramPacket = new DatagramPacket(buffer2, buffer2.length);
                datagramSocket.receive(datagramPacket);
                System.out.println("Text received is: " + new String(buffer2, 0, datagramPacket.getLength()));

            } while (!echoString.equals("exit"));

        } catch (SocketTimeoutException e) {
            System.out.println("Socket timed out!");
        } catch (IOException e) {
            System.out.println("Client error: " + e.getMessage());
        }
    }
}
