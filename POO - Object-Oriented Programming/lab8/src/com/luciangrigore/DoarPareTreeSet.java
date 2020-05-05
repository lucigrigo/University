package com.luciangrigore;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.TreeSet;

public class DoarPareTreeSet extends TreeSet<Integer> {

    @Override
    public boolean add(Integer integer) {
        if (integer % 2 == 0) {
            return super.add(integer);
        }
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends Integer> c) {
        List<Integer> newCollection = new ArrayList<>();
        for (Integer element : c) {
            if (element % 2 == 0) {
                newCollection.add(element);
            }
        }
        return super.addAll(newCollection);
    }
}
