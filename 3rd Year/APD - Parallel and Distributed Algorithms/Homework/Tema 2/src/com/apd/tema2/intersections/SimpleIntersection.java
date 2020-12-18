package com.apd.tema2.intersections;

import java.util.concurrent.CyclicBarrier;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import static java.lang.Thread.sleep;

/**
 * Clasa care se ocupa de rezolvarea cerintei 1: simple_intersection
 */
public class SimpleIntersection implements Intersection {
    // bariera folosita in rezolvare
    private CyclicBarrier bar = new CyclicBarrier(Main.carsNo);

    public void handleCar(Car car) {
        // printez mesajul cand masina ajunge in intersectie
        System.out.println("Car " + car.getId() + " has reached the semaphore, now waiting...");

        // pentru sincronizarea masinilor
        try {
            bar.await();
        } catch (Exception e) {
            e.printStackTrace();
        }

        // fiecare masina asteapta un timp diferit
        try {
            sleep(car.getWaitingTime());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // printare mesaj dupa ce termina asteptarea
        System.out.println("Car " + car.getId() + " has waited enough, now driving...");
    }

    @Override
    public void setFirstArg(int arg) {
        // do nothing
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
