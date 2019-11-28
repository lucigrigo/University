package com.luciangrigore;

import java.util.*;

class MyHashMap<Integer, T> {

    private HashSet<Entry<Integer, T>> collection = new HashSet<>();
    private int size = 1;

    public void put(T elem) {
        int key = elem.hashCode() % size;
        size++;
        this.collection.add(new Entry<>(key, elem));
    }

    public Iterator<Entry<Integer, T>> get() {
        return this.collection.iterator();
    }

}
