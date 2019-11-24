package com.luciangrigore;

public class Main {


    public static void main(final String[] args) {

//        String test = "abcdef";
//        new GenerateSubsequences().generateSubsequences(test, 0, new int[test.length()]);

        if (args[0] != null) {
            switch (args[0]) {
                case "tests":
                    // run all tests
                    // input dir, output dir
                    break;
                case "manual":
                    // apply both algorithms to search given pattern
                    // into given string
                    break;
                case "subseq":
                    // TODO decide whether or not this is to be done
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
