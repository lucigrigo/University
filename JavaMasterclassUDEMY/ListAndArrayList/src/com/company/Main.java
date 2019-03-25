package com.company;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    private static Scanner s = new Scanner(System.in);
    public static GroceryList groceryList = new GroceryList();

    public static void main(String[] args) {
        boolean quit = false;
        int choice = 0;
        printInstructions();
        while (!quit) {
            System.out.println("Enter your choice ");
            choice = s.nextInt();
            s.nextLine();
            switch (choice) {
                case 0:
                    printInstructions();
                    break;
                case 1:
                    groceryList.printGroceryList();
                    break;
                case 2:
                    addItem();
                    break;
                case 3:
                    modifyItem();
                    break;
                case 4:
                    removeItem();
                    break;
                case 5:
                    searchItem();
                    break;
                case 6:
                    processArrayList();
                    break;
                case 7:
                    quit = true;
                    break;
            }
        }
    }

    public static void printInstructions() {
        System.out.println("\nPress");
        System.out.println("\t0 - to print choice options");
        System.out.println("\t1 - to print the list of the grocery items");
        System.out.println("\t2 - to add an item to the grocery list");
        System.out.println("\t3 - to modify an item from the list");
        System.out.println("\t4 - to remove an item from the list");
        System.out.println("\t5 - to search for an item in the list");
        System.out.println("\t6 - to quit the app");
    }

    public static void addItem() {
        System.out.print("Please enter the grocery item ");
        groceryList.addGroceryItem(s.nextLine());
    }

    public static void modifyItem() {
        System.out.print("Current item name ");
        String oldItem = s.nextLine();
        System.out.print("Enter new item ");
        String newItem = s.nextLine();
        groceryList.modifyGroceryItem(oldItem, newItem);
    }

    public static void removeItem() {
        System.out.print("Current item name ");
        String oldItem = s.nextLine();
        groceryList.removeGroceryItem(oldItem);
    }

    public static void searchItem() {
        System.out.print("Item to search for ? ");
        String item = s.nextLine();
        if (groceryList.onFile(item)) {
            System.out.println("Found " + item + " in our grocery list !");
        } else {
            System.out.println(item + " is not in the shopping list !");
        }
    }

    public static void processArrayList() {
        //  Ways to copy the components of an ArrayList
        ArrayList<String> newArray = new ArrayList<String>();

        newArray.addAll(groceryList.getGroceryList());

        ArrayList<String> nextArray = new ArrayList<String>(groceryList.getGroceryList());

        //  Convert from ArrayList to classical String
        String[] myArray = new String[groceryList.getGroceryList().size()];
        myArray = groceryList.getGroceryList().toArray(myArray);
    }
}
