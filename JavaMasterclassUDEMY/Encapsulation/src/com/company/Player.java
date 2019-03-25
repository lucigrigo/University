package com.company;

public class Player {
    public String fullName,weapon;
    public int health;

    public void loseHealth(int damage){
        this.health = this.health - damage;
        if(this.health<=0){
            System.out.println("You are dead");
            //Reduce number of lives remaining for the player
        }
    }

    public int healthRemaining(){
        return this.health;
    }
}
