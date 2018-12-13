//  is => inheritance
//  can => interface

package com.luciangrigore;

public class Main {

    public static void main(String[] args) {

        Dog dog = new Dog("Golden Retriever");
        dog.breathe();
        dog.eat();

        Parrot parrot = new Parrot("Australian ringneck");
        parrot.breathe();
        parrot.eat();
        parrot.fly();

        Penguin penguin = new Penguin("Emperor");
        penguin.fly();
    }
}
