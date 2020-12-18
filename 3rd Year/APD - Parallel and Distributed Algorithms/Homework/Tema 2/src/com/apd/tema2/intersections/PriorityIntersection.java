package com.apd.tema2.intersections;

import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

/**
 * Clasa care se ocupa de rezolvarea cerinte 6: priority_intersection
 */
public class PriorityIntersection implements Intersection {
    // numarul de masini cu prioritate
    private int noHighPrioCars;
    // numarul de masini fara prioritate
    private int noLowPrioCars;
    // semaforul intersectiei
    private Semaphore sem;

    public void handleCar(Car car) {
        if (car.getPriority() != 1) {
            // daca masina are prioritate mare

            // printeaza mesaj de intrare in intersectie
            System.out.println("Car " + car.getId() + " with high priority has entered the intersection");

            // incearca sa ia 1 permit din semafor
            try {
                sem.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // asteapta 2 secunde
            try {
                sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // printeaza mesaj de iesire din intersectie
            System.out.println("Car " + car.getId() + " with high priority has exited the intersection");

            // elibereaza permit-ul luat
            sem.release();
        } else {
            // daca masina nu are prioritate

            // printeaza mesaj de intrare
            System.out.println("Car " + car.getId() + " with low priority is trying to enter the intersection...");

            // incearca sa ia din semafor toate permiturile acestuia
            try {
                sem.acquire(this.noHighPrioCars);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // printeaza mesaj de trecere
            System.out.println("Car " + car.getId() + " with low priority has entered the intersection");

            // elibereaza permit-urile
            sem.release(this.noHighPrioCars);
        }
    }

    @Override
    public void setFirstArg(int arg) {
        // numarul de masini cu prioritate
        this.noHighPrioCars = arg;

        // initializare semafor cu acest numar
        sem = new Semaphore(this.noHighPrioCars);
    }

    @Override
    public void setSecondArg(int arg) {
        this.noLowPrioCars = arg;
    }

    @Override
    public void setThirdArg(int arg) {
        // do nothing
    }
}
