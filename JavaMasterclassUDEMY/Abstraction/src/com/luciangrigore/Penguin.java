package com.luciangrigore;

public class Penguin extends Bird {

    public Penguin(String name) {
        super(name);
    }

    @Override
    public void fly() {
        super.fly();
        System.out.println("I can't fly. I can swim tho'!");
    }
}
