package com.apd.tema2.factory;

import com.apd.tema2.Main;
import com.apd.tema2.entities.*;

import static java.lang.Thread.sleep;

/**
 * Clasa Factory ce returneaza implementari ale InterfaceHandler sub forma unor
 * clase anonime.
 */
public class IntersectionHandlerFactory {

    public static IntersectionHandler getHandler(String handlerType) {
        /**
         * Pentru fiecare tip de intersectie apelez functia de handle pe masina curenta
         * din intersectia curenta.
         * Aditional, acolo unde au fost plasate sleep-uri in schelet, le-am lasat
         * inaintea acestui apel pentru a intarzia masinile diferit.
         */
        return switch (handlerType) {
            case "simple_semaphore" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    Main.intersection.handleCar(car);
                }
            };
            case "simple_n_roundabout" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    Main.intersection.handleCar(car);
                }
            };
            case "simple_strict_1_car_roundabout" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    Main.intersection.handleCar(car);
                }
            };
            case "simple_strict_x_car_roundabout" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    Main.intersection.handleCar(car);
                }
            };
            case "simple_max_x_car_roundabout" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    // sleep-ul din schelet inainte ca o masina sa intre in intersectie
                    try {
                        sleep(car.getWaitingTime());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    Main.intersection.handleCar(car);
                }
            };
            case "priority_intersection" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    // sleep-ul din schelet inainte ca o masina sa intre in intersectie
                    try {
                        sleep(car.getWaitingTime());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    Main.intersection.handleCar(car);
                }
            };
            case "crosswalk" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    Main.intersection.handleCar(car);
                }
            };
            case "simple_maintenance" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    Main.intersection.handleCar(car);
                }
            };
            case "complex_maintenance" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    Main.intersection.handleCar(car);
                }
            };
            case "railroad" ->new IntersectionHandler() {
                @Override
                public void handle(Car car) {
                    Main.intersection.handleCar(car);
                }
            };
            default ->null;
        } ;
    }
}
