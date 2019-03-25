package com.company;

import java.util.Scanner;

public class Main {

    private static Scanner scanner = new Scanner(System.in);
    private static MobilePhone thePhone = new MobilePhone("Luci",
            "0728896395");

    public static void main(String[] args) {
        System.out.println("Welcome!");
        boolean run = true;
        printInstr();
        while (run) {
            int a = scanner.nextInt();
            scanner.nextLine();
            switch (a) {
                case 0:
                    run = false;
                    break;
                case 1:
                    printContacts();
                    break;
                case 2:
                    addContact();
                    break;
                case 3:
                    updateContact();
                    break;
                case 4:
                    removeContact();
                    break;
                case 5:
                    searchContact();
                    break;
                case 6:
                    printInstr();
                    break;
            }

        }
    }

    public static void printInstr() {
        System.out.println("Your options are :");
        System.out.println("#0 - quit the menu");
        System.out.println("#1 - print the list of contacts");
        System.out.println("#2 - add new contact");
        System.out.println("#3 - update existing contact");
        System.out.println("#4 - remove contact");
        System.out.println("#5 - search contact");
        System.out.println("#6 - print these instructions");
    }

    public static void printContacts() {
        thePhone.printList();
    }

    public static void addContact() {
        System.out.println("Enter the number that you want to add ");
        int nr = scanner.nextInt();
        scanner.nextLine();
        if (thePhone.searchContact(nr) == false) {
            System.out.println("Enter the name :");
            String name = scanner.nextLine();
            thePhone.addContact(name, nr);
        } else {
            System.out.println("You already have that number in your contacts list !");
        }
    }

    public static void updateContact() {
        System.out.println("Press 1 to search for the name , or 2 to search for the number");
        int n = scanner.nextInt();
        if (n == 1) {
            String name = scanner.nextLine();
            if (thePhone.searchContact(name)) {
                System.out.println("Enter new number");
                int number = scanner.nextInt();
                scanner.nextLine();
                thePhone.updateContact(name, number);
            } else {
                System.out.println("The name is not in your contacts list !");
                System.out.println("Would you like to add it ? true/false ");
                String option = scanner.nextLine();
                if (option == "true") {
                    addContact();
                }
            }
        } else if (n == 2) {
            int number = scanner.nextInt();
            if (thePhone.searchContact(number)) {
                System.out.println("Enter new name");
                String newName = scanner.nextLine();
                thePhone.updateContact(number, newName);
            } else {
                System.out.println("The number is not in your contacts list !");
                System.out.println("Would you like to add it ? true/false ");
                String option = scanner.nextLine();
                if (option == "true") {
                    addContact();
                }
            }
        }
    }

    public static void removeContact() {
        System.out.println("Enter the name or the number that you want to remove !");
        if (scanner.hasNextInt()) {
            int nr = scanner.nextInt();
            scanner.nextLine();
            thePhone.removeContact(nr);
        } else {
            String nm = scanner.nextLine();
            thePhone.removeContact(nm);
        }
    }

    public static void searchContact() {
        System.out.println("Enter the name or the number that you want to search for !");
        if (scanner.hasNextInt()) {
            int nr = scanner.nextInt();
            scanner.nextLine();
            if (thePhone.searchContact(nr)) {
                System.out.println("Contact found !");
                thePhone.printContact(nr);
            } else {
                System.out.println("Contact not found !");
            }
        } else {
            String nm = scanner.nextLine();
            if (thePhone.searchContact(nm)) {
                System.out.println("Contact found !");
                thePhone.printContact(nm);
            } else {
                System.out.println("Contact not found !");
            }
        }
    }
}
