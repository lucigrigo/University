package com.company;

import com.company.gril.Foo;
import com.company.gril.SampleClass;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        Foo f = null;
        f.doStuff();
        Foo.doStuff();

        SampleClass.Ext newExt = new SampleClass.Ext();

//        SampleClass sampleClass = new SampleClass();
//        SampleClass.Ext newExt2 = sampleClass.new Ext();

        String a = "hello";
        String b = "world";
        String c = b;
        b = a + b;
        String d = new String("hello");
        System.out.println(c + " " + (d == a));
    }
}
