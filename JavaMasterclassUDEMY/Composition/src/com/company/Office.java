package com.company;

public class Office {
    private String owner,sofa,desk,table,chair;
    private Dimensions masuriBirou;

    public Office(String owner, String sofa, String desk, String table,
                  String chair, Dimensions masuriBirou) {
        this.owner = owner;
        this.sofa = sofa;
        this.desk = desk;
        this.table = table;
        this.chair = chair;
        this.masuriBirou = masuriBirou;
    }

    public void officeOpen(){
        System.out.println("Office is open !!");
        System.out.println("Your belongings are not safe !");
    }
}
