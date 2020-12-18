package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

/**
 * Clasa care se ocupa de rezolvarea cerintei 4: simple_strict_x_car_roundabout
 */
public class SimpleStrictXCarRoundabout implements Intersection {
    // numarul de benzi
    private int no_lanes;
    // timpul de asteptare
    private int wait_time;
    // numarul maxim de masini
    private int max_cars;
    // semafoarele la care asteapta in functie de banda
    private List<Semaphore> sems;
    // bariera initiala
    private CyclicBarrier initBar;
    // bariera de mijloc
    private CyclicBarrier enterBar;
    // bariera de iesire
    private CyclicBarrier exitBar;

    public void handleCar(Car car) {
        // printare mesaj daca a juns la sensul giratoriu
        System.out.println("Car " + car.getId() + " has reached the roundabout, now waiting...");

        // se asteapta la bariera initiala toate masinile
        try {
            initBar.await();
        } catch (Exception e) {
            e.printStackTrace();
        }

        // se incearca sa se intre folosind semaforul de pe banda corespunzatoare
        try {
            sems.get(car.getStartDirection()).acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // printare mesaj daca masina a fost selectata sa intre in intersectie
        System.out.println("Car " + car.getId() + " was selected to enter the roundabout from lane "
                + car.getStartDirection());

        // se asteapta si celelalte masini
        try {
            enterBar.await();
        } catch (Exception e) {
            e.printStackTrace();
        }

        // printare mesaj daca masina a intrat in intersectie
        System.out.println("Car " + car.getId() + " has entered the roundabout from lane "
                + car.getStartDirection());

        // asteptare in interesectie
        try {
            sleep(this.wait_time);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // printare mesaj daca masina a iesit din sens
        System.out.println("Car " + car.getId() + " has exited the roundabout after "
                + (wait_time / 1000) + " seconds");

        // se asteapta la bariera de iesire si celelalte masinia
        try {
            exitBar.await();
        } catch (Exception e) {
            e.printStackTrace();
        }

        // se elibereaza permit-ul luat
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
        // numarul maxim de masini
        this.max_cars = arg;

        // initializare semafoare
        sems = new ArrayList<>();
        for (int i = 0; i < this.no_lanes; ++i) {
            sems.add(new Semaphore(this.max_cars));
        }

        // initializare bariere
        initBar = new CyclicBarrier(Main.carsNo);
        enterBar = new CyclicBarrier(this.max_cars * this.no_lanes);
        exitBar = new CyclicBarrier(this.max_cars * this.no_lanes);
    }
}
