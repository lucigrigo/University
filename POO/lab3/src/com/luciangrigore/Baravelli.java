package com.luciangrigore;

public class Baravelli extends CandyBox {
    private float radius, height;

    public Baravelli(String flavor, String origin) {
        super(flavor, origin);
    }

    public Baravelli(String flavor, String origin, float radius, float height) {
        super(flavor, origin);
        this.radius = radius;
        this.height = height;
    }

    @Override
    public float getVolume() {
        return height * (float) Math.PI * (float) Math.pow(radius, 2);
    }

    public void printDim() {
        System.out.println("radius = " + radius + "; height = " + height);
    }

    public void printBaravelliDim() {
        System.out.println("radius = " + radius + "; height = " + height);
    }
}
