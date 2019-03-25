package com.company;

public class Main {

    public static void main(String[] args) {
        int result = 1 + 2;
        System.out.println("1 + 2 = " + result);

        int previousResult = result;
        result = result - 1;
        System.out.println(previousResult + " - 1 = " + result);

        previousResult = result;
        result = result * 10;
        System.out.println(previousResult + " * 10 = " + result);

        previousResult = result;
        result = result / 5;
        System.out.println(previousResult + " / 5 = " + result);

        previousResult = result;
        result = result % 3;
        System.out.println(previousResult + " % 3 = " + result);

        result++;
        result--;
        result += 3;
        result *= 10;
        result -= 10;
        result /= 10;


        boolean isAlien = false;
        if (isAlien) {
            System.out.println("RUN !! It is an alien !!");
        }
        if (!isAlien) {
            System.out.println("It is not an alien !");
        }


        int topScore = 80;
        if (topScore < 100)
            System.out.println("You got the high score !");
        int secondTopScore = 95;
        if ((topScore > secondTopScore) && (topScore < 100))
            System.out.println("Niceeeeeee !!");
        if ((topScore > 90) || (secondTopScore <= 90)) {
            System.out.println("One of these tests is true");
        }


        int newValue = 50;
        if (newValue == 50) {
            System.out.println("this is not an error");
        }

        boolean isCar = false;
        if (isCar) {
            System.out.println("this should not happen");
        }

        isCar=true;
        boolean wasCar = isCar ? true : false;
        if(wasCar)
            System.out.println("wasCar is true");

        double a=20d;
        double b=80d;
        if((((a+b)*25)%40)<=20)
        {
            System.out.println("Total was over the limit!");
        }
    }
}
