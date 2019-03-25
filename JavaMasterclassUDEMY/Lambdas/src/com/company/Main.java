package com.company;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        new Thread(() -> {
            System.out.println("Printing from the runnable");
            System.out.println("another line printed");
            System.out.println("the third and final line");
            System.out.println("\n\n\n\n");
        }).start();

        Employee john = new Employee("John Doe", 30);
        Employee marius = new Employee("Marius Viriginel", 100);
        Employee yo = new Employee("De la bloc", 3);
        Employee alba = new Employee("Alba-Iulia", 65);

        List<Employee> employees = new ArrayList<>();
        employees.add(john);
        employees.add(marius);
        employees.add(yo);
        employees.add(alba);

//        Collections.sort(employees, new Comparator<Employee>() {
//            @Override
//            public int compare(Employee o1, Employee o2) {
//                return o1.getName().compareTo(o2.getName());
//            }
//        });

        Collections.sort(employees, (o1, o2) ->
                o1.getName().compareTo(o2.getName()));

        for (Employee employee : employees) {
            System.out.println(employee.getName());
            new Thread(() -> System.out.println(employee.getAge())).start();
        }

        System.out.println("=============");

        employees.forEach(employee -> {
            System.out.println(employee.getName());
            System.out.println(employee.getAge());
        });

//        String sillyString = doStringStuff(new UpperConcat() {
//            @Override
//            public String upperAndConcat(String s1, String s2) {
//                return s1.toUpperCase() + s2.toUpperCase();
//            }
//        }, employees.get(0).getName(), employees.get(1).getName());
//        System.out.println(sillyString);

        UpperConcat uc = (s1, s2) -> {
            String result = s1.toUpperCase() + s2.toUpperCase();
            return result;
        };
        String sillyString = doStringStuff(uc, employees.get(0).getName(),
                employees.get(2).getName());
        System.out.println("\n\n" + sillyString + "\n\n");

        AnotherClass anotherClass = new AnotherClass();
        String s = anotherClass.doSomething();
        System.out.println(s);
    }

    public final static String doStringStuff(UpperConcat uc, String s1, String s2) {
        return uc.upperAndConcat(s1, s2);
    }
}

class Employee {
    private String name;
    private int age;

    public Employee(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}

interface UpperConcat {
    public String upperAndConcat(String s1, String s2);
}

class AnotherClass {

    public String doSomething() {
//        UpperConcat uc = (s1, s2) -> {
//            System.out.println("The lambda expression's name is: " +
//                    getClass().getSimpleName());
//            String result = s1.toUpperCase() + s2.toUpperCase();
//            return result;
//        };
        int count = 0;

        count += 5;

        UpperConcat uc = (s1, s2) -> {
            System.out.println("The lambda expr's class is " + getClass().getSimpleName());
//            System.out.println("count from lambda = " + count);
            String result = s1.toUpperCase() + s2.toUpperCase();
            return result;
        };

//        UpperConcat uc = new UpperConcat() {
//            @Override
//            public String upperAndConcat(String s1, String s2) {
//                System.out.println("count (from anonymous class) = " + count);
//                return s1.toUpperCase() + s2.toUpperCase();
//            }
//        };

        System.out.println("The AnotherClass class's name is: " +
                getClass().getSimpleName());

//            count += 5;
        System.out.println("count = " + count);
        return Main.doStringStuff(uc, "String1", "String2");
    }
//
//        System.out.println("The AnotherClass's name is: " + getClass().getSimpleName());
//        return Main.doStringStuff(new UpperConcat() {
//            @Override
//            public String upperAndConcat(String s1, String s2) {
//                System.out.println("The anonymous class's name is: " +
//                        getClass().getSimpleName());
//                return s1.toUpperCase() + s2.toUpperCase();
//            }
//        }, "String 1", "String 2");
//    }

    public void printValue() {
        int number = 25;

        Runnable r = () -> {
            try {
                Thread.sleep(5000);
            } catch (InterruptedException ie) {
                ie.printStackTrace();
            }
            System.out.println("The value is " + number);
        };

        new Thread(r).start();
    }
}
