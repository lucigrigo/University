package com.luciangrigore;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class MyImmutableArray {
    private final ArrayList<Integer> immutableArray = new ArrayList<>();

    public MyImmutableArray(List<Integer> arrayIn) {
        immutableArray.addAll(arrayIn);
    }

    public List<Integer> getArray() {
        return Collections.unmodifiableList(immutableArray);
    }
}
