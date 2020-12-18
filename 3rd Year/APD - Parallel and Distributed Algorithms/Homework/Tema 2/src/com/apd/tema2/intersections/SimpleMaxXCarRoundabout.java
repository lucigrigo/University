package com.apd.tema2.intersections;

import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

/**
 * Clasa care se ocupa de rezolvarea cerinte 5: simple_max_x_car_roundabout
 */
public class SimpleMaxXCarRoundabout implements Intersection {
    // numarul de benzi
    private int no_lanes;
    // numarul maxim de masini
    private int max_cars;
    // timpul de asteptare pentru o masina in sensul giratoriu
    private int wait_time;
    // semafoarele pentru fiecare banda
    private List<Semaphore> sems;

    public void handleCar(Car car) {
        // mesajul de asteptare la sens printat de o masina
        System.out.println("Car " + car.getId() +
                " has reached the roundabout from lane " + car.getStartDirection());

        // asteptare la semafor pentru banda de pe care vine
        try {
            sems.get(car.getStartDirection()).acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // printare mesaj de intrare in sens
        System.out.println("Car " + car.getId() + " has entered the roundabout from lane "
                + car.getStartDirection());

        // masina asteapta wait_time milisecunde in sens
        try {
            sleep(wait_time);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // printare mesaj de iesire din sens
        System.out.println("Car " + car.getId() + " has exited the roundabout after "
                + (wait_time / 1000) + " seconds");

        // eliberare permit pentru semaforul corespunzator
        sems.get(car.getStartDirection()).release();
    }

    @Override
    public void setFirstArg(int arg) {
        // numarul de benzi
        this.no_lanes = arg;
    }

    @Override
    public void setSecondArg(int arg) {
        // timpul de asteptare
        this.wait_time = arg;
    }

    @Override
    public void setThirdArg(int arg) {
        // numarul maxim de masini de pe fiecare banda
        this.max_cars = arg;

        // initializare semafoare
        sems = new ArrayList<>();
        for (int i = 0; i < this.no_lanes; ++i) {
            sems.add(new Semaphore(this.max_cars));
        }
    }
}
