package com.company;

import java.io.BufferedReader;

public class HealthyBuger extends Burger {

    public boolean salad, crisps;

    public HealthyBuger(boolean lettuce, boolean tomato, boolean carrot, boolean onions,
                        String meatType, boolean salad, boolean crisps) {
        super("Healthy Burger", lettuce, tomato, carrot, onions,
                "rye bread", meatType, 12);
        this.salad = salad;
        this.crisps = crisps;

        if(salad){
            System.out.println("Salad added for 3$");
        }
        if(crisps){
            System.out.println("Crisps added for 2$");
        }
    }

    @Override
    public int getPricing() {
        System.out.println("The final price of your Healthy Burger is ");
        int price = super.getPricing();
        price +=5;      //  the salad and the crisps
        return price;
    }
}
