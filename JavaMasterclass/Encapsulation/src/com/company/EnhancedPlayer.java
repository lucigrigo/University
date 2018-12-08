package com.company;

public class EnhancedPlayer {

    private String name, weapong;
    private int hitpoints = 100;

    public EnhancedPlayer(String name, String weapong, int health) {
        this.name = name;
        if (health > 0 && health <= 100) {
            this.hitpoints = health;
        }
        this.weapong = weapong;
    }

    public void loseHealth(int damage){
        this.hitpoints = this.hitpoints - damage;
        if(this.hitpoints <0){
            System.out.println("you are dead");
            //  Reduce the number of lives etc
        }
    }

    public int getHealth() {
        return hitpoints;
    }
}
