package com.apd.tema2.intersections;

import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

/**
 * Clasa care se ocupa de rezolvarea cerintei 3: simple_strict_1_car_roundabout
 */
public class SimpleStrict1CarRoundabout implements Intersection {
    // numarul de masini
    private int no_cars;
    // timpul de asteptare
    private int wait_time;
    // semafoarele pentru fiecare banda
    private List<Semaphore> sems;
    // bariera la care asteapta ca sa intre mai multe masini concomitent
    private CyclicBarrier bar;

    public void handleCar(Car car) {
        // printare mesaj ca a ajuns in intersectie
        System.out.println("Car " + car.getId() + " has reached the roundabout");

        // incearca sa ia 1 permit din semaforul corespunzator benzii de pe care a venit
        try {
            sems.get(car.getStartDirection()).acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // asteapta la bariera si alte masini daca a reusit sa ia permit-ul
        try {
            bar.await();
        } catch (Exception e) {
            e.printStackTrace();
        }

        // printare mesaj daca a intrat in intersectie
        System.out.println("Car " + car.getId() + " has entered the roundabout from lane "
                + car.getStartDirection());

        // asteapta o perioada de timp
        try {
            sleep(wait_time);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // printare mesaj daca a iesit din intersectie
        System.out.println("Car " + car.getId() + " has exited the roundabout after "
                + (wait_time / 1000) + " seconds");

        // elibereaza permit-ul luat
        sems.get(car.getStartDirection()).release();
    }

    @Override
    public void setFirstArg(int arg) {
        // initializare numar de masini
        this.no_cars = arg;

        // initializare semafoare
        sems = new ArrayList<>();
        for (int i = 0; i < arg; ++i) {
            sems.add(new Semaphore(1));
        }

        // initializare bariera
        bar = new CyclicBarrier(arg);
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
