package com.company;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

public class Demo {

    public static void main(String[] args) {

        LinkedList<String> placesToVisit = new LinkedList<String>();

        addInOrder("Sydney", placesToVisit);
        addInOrder("Melbourne", placesToVisit);
        addInOrder("Brisbane", placesToVisit);
        addInOrder("Adelaide", placesToVisit);
        addInOrder("Darwin", placesToVisit);
        addInOrder("Perth", placesToVisit);
        addInOrder("Canberra", placesToVisit);

        printList(placesToVisit);

        addInOrder("Alice Springs", placesToVisit);

        printList(placesToVisit);

        addInOrder("Darwin", placesToVisit);

        printList(placesToVisit);


        visit(placesToVisit);

        /*
        placesToVisit.add("Sydney");
        placesToVisit.add("Melbourne");
        placesToVisit.add("Brisbane");
        placesToVisit.add("Perth");
        placesToVisit.add("Darwin");

        printList(placesToVisit);

        placesToVisit.add(1, "Alice Springs");

        printList(placesToVisit);

        placesToVisit.remove(4);

        printList(placesToVisit);
        */

    }

    private static void printList(LinkedList<String> lS) {
        Iterator<String> i = lS.iterator();

        while (i.hasNext()) {
            System.out.println("Now visiting " + i.next());
        }
        System.out.println("======================");
    }

    private static boolean addInOrder(String newCity, LinkedList<String> LS) {
        ListIterator<String> LI = LS.listIterator();

        while (LI.hasNext()) {
            int comparison = LI.next().compareTo(newCity);
            if (comparison == 0) {
                //  equal -> do not add
                System.out.println(newCity + " is already included as a destination!");
                return false;
            } else if (comparison > 0) {
                //  newCity should appear before this one
                //  Brisbane -> Adelaide
                LI.previous();
                LI.add(newCity);
                return true;
            } else if (comparison < 0) {
                //  move on to next city
                //  do nothing
            }
        }

        LI.add(newCity);
        return true;
    }

    private static void visit(LinkedList cities) {
        Scanner scanner = new Scanner(System.in);
        boolean quit = false;
        boolean goingForward = true;
        ListIterator<String> listIterator = cities.listIterator();

        if (cities.isEmpty()) {
            System.out.println("No cities in the list!");
            return;
        } else {
            System.out.println("Now visiting " + listIterator.next());
            printMenu();
        }

        while (!quit) {
            int action = scanner.nextInt();
            scanner.nextLine();
            switch (action) {
                case 0:
                    System.out.println("Holiday over !");
                    quit = true;
                    break;
                case 1:
                    if (!goingForward) {
                        if (listIterator.hasNext()) {
                            listIterator.next();
                        }
                        goingForward = true;
                    }
                    if (listIterator.hasNext()) {
                        System.out.println("Now visiting " + listIterator.next());
                    } else {
                        System.out.println("Reached the end of the list !");
                        goingForward = false;
                    }
                    break;
                case 2:
                    if (goingForward) {
                        if (listIterator.hasPrevious()) {
                            listIterator.previous();
                        }
                        goingForward = false;
                    }
                    if (listIterator.hasPrevious()) {
                        System.out.println("Now visiting " + listIterator.previous());
                    } else {
                        System.out.println("Reached the start of the list !");
                        goingForward = true;
                    }
                    break;
                case 3:
                    printMenu();
                    break;
            }
        }
    }

    private static void printMenu() {
        System.out.println("Available actions : \npress");
        System.out.println("0 - to quit\n" +
                "1 - next city\n" +
                "2 - previous city\n" +
                "3 - print the menu\n");
    }
}

