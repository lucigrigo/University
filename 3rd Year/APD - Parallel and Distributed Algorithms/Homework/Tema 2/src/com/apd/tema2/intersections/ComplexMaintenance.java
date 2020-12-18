package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Clasa care se ocupa de rezolvarea cerintei 9: complex_intersection
 */
public class ComplexMaintenance implements Intersection {
    // numarul de benzi noi
    private int noNewLanes;
    // numarul de benzi vechi
    private int noOldLanes;
    // numarul maxim de masini pe fiecare banda noua
    private int maxCarsPerLane;
    // bariera la care asteapta masinile cand ajung in intersectie
    private CyclicBarrier bar;
    // folosit pentru asignarea benzilor
    private int[] newLanes;
    // folosit pentru a tine ordinea benzilor vechi care intra pe aceeasi banda noua
    private ConcurrentHashMap<Integer, List<Integer>> oldLanesPriority;
    // folosit pentru a monitoriza flow-ul de trafic pe fiecare banda noua
    private ConcurrentHashMap<Integer, Semaphore> sems;
    // folosit pentru asignarea unui numar de ordine pe fiecare banda veche
    private ConcurrentHashMap<Integer, AtomicInteger> prios;
    // folosit pentru alegerea unei ordini a masinilor care intra pe o banda noua
    private ConcurrentHashMap<Integer, AtomicInteger> nowEntering;
    // folosit pentru a contoriza toate masinile de pe fiecare banda
    private ConcurrentHashMap<Integer, AtomicInteger> noCars;
    // folosit pentru a numara cate masini au trecut la un moment de timp
    private ConcurrentHashMap<Integer, AtomicInteger> noCarsPassed;
    /*
       folosit ca lock pentru a evita ca 2 citiri de la masini de pe benzi diferite
       sa fie valide cand ar trebui sa se schimbe banda veche care intra in una noua
    */
    private final Object lock = new Object();

    public void handleCar(Car car) {
        // printare mesaj initial
        System.out.println("Car " + car.getId()
                + " has come from the lane number " + car.getStartDirection());

        // primesc numarul de ordine propriu
        int ownPrio = prios.get(car.getStartDirection()).incrementAndGet();
        // noua banda pe care voi intra
        int newLane = newLanes[car.getStartDirection()];
        // incrementez numarul de masini total de pe banda de pe care am venit
        noCars.get(car.getStartDirection()).incrementAndGet();

        // asteptarea tuturor masinilor sa ajunga la ingustare
        try {
            bar.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        // dupa bariera, pun masinile in busy waiting
        while (true) {
            // do nothing -- wait
            synchronized (lock) {
                try {
                    /* testez daca este randul meu sa intru si daca banda de pe care vin
                       este cea curenta */
                    if (nowEntering.get(car.getStartDirection()).get() == ownPrio &&
                            oldLanesPriority.get(newLane).get(0) == car.getStartDirection())
                        break;
                } catch (Exception e) {
                    // be silent
                    /*
                    uneori in timpul eliminarii de la linie 112, acest get(0) nu indica nimic pana
                    se restabileste ordinea in lista, asa ca primesc la anumite momente de timp
                    NoSuchElementException
                     */
                }
            }
        }

        // iar un loc din cele ramase
        try {
            sems.get(newLane).acquire(1);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // printez mesajul ca am intrat pe noua banda
        System.out.println("Car " + car.getId() + " from the lane "
                + car.getStartDirection() + " has entered lane number " + newLane);
        // incrementez numarul total de masini care au trecut
        noCarsPassed.get(car.getStartDirection()).incrementAndGet();

        // testez daca au trecut maxCars de pe banda veche curenta sau daca ea s-a terminat
        if (sems.get(newLane).availablePermits() == 0 ||
                noCars.get(car.getStartDirection()).get() ==
                        noCarsPassed.get(car.getStartDirection()).get()) {
            if (noCars.get(car.getStartDirection()).get() ==
                    noCarsPassed.get(car.getStartDirection()).get()) {
                // daca au trecut toate masinile de pe banda veche curenta, o elimin
                System.out.println("The initial lane " + car.getStartDirection()
                        + " has been emptied and removed from the new lane queue");
                oldLanesPriority.get(newLane).remove(0);
            } else {
                // daca banda curenta si-a terminat permit-urile, afisez mesajul corespunzator
                System.out.println("The initial lane " + car.getStartDirection()
                        + " has no permits and is moved to the back of the new lane queue");
                // o mut la capatul cozii
                Integer old = oldLanesPriority.get(newLane).get(0);
                oldLanesPriority.get(newLane).remove(0);
                oldLanesPriority.get(newLane).add(old);
            }
            // restabilesc semaforul de pe banda noua curenta
            try {
                sems.get(newLane).acquire(sems.get(newLane).availablePermits());
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            sems.get(newLane).release(this.maxCarsPerLane);
        }

        // las urmatoarea masina sa treaca de pe banda de pe care am venit
        nowEntering.get(car.getStartDirection()).incrementAndGet();
    }

    @Override
    public void setFirstArg(int arg) {
        // numarul de benzi noi
        this.noNewLanes = arg;
    }

    @Override
    public void setSecondArg(int arg) {
        // numarul de benzi vechi
        this.noOldLanes = arg;

        // aici atribui benzile vechi celor noi conform start-stop din lab 1
        newLanes = new int[this.noOldLanes];
        for (int i = 0; i < this.noNewLanes; ++i) {
            int start = i * this.noOldLanes / this.noNewLanes;
            int end = Math.min(this.noOldLanes, (i + 1) * this.noOldLanes / this.noNewLanes);

            for (int j = start; j < end; ++j) {
                newLanes[j] = i;
            }
        }

        // initializez prioritatile pentru benzile vechi
        this.prios = new ConcurrentHashMap<>();
        for (int i = 0; i < this.noOldLanes; ++i) {
            prios.put(i, new AtomicInteger(0));
        }

        // initializez ordinea de intrare de pe benzile vechi
        this.nowEntering = new ConcurrentHashMap<>();
        for (int i = 0; i < this.noOldLanes; ++i) {
            nowEntering.put(i, new AtomicInteger(1));
        }

        // numarul total de masini
        this.noCars = new ConcurrentHashMap<>();
        for (int i = 0; i < this.noOldLanes; ++i) {
            this.noCars.put(i, new AtomicInteger(0));
        }

        // numarul total de masini care au trecut la un moment dat
        this.noCarsPassed = new ConcurrentHashMap<>();
        for (int i = 0; i < this.noOldLanes; ++i) {
            this.noCarsPassed.put(i, new AtomicInteger(0));
        }
    }

    @Override
    public void setThirdArg(int arg) {
        // numarul maxim de masini care sa intre de pe o banda veche pe una noua
        this.maxCarsPerLane = arg;
        // bariera initiala
        this.bar = new CyclicBarrier(Main.carsNo);

        // lista cu ordinea de intrare a benzilor
        this.oldLanesPriority = new ConcurrentHashMap<>();
        for (int i = 0; i < this.noNewLanes; ++i) {
            oldLanesPriority.put(i, new ArrayList<>());

            for (int j = 0; j < this.noOldLanes; ++j) {
                if (this.newLanes[j] == i) {
                    oldLanesPriority.get(i).add(j);
                }

            }
        }

        // semafoarele de pe fiecare banda noua
        sems = new ConcurrentHashMap<>();
        for (int i = 0; i < this.noNewLanes; ++i) {
            sems.put(i, new Semaphore(this.maxCarsPerLane));
        }
    }
}
