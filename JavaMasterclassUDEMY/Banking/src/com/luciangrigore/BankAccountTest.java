package com.luciangrigore;

import java.util.concurrent.ExecutionException;

import static org.junit.Assert.*;

public class BankAccountTest {

    private BankAccount account;
    private static int count;

    @org.junit.BeforeClass
    public static void beforeClass() {
        System.out.println("this executes BEFORE any test cases. Count = " + count++);

    }

    @org.junit.Before
    //  Before annotation -> run before every test (method)
    public void setup() {
        account = new BankAccount("Luci", "Grigore", 1000.00, BankAccount.CHEKING);
        System.out.println("Running a test...");
    }

    @org.junit.Test
    public void deposit() {
//        fail("this test has yet to be completed");
//        BankAccount account = new BankAccount("Luci", "Grigore", 1000.00, BankAccount.CHEKING);
        double balance = account.deposit(200.00, true);
        assertEquals(1200.00, balance, 0);
        assertEquals(1200.00, account.getBalance(), 0);
    }

    @org.junit.Test
    public void withdraw_branch() {
//        fail("this test has yet to be completed");
        double balance = account.withdraw(600.00, true);
        assertEquals(400.00, balance, 0);
    }

    @org.junit.Test(expected = IllegalArgumentException.class)
    public void withdraw_notBranch() throws Exception {
        account.withdraw(600.00, false);
        fail("should have thrown an IllegalArgumentException");
//        assertEquals(400.00, balance, 0);

        //  for older versions of JUnit
        try {
            account.withdraw(600.00, false);
            fail("should have thrown an IllegalArgumentException");
        } catch (IllegalArgumentException iae) {

        }
    }

    @org.junit.Test
    public void getBalance_deposit() {
//        fail("this test has yet to be completed");
//        BankAccount account = new BankAccount("Luci", "Grigore", 1000.00, BankAccount.CHEKING);
        account.deposit(200.00, true);
        assertEquals(1200.00, account.getBalance(), 0);
    }

    @org.junit.Test
    public void getBalance_withdraw() {
//        fail("this test has yet to be completed");
//        BankAccount account = new BankAccount("Luci", "Grigore", 1000.00, BankAccount.CHEKING);
        account.withdraw(200.00, true);
        assertEquals(800.00, account.getBalance(), 0);
    }

    @org.junit.Test
    public void isCheking_true() {
//        BankAccount account = new BankAccount("Luci", "Grigore", 1000.00, BankAccount.CHEKING);
//        assertEquals(true, account.isChecking());
        assertTrue("the account is NOT checking account ", account.isChecking());
    }

    @org.junit.AfterClass
    public static void afterClass() {
        System.out.println("this executes AFTER any test cases. Count = " + count);
    }

    //  this executes after each method in the test
    @org.junit.After
    public void teardown() {
        System.out.println("count = " + count++);
    }
}