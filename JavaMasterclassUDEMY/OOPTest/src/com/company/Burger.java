package com.company;

public class Burger {
    private String name;
    private boolean lettuce, tomato, carrot, onions;
    private String breadRollType, meatType;
    private int pricing;

    public Burger(String name, boolean lettuce, boolean tomato,
                  boolean carrot, boolean onions, String breadRollType,
                  String meatType, int pricing) {
        this.name = name;
        this.lettuce = lettuce;
        this.tomato = tomato;
        this.carrot = carrot;
        this.onions = onions;
        this.breadRollType = breadRollType;
        this.meatType = meatType;
        this.pricing = pricing;
    }

    public int getPricing() {
        System.out.println("Base price :" + this.pricing);
        if (lettuce) {
            System.out.printf("Added lettuce (+2$)");
            this.pricing += 1;
        }
        if (tomato) {
            System.out.printf("Added tomato (+1$)");
            this.pricing += 2;
        }
        if (carrot) {
            System.out.printf("Added carrots (+3$)");
            this.pricing += 3;
        }
        if (onions) {
            System.out.printf("Added onions (+1$)");
            this.pricing += 1;
        }
        System.out.println("Total :");
        return pricing;
    }
}
