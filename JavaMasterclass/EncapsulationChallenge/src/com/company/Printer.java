package com.company;

public class Printer {
    private boolean duplexPrinter;
    private int tonerLevel, pagesPrinted;

    public Printer(boolean duplexPrinter, int tonerLevel, int pagesPrinted) {
        this.duplexPrinter = duplexPrinter;
        this.tonerLevel = tonerLevel;
        this.pagesPrinted = pagesPrinted;
    }

    public boolean isDuplexPrinter() {
        return duplexPrinter;
    }

    public int getTonerLevel() {
        return tonerLevel;
    }

    public int getPagesPrinted() {
        return pagesPrinted;
    }

    public void printPages(int number, boolean bothSides) {
        if (bothSides == true && duplexPrinter == true) {
            System.out.println("Printing the pages both sides ...");
            this.pagesPrinted += number / 2;
            this.tonerLevel -= number;
        } else if (bothSides == true && duplexPrinter == false) {
            System.out.println("This is not a duplex printer !");
            System.out.println("Printing pages one by one ...");
            this.pagesPrinted += number;
            this.tonerLevel -= number;
        } else if (bothSides == false && duplexPrinter == false) {
            System.out.println("Printing " + number + " pages. Please wait ...");
            this.pagesPrinted += number;
            this.tonerLevel -= number;
        }

        if (tonerLevel <= 0) {
            System.out.println("No tone left");
        } else {
            System.out.println("Tone left : " + this.tonerLevel);
        }

        System.out.println("This printer printed so far " + this.pagesPrinted + " pages");
        System.out.println("Keep it up :)");
        System.out.println();
    }

    public void fillToner(int addedToner) {
        this.tonerLevel += addedToner;
        if (tonerLevel > 100) {
            System.out.println("Too much toner added !");
        } else {
            System.out.println("Current toner level is " + this.tonerLevel);
        }
    }
}
