package com.apd.tema2.entities;

/**
 * Utilizata pentru a uniformiza tipul de date ce ajuta la definirea unei
 * intersectii / a unui task. Implementarile acesteia vor contine variabile
 * specifice task-ului, respectiv mecanisme de sincronizare.
 */
public interface Intersection {
    /**
     * Functia principala de directionare a unei masini intr-o singura
     * intersectie la un moment de timp.
     *
     * @param car thread-ul curent
     */
    void handleCar(Car car);

    /**
     * Setam primul parametru de pe ultima linie, daca aceasta exista pentru
     * cerinta curenta.
     *
     * @param arg primul argument al cerintei
     */
    void setFirstArg(int arg);

    /**
     * La fel ca functia _setFirstArg_ pentru al doilea argument.
     *
     * @param arg al doilea argument al cerintei
     */
    void setSecondArg(int arg);

    /**
     * La fel ca functia _setFirstArg_ pentru al treilea argument.
     *
     * @param arg al treilea argument al cerintei
     */
    void setThirdArg(int arg);
}
