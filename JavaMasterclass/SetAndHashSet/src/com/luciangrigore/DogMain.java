package com.luciangrigore;

public class DogMain {

    public static void main(String[] args) {

        //  The labrador is a dog instance, but not otherwise
        Labrador rover = new Labrador("Rover");
        Dog rover2 = new Dog("Rover");

        //  This test violates the simmetryc rule
        System.out.println(rover2.equals(rover));
        System.out.println(rover.equals(rover2));
    }
}
