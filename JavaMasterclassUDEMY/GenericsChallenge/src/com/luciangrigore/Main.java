package com.luciangrigore;

//import java.util.ArrayList;
//import java.util.Collection;
//import java.util.Collections;

public class Main {

    public static void main(String[] args) {
//        ArrayList<Team> teams;
//        Collections.sort(teams);

        League<FootballTeam> championsLeague = new League<>("Champions League by UEFA");

        FootballTeam real = new FootballTeam("Real Madrid");
        FootballTeam juventus = new FootballTeam("Juventus Torino");
        FootballTeam barcelona = new FootballTeam("FC Barcelona");

        championsLeague.addTeam(real);
        championsLeague.addTeam(juventus);
        championsLeague.addTeam(barcelona);

        barcelona.matchResult(real, 3, 2);
        barcelona.matchResult(juventus, 2, 2);
        juventus.matchResult(real, 1, 1);

        championsLeague.printLeague();
    }
}
