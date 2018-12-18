package com.luciangrigore;

public class Main {

    public static void main(String[] args) {

        Account luciAcc = new Account("Cont de smeker");
        luciAcc.deposit(1000);
        luciAcc.withdraw(200);
        luciAcc.withdraw(-200);
        luciAcc.deposit(-100);
        luciAcc.calculateBalance();
//        luciAcc.balance = 10000;

        System.out.println("Balance on account is " + luciAcc.getBalance());

    }
}
