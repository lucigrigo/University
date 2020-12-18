package com.apd.tema2.factory;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Pedestrians;
import com.apd.tema2.entities.ReaderHandler;

import java.io.BufferedReader;
import java.io.IOException;

/**
 * Returneaza sub forma unor clase anonime implementari pentru metoda de citire din fisier.
 */
public class ReaderHandlerFactory {

    public static ReaderHandler getHandler(String handlerType) {
        /**
         * Pentru fiecare tip de intersectie, ma asigur ca setez tipul de intersectie corespunzator.
         * Acolo unde este cazul, citesc din input ultima linie de parametrii aditionali si ii
         * comunic intersectiei curente.
         */
        return switch (handlerType) {
            case "simple_semaphore" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) {
                    Main.intersection =
                            IntersectionFactory.getIntersection("simple_intersection");
                }
            };
            case "simple_n_roundabout" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    String[] line = br.readLine().split(" ");
                    int n = Integer.parseInt(line[0]);
                    int t = Integer.parseInt(line[1]);
                    Main.intersection =
                            IntersectionFactory.getIntersection("simple_n_roundabout");
                    Main.intersection.setFirstArg(n);
                    Main.intersection.setSecondArg(t);
                }
            };
            case "simple_strict_1_car_roundabout" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    String[] line = br.readLine().split(" ");
                    int n = Integer.parseInt(line[0]);
                    int t = Integer.parseInt(line[1]);
                    Main.intersection =
                            IntersectionFactory.getIntersection("simple_strict_1_car_roundabout");
                    Main.intersection.setFirstArg(n);
                    Main.intersection.setSecondArg(t);
                }
            };
            case "simple_strict_x_car_roundabout" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    String[] line = br.readLine().split(" ");
                    int n = Integer.parseInt(line[0]);
                    int t = Integer.parseInt(line[1]);
                    int m = Integer.parseInt(line[2]);
                    Main.intersection =
                            IntersectionFactory.getIntersection("simple_strict_x_car_roundabout");
                    Main.intersection.setFirstArg(n);
                    Main.intersection.setSecondArg(t);
                    Main.intersection.setThirdArg(m);
                }
            };
            case "simple_max_x_car_roundabout" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    String[] line = br.readLine().split(" ");
                    int n = Integer.parseInt(line[0]);
                    int t = Integer.parseInt(line[1]);
                    int m = Integer.parseInt(line[2]);
                    Main.intersection =
                            IntersectionFactory.getIntersection("simple_max_x_car_roundabout");
                    Main.intersection.setFirstArg(n);
                    Main.intersection.setSecondArg(t);
                    Main.intersection.setThirdArg(m);
                }
            };
            case "priority_intersection" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    String[] line = br.readLine().split(" ");
                    int n = Integer.parseInt(line[0]);
                    int m = Integer.parseInt(line[1]);
                    Main.intersection =
                            IntersectionFactory.getIntersection("priority_intersection");
                    Main.intersection.setFirstArg(n);
                    Main.intersection.setSecondArg(m);
                }
            };
            case "crosswalk" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    Main.intersection =
                            IntersectionFactory.getIntersection("crosswalk");
                    Main.intersection.setFirstArg(Main.carsNo);
                    String[] line = br.readLine().split(" ");
                    int n = Integer.parseInt(line[0]);
                    int m = Integer.parseInt(line[1]);
                    Main.pedestrians = new Pedestrians(n, m);
                }
            };
            case "simple_maintenance" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    Main.intersection =
                            IntersectionFactory.getIntersection("simple_maintenance");
                    String[] line = br.readLine().split(" ");
                    int n = Integer.parseInt(line[0]);
                    Main.intersection.setFirstArg(n);
                }
            };
            case "complex_maintenance" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    String[] line = br.readLine().split(" ");
                    int n = Integer.parseInt(line[0]);
                    int t = Integer.parseInt(line[1]);
                    int m = Integer.parseInt(line[2]);
                    Main.intersection =
                            IntersectionFactory.getIntersection("complex_maintenance");
                    Main.intersection.setFirstArg(n);
                    Main.intersection.setSecondArg(t);
                    Main.intersection.setThirdArg(m);
                }
            };
            case "railroad" ->new ReaderHandler() {
                @Override
                public void handle(final String handlerType, final BufferedReader br) throws IOException {
                    Main.intersection =
                            IntersectionFactory.getIntersection("railroad");
                    Main.intersection.setFirstArg(2); // folosit pentru initializare de variabile
                }
            };
            default ->null;
        } ;
    }

}
