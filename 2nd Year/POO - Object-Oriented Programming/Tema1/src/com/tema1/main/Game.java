package com.tema1.main;

import com.tema1.player.Player;

import java.util.List;

/**
 * Clasa care implementeaza desfasurarea jocului.
 */
public final class Game {

    private int nrRounds;
    private static Game instance = null;

    private Game() {
        nrRounds = 0;
    }

    /**
     * @return instanta clasei de joc
     */
    public static Game getInstance() {
        if (instance == null) {
            instance = new Game();
        }
        return instance;
    }

    /**
     * Functia principala de desfasurare a jocului, realizand toti
     * pasii pentru fiecare runda si sub-runda.
     *
     * @param players   jucatorii care iau parte la joc
     * @param freeGoods cartile care nu au ajuns in mana niciunui jucator
     * @param maxRounds numarul maxim de runde
     */
    public void startGame(final List<Player> players,
                          final List<Integer> freeGoods,
                          final int maxRounds) {
        Utilities.getInstance().setNrRounds(1);
        while (nrRounds < Constants.getInstance().getMaximumRoundsNumber()
                && nrRounds < maxRounds) {
            // facem pe rand fiecare jucator serif
            for (Player sheriffPlayer : players) {
                for (Player nonSheriffPlayer : players) {
                    if (sheriffPlayer != nonSheriffPlayer) {
                        // fiecare jucator care nu e serif ia in mana 10 carti de joc
                        nonSheriffPlayer.handRefill(freeGoods);
                        // crearea sacilor jucatorilor
                        nonSheriffPlayer.bagCreation();
                    }
                }
                // inspectarea sacilor celorlalti jucatori
                sheriffPlayer.inspection(players, freeGoods);
            }
            // incrementarea numarului de runde
            nrRounds++;
            // acest numar de runde (din Utilities) e folosit in cazul jucatorului "GREEDY"
            Utilities.getInstance().setNrRounds(nrRounds + 1);
        }
    }

    /**
     * Functia care se ocupa de finalizarea jocului.
     *
     * @param players jucatorii care iau parte la joc
     */
    public void endGame(final List<Player> players) {
        // calcularea scorului final - fara bonusuri
        Utilities.getInstance().computeFinalScore(players);
        // adaugarea bonusurilor la scorul final
        Utilities.getInstance().addKQFinalBonus(players);
        // scrierea rezultatelor jocului in fisierul de output
        Utilities.getInstance().writeEndGameResults(players);
    }
}
