package com.tema1.main;

import com.tema1.goods.Goods;

import java.util.ArrayList;
import java.util.List;

public class Bag {
    private int bribe;
    private List<Goods> assets;
    private int dominantAsset;

    public Bag() {
        this.assets = new ArrayList<>();
        dominantAsset = -1;
    }

    public void setBribe(int bribe) {
        this.bribe = bribe;
    }

    public void setDominantAsset(int dominantAsset) {
        this.dominantAsset = dominantAsset;
    }

    public List<Goods> getAssets() {
        return assets;
    }

    public int getBribe() {
        return bribe;
    }

    public int getDominantAsset() {
        return dominantAsset;
    }
}
