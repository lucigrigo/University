package com.company;

public class Main {

    public static void main(String[] args) {

       /*
       //int are latimea de 32
        int myMinValue = -2_147_483_648;    //min int value
        int myMaxValue = 2_147_483_647;     //max int value
        int myNewIntValue = (myMinValue/2);
        System.out.println("myTotal = " + myNewIntValue);

        //byte are latimea de 8
        byte myByteValue = 127;         //max byte value
        byte myByteValueMin = -128;     //min byte value
        byte myNewByteValue = (byte)(myByteValueMin/2);
        System.out.println("myNewByteValue = " + myNewByteValue);

        //short are latimea de 16
        short myShortMax = 32767;   //max short value
        short myShortMin = -32768;  //min short value
        short myNewShortValue = (short)(myShortMax/2);
        System.out.println(myNewShortValue);

         //long are latimea de 64
         //valorile min/max sunt de +- 2ˆ63
        long myLongValue = 100L;
        */




       byte b = 57;
       short s = 25_000;
       int i = 1_000_000;
       long l = 50_000 + 10 * (b+s+i);
       System.out.println("longTotal = " + l);

    }
}
