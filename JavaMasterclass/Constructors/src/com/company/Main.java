package com.company;

public class Main {

    public static void main(String[] args) {
//        BankAccount abc = new BankAccount(12345,1500,
//                "myEmail@me.com","0716263616263",
//                "LuciGie");
//        System.out.println(abc.getBalance());
//        System.out.println(abc.getCustomerName());
//
//        BankAccount bcd = new BankAccount();
//        System.out.println(bcd.getCustomerName());
//        System.out.println(bcd.getEmail());



        //      CHALLENGE

        VipCustomer adrian = new VipCustomer("Adrian","adi@boss.com",19000);
        System.out.println(adrian.getCreditLimit());
        System.out.println(adrian.getEmailAddress());
        System.out.println(adrian.getName());
    }
}
