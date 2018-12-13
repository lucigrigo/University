package com.example.game;

import java.util.ArrayList;
import java.util.List;

public class Monster implements ISaveable {

    private String name;
    private double health;
    private double strength;

    public Monster(String name, double health, double strength) {
        this.name = name;
        this.health = health;
        this.strength = strength;
    }

    public String getName() {
        return name;
    }

    public double getHealth() {
        return health;
    }

    public double getStrength() {
        return strength;
    }

    @Override
    public String toString() {
        return "Monster{" +
                "name='" + name + '\'' +
                ", health=" + health +
                ", strength=" + strength +
                '}';
    }

    @Override
    public List<String> write() {

        ArrayList<String> values = new ArrayList<String>();

        values.add(0, this.name);
        values.add(1, "" + this.health);
        values.add(2, "" + this.strength);

        return values;
    }

    @Override
    public void read(List<String> values) {

        if (values != null && values.size() > 0) {
            this.name = values.get(0);
            this.health = Double.parseDouble(values.get(1));
            this.strength = Double.parseDouble(values.get(2));
        }
    }
}
