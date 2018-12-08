package com.luciangrigore;

import java.util.Scanner;

public class Main {

    private static Scanner scanner = new Scanner(System.in);
    private static Button buttonPrint = new Button("Print");

    public static void main(String[] args) {

        /*
        Gearbox mcLaren = new Gearbox(6);
        */
//        Gearbox.Gear first = mcLaren.new Gear(1, 12.3);
//        System.out.println(first.driveSpeed(1000));

//        mcLaren.addGear(1, 5.3);
//        mcLaren.addGear(2, 10.6);
//        mcLaren.addGear(3, 15.9);

        /*
        mcLaren.operateClucth(true);
        mcLaren.changeGear(1);
        mcLaren.operateClucth(false);
        System.out.println(mcLaren.realSpeed(1000));
        mcLaren.changeGear(2);
        System.out.println(mcLaren.realSpeed(3000));
        mcLaren.operateClucth(true);
        mcLaren.changeGear(3);
        mcLaren.operateClucth(false);
        System.out.println(mcLaren.realSpeed(6000));
        */

        /*
        class ClickListener implements Button.OnClickListener {

            public ClickListener() {
                System.out.println("I've been attached!");
            }

            @Override
            public void onClick(String title) {
                System.out.println(title + " was clicked !");
            }
        }
        */


        //        buttonPrint.setOnClickListener(new ClickListener());
        buttonPrint.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(String title) {
                System.out.println(title + " was clicked !");
            }
        });

        listen();
    }

    private static void listen() {
        boolean quit = false;
        while (!quit) {
            int choice = scanner.nextInt();
            scanner.nextLine();
            switch (choice) {
                case 0:
                    quit = true;
                    break;
                case 1:
                    buttonPrint.onClick();
                    break;
            }
        }
    }
}
