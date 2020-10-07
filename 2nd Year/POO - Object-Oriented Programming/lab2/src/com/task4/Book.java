package com.task4;

// EXERCITIUL 4
public class Book {
    private String title;
    private String author;
    private int year;

    public Book(String title, String author, int year) {
        this.title = title;
        this.author = author;
        this.year = year;
    }

    @Override
    public String toString() {
        return "Cartea este \"" + this.title + "\", scrisa de " +
                this.author + ", in anul " + this.year + ".";
    }
}