package com.tema1.main;

import com.tema1.player.Player;

import java.util.List;

public final class Game {

    private int nrRounds;
    private static Game instance = null;

    private Game() {
        nrRounds = 0;
    }

    public static Game getInstance() {
        if (instance == null) {
            instance = new Game();
        }
        return instance;
    }

    public void startGame(List<Player> players, List<Integer> freeGoods, int maxRounds) {
        Main.utilities.setNrRounds(1);
        while (nrRounds < 5 && nrRounds < maxRounds) {
            // facem pe rand fiecare jucator serif
            for (Player sheriffPlayer : players) {
                for (Player nonSheriffPlayer : players) {
                    if (sheriffPlayer != nonSheriffPlayer) {
                        // fiecare jucator ia in mana 10 carti de joc
                        nonSheriffPlayer.handRefill(freeGoods);
                        // crearea sacilor celorlalti jucatori
                        nonSheriffPlayer.bagCreation();
                    }
                }
                // inspectarea sacilor celorlalti jucatori
                sheriffPlayer.inspection(players, freeGoods);
            }
            nrRounds++;
            Main.utilities.setNrRounds(nrRounds + 1);
        }
    }

    public void endGame(List<Player> players) {
        // calcularea scorului final - fara bonusuri
        Main.utilities.computeFinalScore(players);

        // adaugarea bonusurilor la scorul final
        Main.utilities.addKQFinalBonus(players);

        // scrierea rezultatelor jocului in fisierul de output
        Main.utilities.writeEndGameResults(players);
    }
}
