package com.company;

public class Main {

    public static void main(String[] args) {

        int switchValue = 4;

        switch (switchValue){
            case 1:
                System.out.println("Value was 1");
                break;

            case 2: case 3: case 4:
                System.out.println("Value was 2 , 3 or 4");
                break;

            default:
                System.out.println("Neither of the above");
                break;
        }



        //      CHALLENGE

        char test = 'C';

        switch(test){
            case 'A': case 'B': case 'C': case 'D': case 'E':
                System.out.println("It was one of A,B,C,D or E!");
                break;

                default:
                    System.out.println("It was not one of A, B, C, D or E!");
                    break;
        }



        //      Since JDK 8 , switch works with Strings as well !

        String month = "JANUARY";
        switch (month.toLowerCase()){
            case "june":
                System.out.println("June is hot!");
                break;

            case "january":
                System.out.println("January is cold!");
                break;

                default:
                    System.out.println("Idk what month currently is !");
                    break;
        }
    }
}
