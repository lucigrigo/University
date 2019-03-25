package com.company;

public class Main {

    private static final String INVALID_VALUE_MESSAGE = "Invalid value";

    public static void main(String[] args) {

        System.out.println(getDurationString(65,45));
        System.out.println(getDurationString(3945));
    }

    public static String getDurationString(int minutes,
                                           int seconds){

        if(minutes<0 || seconds<0 || seconds>59){
            return INVALID_VALUE_MESSAGE;
        } else {
            int hours = minutes / 60;
            minutes-=hours*60;
            return (hours+"h "+minutes+"m "+seconds+"s");
        }
    }

    public static String getDurationString(int seconds){

        if(seconds<0){
            return INVALID_VALUE_MESSAGE;
        } else  {
            int minutes = seconds / 60;
            seconds -= minutes*60;
            return getDurationString(minutes,seconds);
        }
    }
}
