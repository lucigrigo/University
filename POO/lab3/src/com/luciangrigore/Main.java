package com.luciangrigore;

public class Main {

    public static void main(String[] args) {
        Lindt l1 = new Lindt("cioco", "elvetia", 20, 10, 15);
        Lindt l2 = new Lindt("vanilie", "austria", 20, 10, 15);
        Lindt l3 = new Lindt("mere", "germania", 20, 10, 15);
        Lindt l4 = new Lindt("zmeura", "franta", 10, 5, 10);
        Lindt l5 = new Lindt("mure", "anglia", 10, 5, 10);
        Lindt l6 = new Lindt("banane", "spania", 10, 5, 10);
        Lindt l7 = new Lindt("cioco", "elvetia", 20, 10, 15);

        System.out.println(l1.equals(l2));
        System.out.println(l2.equals(l5));
        System.out.println(l1.equals(l7));

        l3.printLindtDim();
        l6.printLindtDim();

        Area area = new Area(new CandyBag(10), 15, "Unirii Bvd.");
        area.addCandy(l1);
        area.addCandy(l2);
        area.addCandy(l3);
        area.addCandy(l4);
        area.addCandy(l5);
        area.addCandy(l6);
        area.addCandy(l7);
        area.getBirthdayCard();
    }
}
