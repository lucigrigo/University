package com.luciangrigore;

import java.util.ArrayList;

// EXERCITIUL 3
public class Polygon {
    private int nrPoints;
    private ArrayList<Point> points;

    public Polygon(int nrPoints) {
        this.nrPoints = nrPoints;
        this.points = new ArrayList<>(nrPoints);
    }

    public Polygon(int[] coords) {
        this.nrPoints = coords.length / 2;
        this.points = new ArrayList<>(nrPoints);
        for (int i = 0; i < 2 * nrPoints; i += 2) {
            points.add(new Point(coords[i], coords[i + 1]));
        }
    }

    public void showPoly() {
        System.out.println("Poligonul este format din punctele:");
        for (Point point : this.points) {
            point.showPoint();
        }
    }
}
