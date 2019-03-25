package com.company;

public class Vehicle {

    private int gearsNumber, maximumSpeed, currentSpeed;
    private String name;

    public Vehicle(int gearsNumber, int maximumSpeed, String name) {
        this.gearsNumber = gearsNumber;
        this.maximumSpeed = maximumSpeed;
        this.currentSpeed = 0;
        this.name = name;
    }

    public int getGearsNumber() {
        return gearsNumber;
    }

    public int getMaximumSpeed() {
        return maximumSpeed;
    }

    public int getCurrentSpeed() {
        return currentSpeed;
    }

    public String getName() {
        return name;
    }

    public void setGearsNumber(int gearsNumber) {
        this.gearsNumber = gearsNumber;
    }

    public void setMaximumSpeed(int maximumSpeed) {
        this.maximumSpeed = maximumSpeed;
    }

    public void setCurrentSpeed(int currentSpeed) {
        this.currentSpeed = currentSpeed;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void speedUp(int speed) {
        this.currentSpeed += speed;
        System.out.println("Your speed increased to " + this.currentSpeed);
    }

    public void speedDown(int speed) {
        this.currentSpeed -= speed;
        System.out.println("Your speed decreased to " + this.currentSpeed);
    }
}
