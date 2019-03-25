package com.company;

public class Main {

    public static void main(String[] args) {

        int newScore = calculateScore("Tim",500);
        System.out.println("New score is "+newScore);
        calculateScore(75);
        calculateScore();


        System.out.println(calcFeetAndInchesToCentimetres(13,1));
        System.out.println(calcFeetAndInchesToCentimetres(157));


    }

    public static int calculateScore(String playerName,
                                     int score){
        System.out.println("Player " + playerName
                + " score " + score + " points!");
        return score * 1000;
    }

    public static int calculateScore(int score){
        System.out.println("Unnamed player scored " + score + " points!");
        return score * 1000;
    }

    public static int calculateScore(){
        System.out.println("No player name, no score!");
        return 0;
    }


    //  CHALLENGE

    public static double calcFeetAndInchesToCentimetres(double feet,
                                                        double inches){
        if(feet < 0 || inches > 12 || inches < 0){
            System.out.println("Invalid parameters!");
            return -1;
        } else {
            double cm;
            inches = inches + feet * 12;
            cm = inches * 2.54;
            return cm;
        }
    }

    public static double calcFeetAndInchesToCentimetres(double inches) {
        if (inches >= 0) {
            double feet = inches / 12;
            inches = inches - 12 * feet;
            return calcFeetAndInchesToCentimetres(feet, inches);
        } else {
            System.out.println("Invalid parameters!");
            return -1;
        }
    }
}
