package com.luciangrigore;

public class Team implements Comparable<Team> {

    private String name;
    private String stadiumName;

    private int won = 0;
    private int lost = 0;
    private int played = 0;
    private int tied = 0;

    public Team(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }


    public void matchResult(FootballTeam opponent, int ourScore, int theirScore) {
        String message;
        played++;
        if (ourScore > theirScore) {
            won++;
            message = " beat ";
        } else if (ourScore < theirScore) {
            message = " lost to ";
            lost++;
        } else {
            tied++;
            message = " drew with ";
        }

        if (opponent != null) {
            opponent.matchResult(null, theirScore, ourScore);
            System.out.println(this.getName() + message + opponent.getName());
        }
    }


    public int points() {
        return (tied + (3 * won));
    }

    @Override
    public int compareTo(Team opo) {
        if (this.points() == opo.points()) {
            return 0;
        } else if (this.points() < opo.points()) {
            return 1;
        } else {
            return -1;
        }
    }

}
