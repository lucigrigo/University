package com.apd.tema2.intersections;

import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

/**
 * Clasa care se ocupa de rezolvarea cerinte 8: simple_maintenance
 */
public class SimpleMaintenance implements Intersection {
    // numarul maxim de masini
    private int maxCars;
    // semaforul pentru primul sens
    private Semaphore firstLaneSem;
    // semaforul pentru al doilea sens
    private Semaphore secondLaneSem;
    // bariera la care se asteapta maxCars masini
    private CyclicBarrier bar;

    public void handleCar(Car car) {
        // printare mesaj cand masina ajunge in intersectie
        System.out.println("Car " + car.getId() + " from side number "
                + car.getStartDirection() + " has reached the bottleneck");

        /*
         verific directia din care vine masina si in functie de aceasta
         incerc sa iau 1 permit din semaforul corespunzator
          */
        if (car.getStartDirection() == 0) {
            try {
                firstLaneSem.acquire(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } else {
            try {
                secondLaneSem.acquire(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // printez mesajul daca masina curenta a trecut de ingustare
        System.out.println("Car " + car.getId() + " from side number "
                + car.getStartDirection() + " has passed the bottleneck");

        // la aceasta bariera astept mereu maxCars masini
        try {
            bar.await();
        } catch (BrokenBarrierException | InterruptedException e) {
            e.printStackTrace();
        }

        // pentru fiecare masina, eliberez pentru celalt sens 1 permit
        if (car.getStartDirection() == 0) {
            secondLaneSem.release(1);
        } else {
            firstLaneSem.release(1);
        }
    }

    @Override
    public void setFirstArg(int arg) {
        /*
        initializare variabile:
        - numarul maxim de masini care trece o data de pe un sens
        - bariera
        - semafoarele pentru fiecare sens, initializate astfel incat sa treaca prima data masinile
        de pe sensul 0
         */
        this.maxCars = arg;
        bar = new CyclicBarrier(this.maxCars);
        firstLaneSem = new Semaphore(this.maxCars);
        secondLaneSem = new Semaphore(0);
    }

    @Override
    public void setSecondArg(int arg) {
        // do nothing
    }

    @Override
    public void setThirdArg(int arg) {
        // do nothing
    }
}
