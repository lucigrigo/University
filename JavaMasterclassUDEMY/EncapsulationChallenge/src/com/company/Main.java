package com.company;

public class Main {

    public static void main(String[] args) {
        Printer newPrinter = new Printer(false, 95, 15);
        Printer newDuplexPrinter = new Printer(true, 52, 150);

        System.out.println("Number of paged printed so far is " + newPrinter.getPagesPrinted());
        System.out.println("Number of pages printed so far is " + newDuplexPrinter.getPagesPrinted());

        newPrinter.printPages(10, true);
        newPrinter.printPages(10, false);

        newDuplexPrinter.printPages(5, false);
        newDuplexPrinter.printPages(10, true);

        System.out.println(newPrinter.getPagesPrinted());
        System.out.println(newDuplexPrinter.getPagesPrinted());
    }
}
