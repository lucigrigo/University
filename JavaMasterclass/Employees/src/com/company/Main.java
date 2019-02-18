package com.company;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.function.IntPredicate;
import java.util.function.Predicate;
import java.util.function.Supplier;

public class Main {

    public static void main(String[] args) {
        Employee john = new Employee("John Doe", 30);
        Employee marius = new Employee("Marius Viriginel", 100);
        Employee yo = new Employee("De la bloc", 3);
        Employee alba = new Employee("Alba-Iulia", 65);
        Employee adi = new Employee("Adi aditza", 23);
        Employee gogu = new Employee("Traqtor", 33);

        List<Employee> employees = new ArrayList<>();
        employees.add(john);
        employees.add(marius);
        employees.add(yo);
        employees.add(alba);
        employees.add(adi);
        employees.add(gogu);

        printEmployeesByAge(employees, "30 and under", employee -> employee.getAge() <= 30);
        printEmployeesByAge(employees, "older than 30", employee -> employee.getAge() > 30);
        printEmployeesByAge(employees, "younger than 25", new Predicate<Employee>() {
            @Override
            public boolean test(Employee employee) {
                return employee.getAge() < 25;
            }
        });

        /*
        IntPredicate greaterThan15 = i -> i > 15;
        IntPredicate lessThan100 = i -> i < 100;

        System.out.println(greaterThan15.test(10));
        int a = 20;
        System.out.println(greaterThan15.test(a + 5));

        System.out.println(greaterThan15.and(lessThan100).test(50));
        System.out.println(greaterThan15.and(lessThan100).test(15));
        */

        Random random = new Random();
        Supplier<Integer> randomSupplier = () -> random.nextInt(1000);
        for (int i = 0; i < 10; i++) {
//            System.out.println(random.nextInt(1000));
            System.out.println(randomSupplier.get());
        }
    }

    private static void printEmployeesByAge(List<Employee> employees,
                                            String ageText,
                                            Predicate<Employee> ageCondition) {
        System.out.println(ageText);
        System.out.println("=====================");
        for (Employee employee : employees) {
            if (ageCondition.test(employee)) {
                System.out.println(employee.getName());
            }
        }
    }
}