package com.company;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

public class Main {

    public static Scanner scanner = new Scanner(System.in);
    private static ArrayList<Album> albums = new ArrayList<Album>();

    public static void main(String[] args) {
        /*
        Album queen = new Album("Queen Album");

        queen.addSong("Bohemiam rhapsody",6.53);
        queen.addSong("Another one bites the dust",4.23);
        queen.addSong("We will rock you",4.08);

        queen.printSongs();

        queen.addSong("Don't stop me now",3.45);

        queen.printSongs();

        queen.addSong("Bohemiam rhapsody",6.53);

        queen.printSongs();
        */




        /*
        printMenu();
        boolean quit = false;
        while (!quit) {
            int option = scanner.nextInt();
            scanner.nextLine();
            switch (option) {
                case 0:
                    printMenu();
                    break;
                case 1:
                    addSong();
                    break;
                case 2:
                    removeSong();
                    break;
                case 3:
                    printSongs();
                    break;
                case 4:
                    quit = true;
                    break;
            }
        }
        */

        /*
        LinkedList<Song> playlist = new LinkedList<Song>();
        ListIterator<Song> listIterator = playlist.listIterator();


        playlist.add(new Song(4.54, "Bohhh"));
        playlist.add(new Song(6.12, "Prok"));
        playlist.add(new Song(5.03, "Mokinas"));
        playlist.add(new Song(9.23, "Remix"));

        boolean quit = false;
        printMenu2();
        while (!quit) {
            boolean next = true;
            int option = scanner.nextInt();
            scanner.nextLine();
            switch (option) {
                case 0:
                    quit = true;
                    break;
                case 1:
                    printMenu2();
                    break;
                case 2:
                    if (listIterator.hasNext()) {
                        System.out.println("Now playing " + listIterator.next().getTitle());
//                        listIterator.nextIndex();
                    } else {
//                        next = false;
                        System.out.println("Reached the end of the playlist!");

                    }
                    break;
                case 3:
                    if (listIterator.hasPrevious()) {
                        System.out.println("Now playing " + listIterator.previous().getTitle());
//                        listIterator.previousIndex();
                    } else {
//                        next = true;
                        System.out.println("Reached the beginning of the playlist!");
                    }
                    break;
            }
        }
        */


        Album queen = new Album("Queen Album");
        queen.addSong("Bohemiam rhapsody", 6.53);
        queen.addSong("Another one bites the dust", 4.23);
        queen.addSong("We will rock you", 4.08);

        albums.add(queen);


        Album beatles = new Album("Beatles Album");
        beatles.addSong("Yellow Submarine", 5.23);
        beatles.addSong("My love for you", 4.50);
        beatles.addSong("Third Song", 5.55);

        albums.add(beatles);


        LinkedList<Song> playlist = new LinkedList<Song>();
        albums.get(0).addToPlaylist("We will rock you", playlist);
        albums.get(0).addToPlaylist("Bohemiam rhapsody", playlist);
        albums.get(1).addToPlaylist("My love for you", playlist);
        albums.get(1).addToPlaylist("Second song", playlist);

        play(playlist);

    }


    public static void play(LinkedList<Song> playlist) {
        boolean quit = false;
        boolean forward = true;
        printMenu2();
        ListIterator<Song> listIterator = playlist.listIterator();
        if (playlist.size() == 0) {
            System.out.println("No songs in the playlist!");
        } else {
            System.out.println("Now playing " + listIterator.next().getTitle());
        }

        while (!quit) {
            int option = scanner.nextInt();
            scanner.nextLine();
            switch (option) {
                case 0:
                    quit = true;
                    break;
                case 1:
                    printMenu2();
                    break;
                case 2:
                    if (!forward) {
                        if (listIterator.hasNext()) {
                            listIterator.next();
                        }
                        forward = true;
                    }
                    if (listIterator.hasNext()) {
                        System.out.println("Now playing " +
                                listIterator.next().getTitle());
                    } else {
                        System.out.println("We have reached the end of the playlist!");
                        forward = false;
                    }
                    break;
                case 3:
                    if (forward) {
                        if (listIterator.hasPrevious()) {
                            listIterator.previous();
                        }
                        forward = false;
                    }
                    if (listIterator.hasPrevious()) {
                        System.out.println("Now playing " +
                                listIterator.previous().getTitle());
                    } else {
                        System.out.println("We have reached the end of the playlist!");
                        forward = true;
                    }
                    break;
                    /* case 4 or 5 :
                    print the songs in the playlist
                    remove a song from the playlist
                    HINT: listIterator.remove()
                     */

            }
        }
    }

    public static void printMenu2() {
        System.out.println("Menu");
        System.out.println("0 - quit");
        System.out.println("1 - print this menu");
        System.out.println("2 - next song");
        System.out.println("3 - previous song");
    }


    public static void printMenu() {
        System.out.println("Here are the options ");
        System.out.println("0 - print this menu");
        System.out.println("1 - add a song");
        System.out.println("2 - remove a song");
        System.out.println("3 - print the songs");
        System.out.println("4 - quit menu");
    }

    public static void addSong() {
        System.out.println("Enter the name and the duration of the song");
        String name = scanner.nextLine();
        double duration = scanner.nextDouble();
        scanner.nextLine();
//        beatles.addSong(name, duration);
    }

    public static void removeSong() {
        System.out.println("Enter the name of the song" +
                " you want to be removed");
        String name = scanner.nextLine();
//        beatles.removeSong(name);
    }

    public static void printSongs() {
//        beatles.printSongs();
    }
}
