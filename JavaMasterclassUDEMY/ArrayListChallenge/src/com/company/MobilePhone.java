package com.company;

import java.util.ArrayList;

public class MobilePhone {

    private ArrayList<Contacts> Contacts = new ArrayList<Contacts>();

    private String owner;
    private String ownNumber;

    public MobilePhone(String owner, String ownNumber) {
        this.owner = owner;
        this.ownNumber = ownNumber;
    }

    public void printList() {
        if (Contacts.isEmpty() == true) {
            System.out.println("There are no contacts in your contacts list !");
        } else {
            System.out.println("You have " + Contacts.size() + " contacts :");
            for (int i = 0; i < Contacts.size(); i++) {
                System.out.print(i + 1 + "# " +
                        Contacts.get(i).getName() + " - " +
                        Contacts.get(i).getNumber());
                System.out.println();
            }
        }
    }

    public boolean searchContact(int nr) {
        com.company.Contacts cont = new Contacts(nr,new String());
        if (Contacts.indexOf(cont) != (-1)) {
            return true;
        } else {
            return false;
        }
    }

    public boolean searchContact(String name) {
        if ((Contacts.indexOf(new Contacts(name))) != (-1)) {
            return true;
        } else {
            return false;
        }
    }

    public void addContact(String name, int nr) {
        Contacts.add(new Contacts(nr, name));
        System.out.println("Contact added succesfully !");
    }

    public void updateContact(String nm, int nr) {
        int i = Contacts.indexOf(new Contacts(nm));
        Contacts.set(i, new Contacts(nr, nm));
        System.out.println("Contact updated succesfully !");
    }

    public void updateContact(int number, String newName) {
        int i = Contacts.indexOf(new Contacts(number));
        Contacts.set(i, new Contacts(number, newName));
        System.out.println("Contact updated succesfully !");
    }

    public void removeContact(int number) {
        int i = Contacts.indexOf(new Contacts(number));
        Contacts.remove(i);
        System.out.println("Contact removed succesfully !");
    }

    public void removeContact(String name) {
        int i = Contacts.indexOf(new Contacts(name));
        Contacts.remove(i);
        System.out.println("Contact removed succesfully !");
    }

    public void printContact(String name) {
        int i = Contacts.indexOf(new Contacts(name));
        System.out.println(Contacts.get(i));
    }

    public void printContact(int nr) {
        int i = Contacts.indexOf(new Contacts(nr));
        System.out.println(Contacts.get(i));
    }
}
