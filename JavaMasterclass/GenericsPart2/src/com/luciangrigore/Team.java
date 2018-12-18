package com.luciangrigore;

import java.util.ArrayList;

public class Team<T extends Player> implements Comparable<Team<T>> {

    private String name;
    private int played = 0;
    private int won = 0;
    private int lost = 0;
    private int tied = 0;
    private ArrayList<T> members = new ArrayList<>();

    @Override
    public int compareTo(Team<T> team) {
        if (this.ranking() > team.ranking()) {
            return -1;
        } else if (this.ranking() < team.ranking()) {
            return 1;
        } else {
            return 0;
        }
    }

    public Team(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public boolean addPlayer(T player) {
        if (members.contains(player)) {
            System.out.println("Player " + player.getName() + " already on the team!");
            return false;
        }
        members.add(player);
        System.out.println(player.getName() + " added to the squad!");
        return true;
    }

    public int numPlayers() {
        return this.members.size();
    }

    public void matchResult(Team<T> opponent, int ourScore, int theirScore) {
        played++;
        String message;
        if (ourScore > theirScore) {
            won++;
            message = " beat ";
        } else if (ourScore == theirScore) {
            tied++;
            message = " drew with ";
        } else {
            lost++;
            message = " lost to ";
        }
        if (opponent != null) {
            System.out.println(this.getName() + message + opponent.getName());
            opponent.matchResult(null, theirScore, ourScore);
        }
    }

    public int ranking() {
        return (won * 3) + tied;
    }
}
