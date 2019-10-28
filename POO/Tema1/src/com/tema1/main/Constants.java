package com.tema1.main;

public final class Constants {
    public static Constants instance = null;

    public static Constants getInstance() {
        if (instance == null) {
            instance = new Constants();
        }
        return instance;
    }

    public final int nrLegalItems = 10;
    public final int nrIllegalItems = 5;

    public int getNrLegalItems() {
        return nrLegalItems;
    }

    public int getNrIllegalItems() {
        return nrIllegalItems;
    }
}
