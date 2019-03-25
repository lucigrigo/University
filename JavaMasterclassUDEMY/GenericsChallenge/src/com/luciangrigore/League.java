package com.luciangrigore;

import java.util.ArrayList;
import java.util.Collections;

public class League<T extends Team> {

    private ArrayList<T> teams = new ArrayList<T>();
    private String leagueName;

    public League(String leagueName) {
        this.leagueName = leagueName;
    }

    public boolean addTeam(T newTeam) {
        if (teams.contains(newTeam)) {
            System.out.println(newTeam.getName() + " already in the league!");
            return false;
        } else {
            teams.add(newTeam);
            System.out.println(newTeam.getName() + " added successfully!");
            return true;
        }
    }

    public void printLeague() {
        Collections.sort(teams);
        for (T t : teams) {
            System.out.println(t.getName() + ": " +
                    t.points() + "p");
        }
    }

}
