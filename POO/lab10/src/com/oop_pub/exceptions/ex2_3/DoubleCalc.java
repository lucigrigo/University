package com.oop_pub.exceptions.ex2_3;

import java.util.Collection;

public class DoubleCalc implements Calculator {

    @Override
    public Double add(Double nr1, Double nr2) throws NullParameterException, OverflowException, UnderflowException {
        if (nr1 == null || nr2 == null)
            throw new NullParameterException("add method.");
        if (nr1 + nr2 > Double.POSITIVE_INFINITY)
            throw new OverflowException("add method.");
        if (nr1 + nr2 < Double.NEGATIVE_INFINITY)
            throw new UnderflowException("add method.");
        return nr1 + nr2;
    }

    @Override
    public Double divide(Double nr1, Double nr2) throws NullParameterException {
        if (nr1 == null || nr2 == null)
            throw new NullParameterException("divide method.");
        return nr1 / nr2;
    }

    @Override
    public Double average(Collection<Double> numbers) throws NullParameterException {
        double result = 0;
        for (double nr : numbers) {
            result = add(result, nr);
        }
        result = divide(result, (double) numbers.size());
        return result;
    }
}
