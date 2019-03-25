package com.company;

import java.util.ArrayList;

class IntClass {
    private int myValue;

    public IntClass(int myValue) {
        this.myValue = myValue;
    }

    public int getMyValue() {
        return myValue;
    }

    public void setMyValue(int myValue) {
        this.myValue = myValue;
    }
}

public class Main {

    public static void main(String[] args) {

//        ArrayList<int> intArrayList = new ArrayList<int>();
        ArrayList<IntClass> intClassArrayList = new ArrayList<IntClass>();

        intClassArrayList.add(new IntClass(225));
        Integer integer = new Integer(225);
        Double doublee = new Double(213.22);

        ArrayList<Integer> integerArrayList = new ArrayList<Integer>();

        for (int i = 0; i < 10; i++) {
            //  AUTOBOXING = going from a primitive type to a wrapped class in Java
            integerArrayList.add(Integer.valueOf(i));
        }

        for (int i = 0; i < 10; i++) {
            //  UNBOXING = going from a class in Java back to a primitive type
            System.out.println(i + " --> " + integerArrayList.get(i).intValue());
        }

        Integer myIntValue = 56;   //  Integer myIntValue = Integer.valueOf(56);
        int myInt = myIntValue;     //  int myInt = myIntValue.intValue();


        ArrayList<Double> myDoubleValues = new ArrayList<Double>();

        for (double dbl = 0.0; dbl < 10.0; dbl += 0.5) {
            myDoubleValues.add(dbl);    //  AUTOBOXING
        }

        for (int i = 0; i < myDoubleValues.size(); i++) {
            System.out.println(myDoubleValues.get(i));      //  UNBOXING
        }
    }
}
