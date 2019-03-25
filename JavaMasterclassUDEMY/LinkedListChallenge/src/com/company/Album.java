package com.company;

import java.util.ArrayList;
import java.util.LinkedList;

public class Album {

    private ArrayList<Song> songs = new ArrayList<Song>();
    private String title;

    public Album(String title) {
        this.title = title;
    }

    public Album(ArrayList<Song> songs, String title) {
        this.songs = songs;
        this.title = title;
    }

    public boolean addSong(String name, double duration) {
        for (int i = 0; i < songs.size(); i++) {
            Song currentSong = songs.get(i);
            if (currentSong.getTitle().equals(name)) {
                System.out.println("Song already in the album!");
                return false;
            }
        }
        System.out.println("Song added to the playlist!");
        songs.add(new Song(duration, name));
        return true;
    }

    private Song findSong(String title) {
        for (Song checkedSong : this.songs) {
            if (checkedSong.getTitle().equals(title)) {
                return checkedSong;
            }
        }
        return null;
    }

    public boolean addToPlaylist(String title, LinkedList<Song> playlist) {
        Song checkedSong = findSong(title);
        if (checkedSong != null) {
            playlist.add(checkedSong);
            return true;
        }
        System.out.println("The song " + " is not in the album!");
        return false;
    }

    public boolean removeSong(String name) {
        for (int i = 0; i < songs.size(); i++) {
            Song currentSong = songs.get(i);
            if (currentSong.getTitle().equals(name)) {
                System.out.println("Song removed succesfully!");
                songs.remove(i);
                return true;
            }
        }
        System.out.println("No such song in the album!");
        return true;
    }

    public void printSongs() {
        System.out.println("The songs in album " + this.title + " are:");
        for (int i = 0; i < songs.size(); i++) {
            System.out.println("#" + (i + 1) + " : " + songs.get(i).getTitle());
        }
    }
}
