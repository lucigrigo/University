package com.luciangrigore;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Main {

    public static void main(String[] args) {
        List<String> someBingoNumbers = Arrays.asList(
                "N40", "N36",
                "B12", "B6",
                "G53", "G49", "G60", "G50", "g64",
                "I26", "I17", "I29",
                "071");

//        List<String> gNumbers = new ArrayList<>();
//
//        someBingoNumbers.forEach(number -> {
//            if (number.toUpperCase().startsWith("G")) {
//                gNumbers.add(number);
////                System.out.println(number);
//            }
//        });
//
//        gNumbers.sort((String s1, String s2) -> s1.compareTo(s2));
//        gNumbers.forEach(s1 -> System.out.println(s1));

        someBingoNumbers
                .stream()
                .map(String::toUpperCase)
                .filter(s -> s.startsWith("G"))
                .sorted()
                .forEach(System.out::println);

        Stream<String> ioNumberStream = Stream.of("I26", "I17", "I29", "O71");
        Stream<String> inNumberStream = Stream.of("N40", "N36", "I26", "I17", "I29", "O71");
        Stream<String> concatStream = Stream.concat(ioNumberStream, inNumberStream);
        System.out.println("================================");
        System.out.println(concatStream
                .distinct()
                .peek(System.out::println)
                .count());
        System.out.println("================================");

        Employee john = new Employee("John Doe", 30);
        Employee jane = new Employee("Jane Wilson", 25);
        Employee james = new Employee("James Peterson", 50);
        Employee jack = new Employee("Jack Sparrow", 38);
        Employee alex = new Employee("Alex Ferguson", 65);

        Department hr = new Department("Human Resources");
        hr.addEmployee(john);
        hr.addEmployee(jane);
        hr.addEmployee(james);
        Department accounting = new Department("Accounting");
        accounting.addEmployee(jack);
        accounting.addEmployee(alex);

        List<Department> departments = new ArrayList<>();
        departments.add(hr);
        departments.add(accounting);

        departments
                .stream()
                .flatMap(department -> department.getEmployees().stream())
                .forEach(System.out::println);
        System.out.println("================================");

//        List<String> sortedGNumbers = someBingoNumbers
//                .stream()
//                .map(String::toUpperCase)
//                .filter(s -> s.startsWith("G"))
//                .sorted()
//                .collect(Collectors.toList());

        List<String> sortedGNumbers = someBingoNumbers
                .stream()
                .map(String::toUpperCase)
                .filter(s -> s.startsWith("G"))
                .sorted()
                .collect(ArrayList::new, ArrayList::add, ArrayList::addAll);
        sortedGNumbers.forEach(System.out::println);
        System.out.println("================================");

        departments.stream()
                .flatMap(department -> department.getEmployees().stream())
                .reduce((e1, e2) -> e1.getAge() < e2.getAge() ? e1 : e2)
                .ifPresent(System.out::println);

        //  stream operations are lazily evaluated
        System.out.println("================================");
        Stream.of("A", "B", "C", "BAC", "ASDF", "ABC")
                .filter(s -> {
                    System.out.println(s);
                    return s.length() == 3;
                })
                .count();
    }
}
