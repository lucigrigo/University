package com.apd.tema2.entities;

import com.apd.tema2.utils.Constants;

import java.util.concurrent.atomic.AtomicBoolean;

import static java.lang.Thread.sleep;

/**
 * Clasa utilizata pentru gestionarea oamenilor care se strang la trecerea de pietoni.
 */
public class Pedestrians implements Runnable {
    private int pedestriansNo = 0;
    private int maxPedestriansNo;
    /*
    am schimbat variabilele 'pass' si 'finished' sa fie de tip AtomicBoolean doar
    ca sa fiu eu impacat cu thread-safeness-ul operatiilor, desi stiu ca aceste
    variabile vor fi doar CITITE de mai multe thread-uri si modificate doar de
    thread-ul acesta - Pedestrians
     */
    private AtomicBoolean pass = new AtomicBoolean(false);
    private AtomicBoolean finished = new AtomicBoolean(false);
    private int executeTime;
    private long startTime;
    /*
    obiect folosit ca lock pentru wait() si notify() folosite de masini,
    respectiv, de pietoni
     */
    public final Object bell = new Object();

    public Pedestrians(int executeTime, int maxPedestriansNo) {
        this.startTime = System.currentTimeMillis();
        this.executeTime = executeTime;
        this.maxPedestriansNo = maxPedestriansNo;
    }

    @Override
    public void run() {
        while (System.currentTimeMillis() - startTime < executeTime) {
            try {
                pedestriansNo++;
                sleep(Constants.PEDESTRIAN_COUNTER_TIME);

                if (pedestriansNo == maxPedestriansNo) {
                    pedestriansNo = 0;
                    pass.set(true);
                    // anunt thread-urile ca pietonii trec
                    try {
                        synchronized (bell) {
                            notify();
                        }
                    } catch (IllegalMonitorStateException e) {
                        // be silent until we get the lock of the object
                    }
                    sleep(Constants.PEDESTRIAN_PASSING_TIME);
                    pass.set(false);
                    // anunt thread-urile ca pietonii au terminat de trecut
                    try {
                        synchronized (bell) {
                            notify();
                        }
                    } catch (IllegalMonitorStateException e) {
                        // be silent until we get the lock of the object
                    }
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        finished.set(true);
        // anunt thread-urile ca toti pietonii au terminat de trecut
        try {
            synchronized (bell) {
                notify();
            }
        } catch (IllegalMonitorStateException e) {
            // be silent until we get the lock of the object
        }
    }

    public boolean isPass() {
        return pass.get();
    }

    public boolean isFinished() {
        return finished.get();
    }
}
