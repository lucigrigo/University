package com.luciangrigore;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Player luci = new Player("Luci", 100.0, 85.0);

        System.out.println(luci.toString());
        savedObject(luci);

        luci.setHealth(80);
        //  Automatically uses .toString() method
        System.out.println(luci);
        luci.setWeapon("Lamâ");

        savedObject(luci);
//        loadObject(luci);
        System.out.println(luci);

        ISaveable werewolf = new Monster("Werewolf", 20, 40);
        System.out.println(((Monster) werewolf).getStrength());
        System.out.println(werewolf);
        savedObject(werewolf);
    }

    public static ArrayList<String> readValues() {
        ArrayList<String> values = new ArrayList<String>();

        Scanner scanner = new Scanner(System.in);
        boolean quit = false;
        int index = 0;
        System.out.println("Choose :\n" +
                "1 to enter a string\n" +
                "0 to quit");

        while (!quit) {
            System.out.println("Choose an option :");
            int option = scanner.nextInt();
            scanner.nextLine();
            switch (option) {
                case 0:
                    quit = true;
                    break;
                case 1:
                    System.out.println("Enter a string :");
                    String stringInput = scanner.nextLine();
                    values.add(index, stringInput);
                    index++;
                    break;
            }
        }

        return values;
    }

    public static void savedObject(ISaveable objectToSave) {
        for (int i = 0; i < objectToSave.write().size(); i++) {
            System.out.println("Saving " + objectToSave.write().get(i) +
                    " to storage device!");
        }
    }

    public static void loadObject(ISaveable objectToLoad) {
        ArrayList<String> values = readValues();
        objectToLoad.read(values);
    }
}
