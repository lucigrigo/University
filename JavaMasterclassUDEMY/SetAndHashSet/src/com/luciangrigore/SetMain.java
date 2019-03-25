package com.luciangrigore;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class SetMain {

    //  Set bulk operations
    public static void main(String[] args) {

        Set<Integer> squares = new HashSet<>();
        Set<Integer> cubes = new HashSet<>();

        for (int i = 1; i <= 100; i++) {
            squares.add(i * i);
            cubes.add(i * i * i);
        }

        //  Reuniunea dintre cele 2 multimi
        Set<Integer> union = new HashSet<>(squares);
        union.addAll(cubes);
        System.out.println(union.size());

        //  Intersectia dintre 2 multimi
        Set<Integer> intersection = new HashSet<>(squares);
        intersection.retainAll(cubes);
        System.out.println(intersection.size());
        for (int i : intersection) {
            System.out.println(i + " is the square of " + Math.sqrt(i) +
                    " and the cube of " + Math.cbrt(i));
        }

        //  Arrays.asList() = transformarea in lista a unui array de string
        Set<String> words = new HashSet<>();
        String sentence = "azi e ziua lu tata mare";
        String[] arrayWords = sentence.split(" ");
        words.addAll(Arrays.asList(arrayWords));
        for (String s : words) {
            System.out.println(s);
        }


        //  Diferenta dintre 2 multimi
        //  = asymmetric difference
        Set<String> nature = new HashSet<>();
        Set<String> divine = new HashSet<>();
        String[] arrayNatureWords = {"all", "nature", "is", "but", "art", "unknown", "to", "thee"};
        String[] arrayDivineWords = {"to", "err", "is", "human", "to", "forgive", "divine"};
        nature.addAll(Arrays.asList(arrayNatureWords));
        divine.addAll(Arrays.asList(arrayDivineWords));

        System.out.println("nature - divine");
        Set<String> diff1 = new HashSet<>(nature);
        diff1.removeAll(divine);
        printSet(diff1);

        System.out.println("divine - nature");
        Set<String> diff2 = new HashSet<>(divine);
        diff2.removeAll(nature);
        printSet(diff2);


        //  The symmetric difference = elementele care apar in fiecare din multimi
        //  dar nu in ambele ( reuniunea minus intersectia )
        Set<String> unionTest = new HashSet<>(nature);
        unionTest.addAll(divine);
        Set<String> intersectionTest = new HashSet<>(nature);
        intersectionTest.retainAll(divine);
        System.out.println("the symmetric difference is ");
        unionTest.removeAll(intersectionTest);
        printSet(unionTest);


        //  ContainAll -> returns true/false | it is non-destructive | tests for subsets
        if(nature.containsAll(divine)){
            System.out.println("divine is a subset of nature");
        }
        if(nature.containsAll(intersectionTest)){
            System.out.println("intersection is a subset of nature");
        }
        if(divine.containsAll(intersectionTest)){
            System.out.println("intersection is a subset of divine");
        }
    }

    private static void printSet(Set<String> set) {
        System.out.print("\t");
        for (String s : set) {
            System.out.print(s + " ");
        }
        System.out.println();
    }
}
