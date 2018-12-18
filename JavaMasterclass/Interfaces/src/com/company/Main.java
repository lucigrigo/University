package com.company;

public class Main {

    public static void main(String[] args) {

        ITelephone timsPhone;
        timsPhone = new Deskphone(12345);
        timsPhone.powerOn();
        timsPhone.callPhone(12345);
        timsPhone.answer();


        timsPhone = new MobilePhone(1234);
        timsPhone.powerOn();
        timsPhone.callPhone(1234567);
        timsPhone.answer();

    }
}
