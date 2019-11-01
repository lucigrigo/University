package com.tema1.main;

import com.tema1.goods.Goods;
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
<<<<<<< HEAD
            System.out.println("--- RUNDA " + Main.utilities.getNrRounds() + "---");
            // facem pe rand fiecare jucator serif
=======
//            System.out.println("---\tRUNDA " + Main.utilities.getNrRounds() + "\t---");
//             facem pe rand fiecare jucator serif
>>>>>>> df91f3181055b19c86a79eaa0fcab5c280f7f1db
            for (Player sheriffPlayer : players) {
                for (Player nonSheriffPlayer : players) {
                    if (sheriffPlayer != nonSheriffPlayer) {
                        // fiecare jucator ia in mana 10 carti de joc
                        nonSheriffPlayer.handRefill(freeGoods);
                        // crearea sacilor celorlalti jucatori
                        System.out.println("CARTILE lui " + nonSheriffPlayer.getType() + " " + nonSheriffPlayer.getInitialOrderNr() + " (coins = " + nonSheriffPlayer.getCoins() + ") sunt:");
                        for (Goods good : nonSheriffPlayer.getOwnCards()) {
                            System.out.print(good.getId() + ",");
                        }
                        System.out.println();
                        nonSheriffPlayer.bagCreation();
                        System.out.println("si baga in SAC cartile:");
                        for (Goods good : nonSheriffPlayer.getBag().getAssets()) {
                            System.out.print(good.getId() + ",");
                        }
                        System.out.println("\nbribe = " + nonSheriffPlayer.getBag().getBribe());
                        System.out.println("\n");
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
        System.out.println("---ITEMELE DE LA FINAL SUNT---");
        for (Player player : players) {
            System.out.println("Player " + player.getType() + " " + player.getInitialOrderNr() + " coins = " + player.getCoins());
            for (Goods good : player.getEndGameGoods()) {
                System.out.print(good.getId() + ",");
            }
            System.out.println();
        }
        // calcularea scorului final - fara bonusuri
        Main.utilities.computeFinalScore(players);

        // adaugarea bonusurilor la scorul final
        Main.utilities.addKQFinalBonus(players);

        // scrierea rezultatelor jocului in fisierul de output
        Main.utilities.writeEndGameResults(players);
    }
}
