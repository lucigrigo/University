package com.luciangrigore;

import java.util.Arrays;
import java.util.List;
import java.util.function.Function;
import java.util.function.Supplier;

public class Main {

    public static void main(String[] args) {
        Runnable runnable = () -> {
            String myString = "Let's split this up into an array";
            String[] parts = myString.split(" ");
            for (String part : parts) {
                System.out.println(part);
            }
        };

        Function<String, String> everySecondChar = (String source) -> {
            StringBuilder finalString = new StringBuilder();
            for (int i = 0; i < source.length(); i++) {
                if (i % 2 == 1) {
                    finalString.append(source.charAt(i));
                }
            }
            return finalString.toString();
        };

        System.out.println(everySecondChar.apply("1234567890"));
        System.out.println(everySecondCharacter(everySecondChar, "1234567890"));

        Supplier<String> iLoveJava = () -> "I Love Java!";
        String supplierResult = iLoveJava.get();
        System.out.println(supplierResult);

        List<String> topNames2015 = Arrays.asList(
                "Amelia",
                "Olivia",
                "emily",
                "Isla",
                "Ava",
                "oliver",
                "Jack",
                "Charlie",
                "harry",
                "Jacob"
        );

        System.out.println("==========================");
        topNames2015.stream()
                .map(s -> s.substring(0, 1).toUpperCase() + s.substring(1))
                .sorted()
                .forEach(System.out::println);

        System.out.println("==========================");
        System.out.println("Number of names beginning with A is " +
                topNames2015.stream()
                        .map(String::toUpperCase)
                        .filter(s -> s.startsWith("A"))
                        .count());

        System.out.println("==========================");
        topNames2015.stream()
                .map(s -> s.substring(0, 1).toUpperCase() + s.substring(1))
                .peek(System.out::println)
                .sorted()
                .forEach(System.out::println);
        System.out.println("==========================");
    }

    private static String everySecondCharacter(Function<String, String> fct, String stringToBeProcessed) {
        return fct.apply(stringToBeProcessed);
    }
}
