package com.luciangrigore;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.ListIterator;

public class Main {

    public static void main(String[] args) {
        //        theatre.getSeats();

//        if (theatre.reserveSeat("D12")) {
//            System.out.println("Please pay");
//        } else {
//            System.out.println("Sorry, seat is taken");
//        }
//
//        if (theatre.reserveSeat("D12")) {
//            System.out.println("Please pay");
//        } else {
//            System.out.println("Sorry, seat is taken");
//        }

        //  theatre.seats and seatCopy point to the same place in memory ( same seats - in our case )
        //  it is a shallow copy
//        List<Theatre.Seat> seatCopy = new ArrayList<>(theatre.seats);
//        printList(seatCopy);
//
//        //  Reverse sort
//        Collections.reverse(seatCopy);
//        System.out.println("Printing theatre.seats");
//        printList(theatre.seats);
//        System.out.println("Printing seatCopy");
//        printList(seatCopy);
//
//        //  Shuffle (random) sort
//        Collections.shuffle(seatCopy);
//        System.out.println("Printing theatre.seats");
//        printList(theatre.seats);
//        System.out.println("Printing seatCopy");
//        printList(seatCopy);
//
//        //  Max and min
//        Theatre.Seat minSeat = Collections.min(seatCopy);
//        Theatre.Seat maxSeat = Collections.max(seatCopy);
//
//        sortList(seatCopy);
//        System.out.println("Printing sorted seatCopy");
//        printList(seatCopy);
//    }
//
//
//    public static void sortList(List<? extends Theatre.Seat> list) {
//        //  Bubble sort
//        for (int i = 0; i < list.size() - 1; i++) {
//            for (int j = i + 1; j < list.size(); j++) {
//                if (list.get(i).compareTo(list.get(j)) > 0) {
//                    //  Swaps two elements between them
//                    Collections.swap(list, i, j);
//                }
//            }
//        }


        Theatre theatre = new Theatre("Cinema City", 8, 12);

        if (theatre.reserveSeat("D12")) {
            System.out.println("Please pay");
        } else {
            System.out.println("Sorry, seat is taken");
        }

        if (theatre.reserveSeat("D12")) {
            System.out.println("Please pay");
        } else {
            System.out.println("Sorry, seat is taken");
        }

//        List<Theatre.Seat> reverseSeats = new ArrayList<>(theatre.getSeats());
//        Collections.reverse(reverseSeats);
//        printList(reverseSeats);


        List<Theatre.Seat> priceSeats = new ArrayList<>(theatre.getSeats());
        priceSeats.add(theatre.new Seat("B00", 13.00));
        priceSeats.add(theatre.new Seat("A00", 13.00));
        //  Elements are not swapped if they do not need to be
        Collections.sort(priceSeats, Theatre.PRICE_ORDER);
        printList(priceSeats);

    }

    public static void printList(List<Theatre.Seat> list) {
        for (Theatre.Seat seat : list) {
            System.out.println(" " + seat.getSeatNumber() + " $" + seat.getPrice());
        }
        System.out.println();
        System.out.println("===================================================================");
        System.out.println();
    }
}
