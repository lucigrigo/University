package com.luciangrigore;

//  EXERCITIUL 1
public class Complex {
    private int real, imaginary;

    public Complex(int real, int imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public Complex(){
        this(0, 0);
    }

    public Complex(Complex complex){
        this.real = complex.real;
        this.imaginary = complex.imaginary;
    }

    public int getReal() {
        return real;
    }

    public void setReal(int real) {
        this.real = real;
    }

    public int getImaginary() {
        return imaginary;
    }

    public void setImaginary(int imaginary) {
        this.imaginary = imaginary;
    }

    public void addWithComplex(Complex b){
        this.real = this.real + b.real;
        this.imaginary = this.imaginary + b.imaginary;
    }

    public void showNumber(){
        System.out.println("Numarul este = " + this.real + " + " +
                            this.imaginary + "i.");
    }
}
