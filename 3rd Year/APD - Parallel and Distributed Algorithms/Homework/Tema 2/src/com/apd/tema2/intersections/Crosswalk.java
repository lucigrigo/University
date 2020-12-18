package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CyclicBarrier;

/**
 * Clasa care se ocupa de rezolvarea cerintei 7: crosswalk
 */
public class Crosswalk implements Intersection {
    // folosita pentru a memora tipul ultimului mesaj trimis de fiecare thread
    private ConcurrentHashMap<Integer, Boolean> isLastMessageGreen;

    public void handleCar(Car car) {
        // cand ajunge in intersectie masina executa in bucla aceste actiuni
        while (true) {
            boolean pass = Main.pedestrians.isPass();
            if (!isLastMessageGreen.get(car.getId()) && !pass) {
                // testez daca ar trebui sa trec prin intersecie
                System.out.println("Car " + car.getId() + " has now green light");
                isLastMessageGreen.replace(car.getId(), true);
            } else if (isLastMessageGreen.get(car.getId()) && pass) {
                // testez daca ar trebui sa ma opresc la trecerea de pietoni
                System.out.println("Car " + car.getId() + " has now red light");
                isLastMessageGreen.replace(car.getId(), false);
            }

            /* am evitat sa fac busy waiting folosind wait() si notify()
               intre masini si pietoni */
            try {
                synchronized (Main.pedestrians.bell) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            } catch (IllegalMonitorStateException e) {
                // be silent until we get the lock of the object
            }

            // verific daca pietonii au terminat de trecut
            if (Main.pedestrians.isFinished())
                break;
        }

        // ma asigur ca ultimul mesaj printat a fost cel de trecere
        if (!isLastMessageGreen.get(car.getId())) {
            System.out.println("Car " + car.getId() + " has now green light");
        }
    }

    @Override
    public void setFirstArg(int arg) {
        // initializez istoricul mesajelor
        isLastMessageGreen = new ConcurrentHashMap<>();
        for (int i = 0; i < arg; ++i) {
            isLastMessageGreen.put(i, false);
        }
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
