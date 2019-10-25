package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.main.Bag;

import java.util.List;

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

    String getType();

    // TODO inspectarea sacului de catre serif
    void inspection(List<Player> players, List<Integer> freeGoods);

    void handRefill(List<Integer> freeGoods);
}

