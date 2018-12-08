package com.luciangrigore;

import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

public class Player implements ISaveable {

    private String name;
    private double health;
    private double strength;
    private String weapon;

    public Player(String name, double health, double strength) {
        this.name = name;
        this.health = health;
        this.strength = strength;
        this.weapon = "Sword";
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getHealth() {
        return health;
    }

    public void setHealth(double health) {
        this.health = health;
    }

    public double getStrength() {
        return strength;
    }

    public void setStrength(double strength) {
        this.strength = strength;
    }

    public String getWeapon() {
        return weapon;
    }

    public void setWeapon(String weapon) {
        this.weapon = weapon;
    }

    @Override
    public String toString() {
        return "Player " + this.name + "\nhitpoints = " + this.health +
                "\nstrength = " + this.strength + "\nweapon = " + this.weapon;
    }

    @Override
    public List<String> write() {

        List<String> values = new ArrayList<String>();

        values.add(0, this.name);
        values.add(1, "" + this.health);
        values.add(2, "" + this.strength);
        values.add(3, this.weapon);

        return values;
    }

    @Override
    public void read(List<String> values) {
        if (values != null && values.size() > 0) {
            this.name = values.get(0);
            this.health = Double.parseDouble(values.get(1));
            this.strength = Double.parseDouble(values.get(2));
            this.weapon = values.get(3);
        }
    }
}
