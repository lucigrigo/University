package com.company;

public class Deskphone implements ITelephone {

    private int myNumber;
    private boolean isRinging;

    public Deskphone(int myNumber) {
        this.myNumber = myNumber;
    }

    @Override
    public void powerOn() {
        System.out.println("The deskphone has no power button!");
    }

    @Override
    public void dial(int phoneNumber) {
        System.out.println("Now calling " + phoneNumber + ".");
    }

    @Override
    public void answer() {
        if (isRinging) {
            System.out.println("Answering the deskphone");
            isRinging = false;
        } else {
            System.out.println("No phonecalls to answer");
        }
    }

    @Override
    public boolean callPhone(int phoneNumber) {
        if (phoneNumber == myNumber) {
            isRinging = true;
            System.out.println("RING RING");
        } else {
            isRinging = false;
        }
        return isRinging;
    }

    @Override
    public boolean isRinging() {
        return isRinging;
    }
}
