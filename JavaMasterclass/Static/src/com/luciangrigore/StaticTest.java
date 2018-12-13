package com.luciangrigore;

public class StaticTest {

    //  A static variable has a single place in memory
    //  all the references to that variable point to that place in memory
    private static int numInstances = 0;
    private String name;

    public StaticTest(String name) {
        this.name = name;
        numInstances++;
    }

    //  A static method can be accessed without any instance of a class
    public static int getNumInstances() {
        return numInstances;
    }

    public String getName() {
        return name;
    }
}
