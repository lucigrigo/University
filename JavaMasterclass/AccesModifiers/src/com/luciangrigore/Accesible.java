package com.luciangrigore;

interface Accesible {
    int SOME_CONSTANT=100;
    public void methodA();
    void methodB();
    boolean methodC();
}

//  interface Accesible is package-private
//  SOME_CONSTANT is public
//  methodA is public
//  methodB and methodC are public as well
//  ALL INTERFACE METHODS ARE BY DEFAULT PUBLIC