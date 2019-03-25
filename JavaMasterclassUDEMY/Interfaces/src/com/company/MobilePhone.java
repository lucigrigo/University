package com.company;

public class MobilePhone implements ITelephone {

    private int myNumber;
    private boolean isRinging;
    private boolean isOn = false;

    public MobilePhone(int myNumber) {
        this.myNumber = myNumber;
    }

    @Override
    public void powerOn() {
        isOn = true;
        System.out.println("The phone is powering up");
    }

    @Override
    public void dial(int phoneNumber) {
        if (isOn) {
            System.out.println("Now calling " + phoneNumber + " on mobilephone.");
        } else {
            System.out.println("Phone is switched off !");
        }
    }

    @Override
    public void answer() {
        if (isRinging) {
            System.out.println("Answering the mobile phone");
            isRinging = false;
        } else {
            System.out.println("No phonecalls to answer");
        }
    }

    @Override
    public boolean callPhone(int phoneNumber) {
        if (phoneNumber == myNumber && isOn) {
            isRinging = true;
            System.out.println("RING RING");
        } else if (isOn) {
            isRinging = true;
            System.out.println("Now calling " + phoneNumber);
        } else {
            isRinging = false;
            System.out.println("Phone switched off!");
        }
        return isRinging;
    }

    @Override
    public boolean isRinging() {
        return isRinging;
    }
}

