package com.apd.tema2.intersections;

import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

/**
 * Clasa care se ocupa de rezolvarea cerintei 2: simple_n_roundabout
 */
public class SimpleNRoundabout implements Intersection {
    // numarul de masini
    private int no_cars;
    // timpul de asteptare in sens
    private int wait_time;
    // semaforul din intersectie
    private Semaphore sem;

    public void handleCar(Car car) {
        // printare mesaj ca a ajuns in intersectie
        System.out.println("Car " + car.getId() +
                " has reached the roundabout, now waiting...");

        // incearca sa intre in intersectie
        try {
            sem.acquire();
        } catch (InterruptedException ie) {
            ie.printStackTrace();
        }

        // printare mesaj daca a reusit sa intre in intersectie
        System.out.println("Car " + car.getId() + " has entered the roundabout");

        // asteapta un timp fix in intersectie
        try {
            sleep(wait_time);
        } catch (InterruptedException ie) {
            ie.printStackTrace();
        }

        // printare mesaj daca a iesit din intersectie
        System.out.println("Car " + car.getId() + " has exited the roundabout after " + (wait_time / 1000) + " seconds");

        // elibereaza permit-ul luat
        sem.release();
    }

    @Override
    public void setFirstArg(int arg) {
        // numarul de masini
        this.no_cars = arg;

        // initializare semafor
        this.sem = new Semaphore(this.no_cars);
    }

    @Override
    public void setSecondArg(int arg) {
        // timpul de asteptare
        this.wait_time = arg;
    }

    @Override
    public void setThirdArg(int arg) {
        // do nothing
    }
}
