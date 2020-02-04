package com.company.classAndSubclass;

public class ParentClass {
    private int nrPrivate = 1;

    private void doNothingPrivate() {
        // private
    }

    protected int nrProtected = 2;

    protected void doNothingProtected() {
        // protected
    }

    public int nrPublic = 3;

    public void publicMethod() {
        // public
    }

    int nrPackageProtected = 4;

    void packageProtectedMethod() {
        // package-protected / package-private
    }

    public final void doIt() {
        doStuff();
    }

    public void doStuff() {
        System.out.println("hello");
    }
}
