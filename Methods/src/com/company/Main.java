package com.company;

public class Main {

    public static void main(String[] args) {

        System.out.println(calculateScore(true, 800, 5, 100));

        int score = 10000;
        int levelCompleted = 8;
        int bonus = 800;

        int highScore = calculateScore(true, score, levelCompleted, bonus);
        System.out.println(highScore);


        //  CHALLENGE

        displayHighScorePosition("Garcea", calculateHighScorePosition(1000));
        displayHighScorePosition("Mariusik", calculateHighScorePosition(900));
        displayHighScorePosition("Giorgi", calculateHighScorePosition(400));
        displayHighScorePosition("Marica", calculateHighScorePosition(50));

    }

    public static int calculateScore(boolean gameOver,
                                     int score,
                                     int levelCompleted,
                                     int bonus) {
        if (gameOver) {
            int finalScore = score + (levelCompleted * bonus);
            finalScore += 2000;
            return finalScore;
        }
        return -1;      //  conventionally used to indicate an error
    }

    public static void displayHighScorePosition(String name,
                                                int position) {
        System.out.println(name + " managed to get into position "
                + position + " on the high score table !");
    }

    public static int calculateHighScorePosition(int score) {
        /*if (score >= 1000) {
            return 1;
        }
        if (score >= 500) {
            return 2;
        }
        if (score >= 100) {
            return 3;
        }
        return 4;*/

        int position = 4;

        if(score >= 1000){
            position = 1;
        } else if(score >= 500){
            position = 2;
        } else if(score >= 100){
            position = 3;
        }

        return position;
    }
}
