package com.company.classAndSubclass;

public class ChildClass1 extends ParentClass {

    public void tryReachOutForPapa() {
        // can use protected methods & members
        super.nrProtected = 100;
        super.doNothingProtected();

        // and public ones
        super.nrPublic = 100;
        super.publicMethod();

        // and default ones
        super.nrPackageProtected = 100;
        super.packageProtectedMethod();
    }

    public void doStuff() {
        System.out.println("heello");
    }
}
