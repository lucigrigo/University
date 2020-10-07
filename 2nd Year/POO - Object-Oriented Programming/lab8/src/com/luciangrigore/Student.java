package com.luciangrigore;

import java.util.Collections;
import java.util.Objects;

public class Student implements Comparable<Student> {
    private long id;
    private String name;
    private String surname;
    private double averageGrade;

    public Student(long id, String name, String surname, double averageGrade) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.averageGrade = averageGrade;
    }

    public long getId() {
        return this.id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return this.surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public double getAverageGrade() {
        return this.averageGrade;
    }

    public void setAverageGrade(double averageGrade) {
        this.averageGrade = averageGrade;
    }

    @Override
    public int compareTo(Student o) {
        if (o.getAverageGrade() > this.getAverageGrade()) {
            return 1;
        } else if (o.getAverageGrade() < this.getAverageGrade()) {
            return -1;
        } else {
            if (o.getSurname().compareTo(this.getSurname()) == 1) {
                return 1;
            } else if (o.getSurname().compareTo(this.getSurname()) == -1) {
                return -1;
            } else {
                if (o.getName().compareTo(this.name) == 1) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }

    @Override
    public String toString() {
        return this.surname + " " + this.name + " - " + this.id
                + " are media " + this.averageGrade;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return id == student.id &&
                Double.compare(student.averageGrade, averageGrade) == 0 &&
                Objects.equals(name, student.name) &&
                Objects.equals(surname, student.surname);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name, surname, averageGrade);
    }
}