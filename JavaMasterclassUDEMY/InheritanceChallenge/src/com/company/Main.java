package com.company;

public class Main {

    public static void main(String[] args) {
        Porsche car1 = new Porsche(9,260,"coupe",600,"911");
        System.out.println(car1.getHorsePower());
        System.out.println(car1.getModel());
        car1.speedUp(150);
    }
}
