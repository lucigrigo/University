package com.company;

public class House {
    private String livingRoom,bedRoom,kitchen;
    private Office theOffice;

    public House(String livingRoom, String bedRoom, String kitchen, Office theOffice) {
        this.livingRoom = livingRoom;
        this.bedRoom = bedRoom;
        this.kitchen = kitchen;
        this.theOffice = theOffice;
    }

    public String getLivingRoom() {
        return livingRoom;
    }

    public String getBedRoom() {
        return bedRoom;
    }

    public String getKitchen() {
        return kitchen;
    }

    public Office getTheOffice() {
        return theOffice;
    }
}
