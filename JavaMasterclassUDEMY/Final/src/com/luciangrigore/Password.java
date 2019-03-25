package com.luciangrigore;

public class Password {

    private static final int key = 716528975;
    private final int encryptedPassword;

    public Password(int password) {
        this.encryptedPassword = encryptDecrypt(password);
    }

    private int encryptDecrypt(int password) {
        return password ^ key;
    }

    public final void storePassword() {
        System.out.println("Saving password as " + this.encryptedPassword);
    }

    public boolean letMeIn(int password) {
        if (encryptDecrypt(password) == this.encryptedPassword) {
            System.out.println("Welcome, boss!");
            return true;
        } else {
            System.out.println("You shall not pass!");
            return false;
        }
    }
}
