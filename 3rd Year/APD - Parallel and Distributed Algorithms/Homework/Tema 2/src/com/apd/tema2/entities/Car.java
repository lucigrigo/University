package com.apd.tema2.entities;

/**
 * Clasa Thread principala.
 */
public class Car implements Runnable {
    private final int id;
    private final int startDirection;
    private final int endDirection;
    private final int priority;
    private final int waitingTime;
    private final IntersectionHandler intersectionHandler;

    public Car(final int id, final int startDirection, final IntersectionHandler intersectionHandler) {
        this(id, startDirection, -1, 0, intersectionHandler, 1);
    }

    public Car(final int id, final int startDirection, final int waitingTime, final IntersectionHandler intersectionHandler) {
        this(id, startDirection, -1, waitingTime, intersectionHandler, 1);
    }

    public Car(final int id, final int startDirection, final int endDirection, final int waitingTime, final IntersectionHandler intersectionHandler) {
        this(id, startDirection, endDirection, waitingTime, intersectionHandler, 1);
    }

    public Car(final int id, final int startDirection, final int endDirection, final int waitingTime, IntersectionHandler intersectionHandler, final int priority) {
        this.id = id;
        this.startDirection = startDirection;
        this.endDirection = endDirection;
        this.waitingTime = waitingTime;
        this.intersectionHandler = intersectionHandler;
        this.priority = priority;
    }

    @Override
    public void run() {
        intersectionHandler.handle(this);
    }

    public int getId() {
        return id;
    }

    public int getStartDirection() {
        return startDirection;
    }

    public int getWaitingTime() {
        return waitingTime;
    }

    public int getPriority() {
        return priority;
    }
}
