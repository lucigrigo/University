package com.company;

public class Car extends Vehicle {

    public String typeOfCar;

    public Car(int gearsNumber, int maximumSpeed, String name, String typeOfCar) {
        super(gearsNumber, maximumSpeed, name);
        this.typeOfCar = typeOfCar;
    }

    public String getTypeOfCar() {
        return typeOfCar;
    }

    public void setTypeOfCar(String typeOfCar) {
        this.typeOfCar = typeOfCar;
    }

    public void gearUP() {
        System.out.println("Gear changed up");
    }

    public void gearDown() {
        System.out.println("Gear changed down");
    }
}
