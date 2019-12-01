package com.oop_pub.exceptions.ex2_3;

import org.w3c.dom.ls.LSOutput;

import java.util.Collection;

public interface Calculator {
    class NullParameterException extends RuntimeException {
        NullParameterException(String message) {
            System.out.println("NullParameterException was thrown in " + message);
        }
    }

    class UnderflowException extends RuntimeException {
        UnderflowException(String message) {
            System.out.println("UnderflowException was thrown in " + message);
        }
    }

    class OverflowException extends RuntimeException {
        OverflowException(String message) {
            System.out.println("OverflowException was thrown in " + message);
        }
    }

    Double add(Double nr1, Double nr2) throws NullParameterException, OverflowException, UnderflowException;

    Double divide(Double nr1, Double nr2) throws NullParameterException;

    Double average(Collection<Double> numbers) throws NullParameterException;
}
