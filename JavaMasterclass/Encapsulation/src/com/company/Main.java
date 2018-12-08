package com.company;

public class Main {

    public static void main(String[] args) {
//        Player player = new Player();
//        player.fullName = "Tim";
////        player.health = 100;
//        player.weapon = "SWORDDDD";
//
//        int damage = 10;
//        player.loseHealth(damage);
//        System.out.println("Remaining health is " + player.healthRemaining());
//
//        damage +=90;
//        player.health = 500;
//        player.loseHealth(damage);
//        System.out.println("Health is now "+player.healthRemaining());

        EnhancedPlayer player = new EnhancedPlayer("Lucyk", "FMS+9", 500);
        System.out.println("Initial health is " + player.getHealth());
    }
}
