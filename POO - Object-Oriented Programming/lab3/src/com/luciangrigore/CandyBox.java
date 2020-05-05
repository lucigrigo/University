package com.luciangrigore;

import java.util.Objects;

public class CandyBox {
    protected String flavor, origin;

    public CandyBox() {
        this(null,null);
    }

    public CandyBox(String flavor, String origin) {
        this.flavor = flavor;
        this.origin = origin;
    }

    public float getVolume() {
        return 0f;
    }

    @Override
    public String toString() {
        return "CandyBox{" +
                "flavor='" + flavor + '\'' +
                ", origin='" + origin + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        CandyBox candyBox = (CandyBox) o;
        return Objects.equals(flavor, candyBox.flavor) &&
                Objects.equals(origin, candyBox.origin);
    }

//    public void printDim() {
//        if (this instanceof Lindt) ((Lindt) this).printLindtDim();
//        if (this instanceof Baravelli) ((Baravelli) this).printBaravelliDim();
//        if (this instanceof ChocAmor) ((ChocAmor) this).printChocAmorDim();
//    }

    public void printDim(){
        System.out.println("nu sunt dulciuri aici");
    }
}
