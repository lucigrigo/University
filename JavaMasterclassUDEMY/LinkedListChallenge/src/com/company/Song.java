package com.company;

public class Song {
    private double duration;
    private String title;

    public Song(double duration, String title) {
        this.duration = duration;
        this.title = title;
    }

    public String getTitle() {
        return this.title;
    }
}
