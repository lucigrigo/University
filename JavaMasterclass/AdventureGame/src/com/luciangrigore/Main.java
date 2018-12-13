package com.luciangrigore;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
    private static Map<Integer, Location> locations = new HashMap<Integer, Location>();

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        //  Adding the locations
        Map<String, Integer> tempExit = new HashMap<String, Integer>();
        locations.put(0, new Location(0, "You are sitting in front of a computer learning Java", null));


        //  Adding the possible exits for each location
        tempExit = new HashMap<String, Integer>();
        tempExit.put("W", 2);
        tempExit.put("E", 3);
        tempExit.put("S", 4);
        tempExit.put("N", 5);
        locations.put(1, new Location(1, "You are standing at the end of the road before a small brick building", tempExit));

        tempExit = new HashMap<String, Integer>();
        tempExit.put("N", 5);
        locations.put(2, new Location(2, "You are at the top of the hill", tempExit));

        tempExit = new HashMap<String, Integer>();
        tempExit.put("W", 1);
        locations.put(3, new Location(3, "You are inside a building, a well house for a small spring", tempExit));

        tempExit = new HashMap<String, Integer>();
        tempExit.put("N", 1);
        tempExit.put("W", 2);
        locations.put(4, new Location(4, "You are in a valley beside a stream", tempExit));


        tempExit = new HashMap<String, Integer>();
        tempExit.put("S", 1);
        tempExit.put("W", 2);
//        tempExit.put("Q", 0);
        locations.put(5, new Location(5, "You are in the forest", tempExit));


        int loc = 1;
        while (true) {
            System.out.println(locations.get(loc).getDescription());

            if (loc == 0) {
                break;
            }

            Map<String, Integer> exits = locations.get(loc).getExits();
            System.out.print("Available exits are : ");
            for (String exit : exits.keySet()) {
                System.out.print(exit + ",");
            }
            System.out.println();

            String direction = scanner.nextLine().toUpperCase();
            if (direction.length() != 1) {
                String[] instr = direction.split(" ");
                for (String str : instr) {
                    if (str.equals("WEST")) {
                        direction = "W";
                    }
                    if (str.equals("EAST")) {
                        direction = "E";
                    }
                    if (str.equals("NORTH")) {
                        direction = "N";
                    }
                    if (str.equals("SOUTH")) {
                        direction = "S";
                    }
                    if (str.equals("QUIT")) {
                        direction = "Q";
                    }
                }
            }
            if (exits.containsKey(direction)) {
                loc = exits.get(direction);
            } else {
                System.out.println("You cannot go in that direction");
            }
        }

    }
}
