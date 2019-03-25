//  Lecture   115
//  Section    10

package com.luciangrigore;

public class Main {

    public static void main(String[] args) {
        FootballPlayer joe = new FootballPlayer("Joe");
        BaseballPlayer pat = new BaseballPlayer("Pat");
        SoccerPlayer leo = new SoccerPlayer("Leo");

        Team<FootballPlayer> steaua = new Team<>("Steaua");
        steaua.addPlayer(joe);
//        steaua.addPlayer(pat);
//        steaua.addPlayer(leo);

        System.out.println(steaua.numPlayers());

        Team<BaseballPlayer> baseballTeam = new Team<>("Chicago Cubs");
        baseballTeam.addPlayer(pat);

//        Team<String> brokenTeam = new Team<>("Won't work");
//        brokenTeam.addPlayer("No-one");

        SoccerPlayer ronaldo = new SoccerPlayer("CR7");
        SoccerPlayer marcelo = new SoccerPlayer("Marcelo");
        SoccerPlayer suarez = new SoccerPlayer("The cannibal");

        Team<SoccerPlayer> barcelona = new Team<>("FC Barcelona");
        barcelona.addPlayer(leo);
        barcelona.addPlayer(suarez);

        Team<SoccerPlayer> real = new Team<>("Real Madrid");
        real.addPlayer(marcelo);
        real.addPlayer(ronaldo);

        barcelona.matchResult(real, 3, 2);

//        barcelona.matchResult(baseballTeam,2,3);

        System.out.println("Rankings");
        System.out.println(barcelona.getName() + " : " + barcelona.ranking() + "p");
        System.out.println(real.getName() + " : " + real.ranking() + "p");

        System.out.println(barcelona.compareTo(real));
        System.out.println(real.compareTo(barcelona));
        System.out.println(real.compareTo(real));
    }
}
