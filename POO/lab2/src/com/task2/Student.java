package com.task2;

// EXERCITIUL 2
public class Student {
    private int id;
    private String name, surname;

    public Student(int id, String name, String surname) {
        this.id = id;
        this.name = name;
        this.surname = surname;
    }

    // copy constructor - se copiaza un obiect
    public Student(Student st) {
        this.id = st.id;
        this.name = st.name;
        this.surname = st.surname;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void show() {
        System.out.println(String.format("Name: %s\nSurname: %s\nStudent ID: %d\n", name, surname, id));
    }

}
