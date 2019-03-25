package com.luciangrigore;

import java.util.*;

public class Theatre {

    private final String thatreName;
    private List<Seat> seats = new ArrayList<>();

    static final Comparator<Seat> PRICE_ORDER;

    static {
        PRICE_ORDER = new Comparator<Seat>() {
            @Override
            public int compare(Seat seat1, Seat seat2) {
                if (seat1.getPrice() < seat2.getPrice()) {
                    return -1;
                } else if (seat1.getPrice() > seat2.getPrice()) {
                    return 1;
                } else {
                    return 0;
                }
            }
        };
    }

    public Theatre(String theatreName, int numRows, int seatsPerRow) {
        this.thatreName = theatreName;

        int lastRow = 'A' + (numRows - 1);
        for (char row = 'A'; row <= lastRow; row++) {
            for (int seatNum = 1; seatNum <= seatsPerRow; seatNum++) {
                double price = 12.00;
                if ((row < 'D') && (seatNum >= 4) && (seatNum <= 9)) {
                    price = 14.00;
                } else if ((row > 'D') || (seatNum < 4) || (seatNum > 9)) {
                    price = 7.00;
                }
                Seat seat = new Seat(row + String.format("%02d", seatNum), price);
                seats.add(seat);
            }
        }
    }

    public String getTheatreName() {
        return thatreName;
    }

    public boolean reserveSeat(String seatNumber) {
        //  THE ONLY ONE THAT WORKS IN MY PROJECT
        Seat requestedSeat = new Seat(seatNumber, 0);
        //  Binary search is very very fast compared to classic search
        int foundSeat = Collections.binarySearch(seats, requestedSeat, null);

        if (foundSeat >= 0) {
            return seats.get(foundSeat).reserved();
        } else {
            System.out.println("There is no seat " + seatNumber);
            return false;
        }


        //  DOES NOT WORK ( in my project )
//        for (Seat seat : seats) {
//            System.out.print(".");
//            if (seat.getSeatNumber().equals(seatNumber)) ;
//            {
//                requestedSeat = seat;
//                break;
//            }
//        }
//
//        if (requestedSeat == null) {
//            System.out.println("No seat free !");
//            return false;
//        }
//        return requestedSeat.reserved();


        //  The actual code behind binary search ( in our case ) - DOES NOT WORK ( in my project )
//        int low = 0;
//        int high = seats.size() - 1;
//
//        while (low <= high) {
//            System.out.print(".");
//            int mid = (low + high) / 2;
//            Seat midValue = seats.get(mid);
//            int cmp = midValue.getSeatNumber().compareTo(seatNumber);
//
//            if (cmp < 0) {
//                low = mid + 1;
//            } else if (cmp > 0) {
//                high = mid - 1;
//            } else {
//                return seats.get(mid).reserved;
//            }
//        }
//
//        System.out.println("There is no such seat as " + seatNumber);
//        return false;
    }

    public Collection<Seat> getSeats() {
        return seats;
    }

    public class Seat implements Comparable<Seat> {

        private final String seatNumber;
        private double price;
        private boolean reserved = false;

        public Seat(String seatNumber, double price) {
            this.seatNumber = seatNumber;
            this.price = price;
        }

        @Override
        public int compareTo(Seat seat) {
            return this.seatNumber.compareToIgnoreCase(seat.getSeatNumber());
        }

        public String getSeatNumber() {
            return this.seatNumber;
        }

        public boolean reserved() {
            if (!this.reserved) {
                this.reserved = true;
                System.out.println("Seat " + this.seatNumber + " is reserved.");
                return true;
            } else {
                return false;
            }
        }

        public boolean cancel() {
            if (this.reserved) {
                this.reserved = false;
                System.out.println("Seat " + seatNumber + " is free.");
                return true;
            } else {
                return false;
            }
        }

        public double getPrice() {
            return price;
        }
    }
}
