package com.company;

class Car {
    private int engineCapacity, cylinders, wheels, currentSpeed;
    private String model;

    public Car(int engineCapacity, int cylinders, int currentSpeed) {
        this.engineCapacity = engineCapacity;
        this.cylinders = cylinders;
        this.wheels = 4;
        this.currentSpeed = currentSpeed;
        this.model = "No name given";
    }

    public void setEngineCapacity(int engineCapacity) {
        this.engineCapacity = engineCapacity;
    }

    public void setCylinders(int cylinders) {
        this.cylinders = cylinders;
    }

    public void setWheels(int wheels) {
        this.wheels = wheels;
    }

    public void setCurrentSpeed(int currentSpeed) {
        this.currentSpeed = currentSpeed;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getModel() {
        return model;
    }

    public int getEngineCapacity() {
        return engineCapacity;
    }

    public int getCylinders() {
        return cylinders;
    }

    public int getWheels() {
        return wheels;
    }

    public int getCurrentSpeed() {
        return currentSpeed;
    }

    public void startEngine() {
        System.out.println("Engine starting . . .");
    }

    public void accelerate(int speed) {
        this.currentSpeed += speed;
        System.out.println("Your car is accelerating !" +
                "\n Current speed is " + currentSpeed);
    }

    public void brake(int speed) {
        this.currentSpeed -= speed;
        System.out.println("Your car is braking !" +
                "\n Current speed is " + currentSpeed);
    }
}

class Lamborghini extends Car {
    private String series;

    public Lamborghini(String series) {
        super(6000, 8, 200);
        this.series = series;
        super.setModel("Lambo");
    }

    public void accelerate(int speed) {
        System.out.println("Your lambo is going fast skkkkrt skkkkrt");
    }
}

class RollsRoyce extends Car {
    private String series;

    public RollsRoyce(String series) {
        super(6750, 12, 120);
        this.series = series;
        super.setModel("Rolllllllssssss");
    }

    public void accelerate(int speed) {
        System.out.println("A gentleman in a Rolls has nowhere to rush #word");
    }
}

class BMW extends Car {
    private String series;

    public BMW(String series) {
        super(3000, 6, 150);
        this.series = series;
        super.setModel("Bemveu faã");
    }

    public void accelerate(int speed) {
        System.out.println("Unde te grabesti cocalare ?!");
    }
}

public class Main {

    public static Car randomCarGen() {
        int randomNumber = (int) (Math.random() * 3) + 1;
        switch (randomNumber) {
            case 1:
                return new Lamborghini("Urus");
            case 2:
                return new BMW("Septar");
            case 3:
                return new RollsRoyce("Phantom");
        }
        return null;
    }

    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            Car newCar = randomCarGen();
            System.out.println("Car #" + i + " is " + newCar.getModel() +
                    "\n let's go ");
            newCar.accelerate(50);
        }
    }
}
