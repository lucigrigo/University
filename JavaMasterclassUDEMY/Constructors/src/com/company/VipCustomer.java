package com.company;

public class VipCustomer {
    private String name, emailAddress;
    private int creditLimit;

    public VipCustomer(){
        this("Unknown Name","No Email Given",0);
    }

    public VipCustomer(String name, String emailAddress, int creditLimit) {
        this.name = name;
        this.emailAddress = emailAddress;
        this.creditLimit = creditLimit;
    }

    public VipCustomer(String name, int creditLimit) {
        this(name, "No Email Address given", creditLimit);
    }

    public int getCreditLimit() {
        return creditLimit;
    }

    public String getEmailAddress() {
        return emailAddress;
    }

    public String getName() {
        return name;
    }
}
