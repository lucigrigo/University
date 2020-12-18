package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Clasa care se ocupa de rezolvarea cerinte 10: railroad
 */
public class Railroad implements Intersection {
    // bariera la care asteapta initial toate masinile
    private CyclicBarrier bar;
    // prioritatea de intrare in intersectie
    private AtomicInteger prio;
    // folosita pentru a indica ce masina trebuie sa treaca la un moment de timp
    private AtomicInteger currentPrio;

    public void handleCar(Car car) {
        // mesaj printat cand masina a juns la calea ferata
        System.out.println("Car " + car.getId() + " from side number "
                + car.getStartDirection() + " has stopped by the railroad");

        // prioritatea masinii curente
        int ownPrio = prio.incrementAndGet();

        // asteapta la bariera toate masinile
        try {
            bar.await();
        } catch (BrokenBarrierException | InterruptedException e) {
            e.printStackTrace();
        }

        // numai o masina printeaza acest mesaj
        if (ownPrio == 1) {
            System.out.println("The train has passed, cars can now proceed");
        }

        // asteapta la bariera toate masinile
        try {
            bar.await();
        } catch (BrokenBarrierException | InterruptedException e) {
            e.printStackTrace();
        }

        // dupa bariera, masinile intra in busy waiting pana le vine randul
        while (ownPrio != currentPrio.get()) ;

        // printeaza mesajul de iesire
        System.out.println("Car " + car.getId() + " from side number "
                + car.getStartDirection() + " has started driving");

        // incrementeaza numarul masinii care trebuie sa treaca la momentul urmator
        currentPrio.incrementAndGet();
    }

    @Override
    public void setFirstArg(int arg) {
        /*
         initializare variabile folosite
         - prioritatile la venire si la trecere
         - bariera
          */
        prio = new AtomicInteger(0);
        currentPrio = new AtomicInteger(1);
        bar = new CyclicBarrier(Main.carsNo);
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
