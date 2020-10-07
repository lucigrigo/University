package com.luciangrigore;

public class Lindt extends CandyBox {
    private float length, width, height;

    public Lindt(String flavor, String origin) {
        super(flavor, origin);
    }

    public Lindt(String flavor, String origin, float length, float width, float height) {
        super(flavor, origin);
        this.length = length;
        this.width = width;
        this.height = height;
    }

    @Override
    public float getVolume() {
        return length * width * height;
    }

    @Override
    public String toString() {
        return "The " + super.origin + " " + super.flavor + " has volume " +
                this.getVolume();
    }

    public void printDim() {
        System.out.println("length = " + length + "; width = " + width + "; height = " +
                height);
    }

    public void printLindtDim() {
        System.out.println("length = " + length + "; width = " + width + "; height = " +
                height);
    }
}
