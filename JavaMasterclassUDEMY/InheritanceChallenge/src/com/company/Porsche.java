package com.company;

public class Porsche extends Car {

    public int horsePower;
    public String model;

    public Porsche(int gearsNumber, int maximumSpeed
            , String typeOfCar, int horsePower, String model) {
        super(gearsNumber, maximumSpeed, "Porsche", typeOfCar);
        this.horsePower = horsePower;
        this.model = model;
    }

    public int getHorsePower() {
        return horsePower;
    }

    public String getModel() {
        return model;
    }

    public void setHorsePower(int horsePower) {
        this.horsePower = horsePower;
    }

    public void setModel(String model) {
        this.model = model;
    }

    @Override
    public void gearUP() {
        System.out.println("Your Porsche" + model);
        super.gearUP();
    }

    @Override
    public void gearDown() {
        System.out.println("Your Porsche " + model);
        super.gearDown();
    }

    @Override
    public void speedUp(int speed) {
        System.out.println("Your Porsche " + model + " is going faster!");
        super.speedUp(speed);
    }

    @Override
    public void speedDown(int speed) {
        System.out.println("Your Porsche " + model + " is going slower!");
        super.speedDown(speed);
    }
}
