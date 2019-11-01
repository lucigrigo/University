package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.main.Bag;

import java.util.List;

/**
 * Interfata de jucator in care se incadreaza toate tipurile de jucatori.
 */
public interface Player {

    List<Goods> getOwnCards();

    List<Goods> getEndGameGoods();

    Bag getBag();

    void setFinalScore(int finalScore);

    int getFinalScore();

    int getCoins();

    void setCoins(int nr);

    void bagCreation();

    int getInitialOrderNr();

    // intoarce tipul jucatorului
    String getType();

    // inspectarea sacului
    void inspection(List<Player> players, List<Integer> freeGoods);

    // re/completarea mainii
    void handRefill(List<Integer> freeGoods);
}

