package com.luciangrigore;

public class ChocAmor extends CandyBox {
    private float length;

    public ChocAmor(String flavor, String origin) {
        super(flavor, origin);
    }

    public ChocAmor(String flavor, String origin, float length) {
        super(flavor, origin);
        this.length = length;
    }

    @Override
    public float getVolume() {
        return (float) Math.pow(length, 3);
    }

    public void printDim() {
        System.out.println("length = " + length);
    }

    public void printChocAmorDim() {
        System.out.println("length = " + length);
    }
}
