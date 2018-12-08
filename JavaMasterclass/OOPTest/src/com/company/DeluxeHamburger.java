package com.company;


public class DeluxeHamburger extends Burger {
    private boolean chips, drink;

    public DeluxeHamburger(String breadRollType, String meatType) {
        super("Deluxe Hamburger", false, false, false, false,
                breadRollType, meatType, 15);
        this.chips = true;
        this.drink = true;

        System.out.println("Drink and chips added for 6$");
    }

    @Override
    public int getPricing() {
        System.out.println("The price of your Deluxe Hamburger (with chips and drink) is ");
        int price = super.getPricing();
        price += 6;     //  the chips and the drink of choice
        return price;
    }
}
