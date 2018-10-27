package com.company;

public class Main {

    public static void main(String[] args) {
        Car porsche = new Car();
        Car bmw = new Car();
        porsche.setModel("Panamera");
        bmw.setModel("5series");
        System.out.println(porsche.getModel());
        System.out.println(bmw.getModel());

    }
}
