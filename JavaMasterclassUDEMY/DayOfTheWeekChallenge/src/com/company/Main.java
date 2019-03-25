package com.company;

import java.util.Random;

public class Main {

    public static void main(String[] args) {
        printDayOfTheWeek(-2);
        printDayOfTheWeek(4);
        printDayOfTheWeek(2);
        printDayOfTheWeek(10000);
    }

    public static void printDayOfTheWeek(int day) {
        if (day < 0 || day > 6) {
            System.out.println("Invalid Value");
        } else {
            switch (day) {
                case 0:
                    System.out.println("Monday");
                    break;
                case 1:
                    System.out.printf("Tuesday");
                    break;
                case 2:
                    System.out.println("Wednsday");
                    break;
                case 3:
                    System.out.println("Thursday");
                    break;
                case 4:
                    System.out.println("TGIF");
                    break;
                case 5:
                    System.out.println("Saturday");
                    break;
                case 6:
                    System.out.println("Sunday");
                    break;
            }
        }
    }


    //      CODING EXERCISE

    public static boolean isLeapYear(int year) {
        if (year < 1 || year > 9999) {
            return false;
        } else {
            if ((year % 4) == 0 && (year % 100) != 0) {
                return true;
            } else if ((year % 400) == 0) {
                return true;
            } else {
                return false;
            }
        }
    }

    public static int getDaysInMonth(int month, int year) {

        if (month > 12 || month < 1 || year < 1 || year > 9999) {
            return -1;
        } else {
            boolean OK = isLeapYear(year);
            switch (month) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    return 31;
                case 4:
                case 6:
                case 9:
                case 11:
                    return 30;
                case 2:
                    if (OK) {
                        return 29;
                    } else {
                        return 28;
                    }
            }
        }
        return 0;
    }
}



