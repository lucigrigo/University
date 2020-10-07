package com.luciangrigore;

public class Entry<Integer, T> {
    private int key;
    private T value;

    Entry(int key, T value) {
        this.key = key;
        this.value = value;
    }

    public int getKey() {
        return key;
    }

    public void setKey(Integer key) {
        this.key = (int) key;
    }

    public T getValue() {
        return value;
    }

    public void setValue(T value) {
        this.value = value;
    }
}
