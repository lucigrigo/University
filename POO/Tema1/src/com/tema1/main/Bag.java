package com.tema1.main;

import com.tema1.goods.Goods;

import java.util.ArrayList;
import java.util.List;

/**
 * Clasa care reprezinta sacul unui jucator la un moment de timp.
 */
public class Bag {
    private int bribe;
    private List<Goods> assets;
    private int dominantAsset;

    public Bag() {
        this.assets = new ArrayList<>();
        dominantAsset = -1;
    }

    /**
     * @param bribe mita sacului
     */
    public void setBribe(final int bribe) {
        this.bribe = bribe;
    }

    /**
     * @param dominantAsset bunul declarat corespunzator sacului
     */
    public void setDominantAsset(final int dominantAsset) {
        this.dominantAsset = dominantAsset;
    }

    /**
     * @return lista de bunuri din sac
     */
    public List<Goods> getAssets() {
        return assets;
    }

    /**
     * @return mita sacului
     */
    public int getBribe() {
        return bribe;
    }

    /**
     * @return bunul declarat (dominant) al sacului
     */
    public int getDominantAsset() {
        return dominantAsset;
    }
}
