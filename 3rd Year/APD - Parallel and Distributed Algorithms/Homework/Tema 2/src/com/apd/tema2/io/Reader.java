package com.apd.tema2.io;

import com.apd.tema2.Main;
import com.apd.tema2.entities.ReaderHandler;
import com.apd.tema2.factory.CarFactory;
import com.apd.tema2.factory.ReaderHandlerFactory;

import java.io.*;
import java.util.HashSet;
import java.util.Set;

/**
 * Clasa de baza care va realiza citirea.
 */
public class Reader {
    private BufferedReader br;

    private static Reader instance;

    private Reader(final String filePath) {
        try {
            File file = new File(filePath);
            br = new BufferedReader(new FileReader(file));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static Reader getInstance(final String filePath) {
        if(instance == null) {
            instance = new Reader(filePath);
        }

        return instance;
    }

    public Set<Thread> getCarsFromInput() {
        Set<Thread> cars = new HashSet<>();

        try {
            String handlerType = br.readLine();
            ReaderHandler readerHandler = ReaderHandlerFactory.getHandler(handlerType);

            Main.carsNo = Integer.parseInt(br.readLine());
            for (int i = 0; i != Main.carsNo; ++i) {
                cars.add(new Thread(CarFactory.getCar(handlerType, br.readLine().split(" "))));
            }

            readerHandler.handle(handlerType, br);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return cars;
    }


}
