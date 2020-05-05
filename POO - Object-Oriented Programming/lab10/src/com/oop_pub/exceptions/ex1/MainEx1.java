package com.oop_pub.exceptions.ex1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MainEx1 {

    private static void readAndPrintLine() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        try {
            System.out.println("type something:");
            String input = reader.readLine();
            System.out.println("\ninput was:\n" + input);
        } catch (IOException e1) {
            e1.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (IOException e2) {
                e2.printStackTrace();
            }
        }

        try (BufferedReader reader1 = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.println("Print smth:");
            String input1 = reader1.readLine();
            System.out.println("\ninput was:\n" + input1);
        } catch (IOException e3) {
            e3.printStackTrace();
        }
    }

    public static void main(String[] args) {
        readAndPrintLine();
    }
}
