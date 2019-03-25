package com.company;

public class Main {

    public static void main(String[] args) {
        Dimensions dimensions = new Dimensions(20,20,5);
        Case theCase = new Case("220b","DELL",
                "600W",dimensions);

        Monitor theMonitor = new Monitor("27inch BEAST","Acer",
                27,new Resolution(2540,1440));

        Motherboard theMotherboard = new Motherboard("280zzd","Gigabyte",
                8,4,"921.22d");

        PC thePC = new PC(theCase,theMonitor,theMotherboard);

//        thePC.getMonitor().drawPixelAt(1200,1400,"red");
//        thePC.getMotherboard().loadProgram("IntelliJ IDEA");
//        thePC.getTheCase().pressPowerButton();

        thePC.powerUP();

        //  Challenge

        House newHouse = new House("spacious","relaxing",
                "well-equiped",new Office("Lucian","no",
                "yes","yes. Business table","grey one",
                new Dimensions(30,5,50)));

        newHouse.getTheOffice().officeOpen();
    }
}
