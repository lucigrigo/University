package com.luciangrigore;

public class Main {

    public static void main(final String[] args) {
        if (args[0] != null) {
            MatchingAdministrator administrator = new MatchingAdministrator();
            switch (args[0]) {
                case "tests":
                    administrator.runAllTests(args[1], args[2]);
                    break;
                case "manual":
                    administrator.runOneTest(args[1], args[2]);
                    break;
                default:
                    System.out.println("Input invalid!");
                    System.exit(1);
            }
        } else {
            System.out.println("Input invalid!");
            System.exit(1);
        }
    }
}
