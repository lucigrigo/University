package com.luciangrigore;

public class Area {
    private CandyBag desaga;
    private int number;
    private String street;

    public Area() {
        ;
    }

    public Area(CandyBag desaga, int number, String street) {
        this.desaga = desaga;
        this.number = number;
        this.street = street;
    }

    public void addCandy(CandyBox cb){
        this.desaga.addCandy(cb);
    }

    public void getBirthdayCard() {
        System.out.println("\n\n\t\tAddress: " + this.street + ", number " + this.number +
                "\n\t\tLa Multi Ani!\n");
        for (CandyBox candyBox : desaga.getDulcegarii()) {
            System.out.println(candyBox.toString());
            candyBox.printDim();
        }
        System.out.println("\n\n");
    }
}
