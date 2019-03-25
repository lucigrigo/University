package com.company;

public class Main {

    public static void main(String[] args) {
        DeluxeHamburger deluxe = new DeluxeHamburger("classic","chicken");
        System.out.println(deluxe.getPricing());
        System.out.println();

        HealthyBuger healthy = new HealthyBuger(false,true,false,true,
                "angus",true,true);
        System.out.println(healthy.getPricing());
        System.out.println();

        Burger basic = new Burger("Classic",false,true,false,false,
                "white soft","pork special",11);
        System.out.println(basic.getPricing());
    }
}
