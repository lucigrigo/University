package com.company;

public class Contacts {
    private int number;
    private String name;

    public Contacts(int number, String name) {
        this.number = number;
        this.name = name;
    }

    public Contacts(int number) {
        this.number = number;
    }

    public Contacts(String name) {
        this.name = name;
    }

    public int getNumber() {
        return number;
    }

    public String getName() {
        return name;
    }
}
