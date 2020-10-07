package com.luciangrigore;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        MyImmutableArray myImmutableArray = new MyImmutableArray(Arrays.asList(1, 2, 3));
        // urmatoarea instr. nu functioneaza in acest context
//        myImmutableArray.getArray().add(123);
        System.out.println(myImmutableArray.getArray().toString());
        PasswordMaker pw1 = PasswordMaker.getInstance();
        PasswordMaker pw2 = PasswordMaker.getInstance();
        PasswordMaker pw3 = PasswordMaker.getInstance();
        PasswordMaker pw4 = PasswordMaker.getInstance();
        System.out.println(pw4.getPassword());
        System.out.println(pw2.getCounts());
    }
}
