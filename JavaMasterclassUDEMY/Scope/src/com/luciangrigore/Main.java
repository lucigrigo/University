package com.luciangrigore;

public class Main {

    public static void main(String[] args) {

        String varFour = "this is private to main()";

        ScopeCheck scopeInstance = new ScopeCheck();
        scopeInstance.useInner();

//        System.out.println("scopeInstance varOne is " +
//                scopeInstance.getVarOne());
//        System.out.println(varFour);
//        scopeInstance.timesTwo();
//
//        System.out.println("*******************************");
//
//        ScopeCheck.innerClass innerClass = scopeInstance.new innerClass();
//        innerClass.timesTwo();
//
//        System.out.println("*******************************");
    }
}
