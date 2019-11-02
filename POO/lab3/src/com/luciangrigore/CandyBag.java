package com.luciangrigore;

import java.util.ArrayList;

public class CandyBag {
    private ArrayList<CandyBox> dulcegarii;

    public CandyBag(int dimMax) {
        this.dulcegarii = new ArrayList<>(dimMax);
    }

    public void addCandy(CandyBox cb){
        this.dulcegarii.add(cb);
    }

    public ArrayList<CandyBox> getDulcegarii() {
        return dulcegarii;
    }
}
