package entities;

import java.util.Random;

public class Monster {
    private String name;
    private Treasure.DamageType weakness;
    private int posx, posy;
    private int hp;

    public Monster(String name, Treasure.DamageType weakness) {
        this.name = name;
        this.weakness = weakness;
        this.hp = 100;
    }

    /* Getters and setters */
    public int getPosy() {
        return posy;
    }

    public void setPosy(int posy) {
        this.posy = posy;
    }

    public int getPosx() {
        return posx;
    }

    public void setPosx(int posx) {
        this.posx = posx;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getHP() {
        return hp;
    }

    public void setHP(int hp) {
        this.hp = hp;
    }

    public Treasure.DamageType getWeakness() {
        return weakness;
    }

    public int getDmg() {
        return new Random().nextInt(26) + 25;
    }

    public String toString() {
        return this.getName() + "is vulnerable agains: " + this.getWeakness();
    }
}
