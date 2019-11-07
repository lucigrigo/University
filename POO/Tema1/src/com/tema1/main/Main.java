package com.tema1.main;

import com.tema1.player.BaseStrategyPlayer;
import com.tema1.player.BribeStrategyPlayer;
import com.tema1.player.GreedyStrategyPlayer;
import com.tema1.player.Player;

import java.util.ArrayList;
import java.util.List;

public final class Main {

    private Main() {
        // doar ca sa treaca la checkstyle
    }

    public static void main(final String[] args) {
        // citirea datelor in fisierul de intrare
        GameInputLoader gameInputLoader = new GameInputLoader(args[0], args[1]);
        GameInput gameInput = gameInputLoader.load();

        // testarea daca input-ul este valid
        if (!gameInput.isValidInput()) {
            System.out.println("INPUT INVALID!");
            System.exit(1);
        }

        // initializarea jucatorilor din meci
        List<Player> players = new ArrayList<>(gameInput.getPlayerNames().size());
        for (String name : gameInput.getPlayerNames()) {
            switch (name) {
                case "bribed":
                    players.add(new BribeStrategyPlayer(players.size()));
                    break;
                case "greedy":
                    players.add(new GreedyStrategyPlayer(players.size()));
                    break;
                case "basic":
                    players.add(new BaseStrategyPlayer(players.size()));
                    break;
                default:
                    System.out.println("TIP DE PLAYER INVALID");
                    break;
            }
        }

        // initializarea unei instante de joc
        Game game = Game.getInstance();

        //  inceperea jocului
        game.startGame(players, gameInput.getAssetIds(), gameInput.getRounds());

        // finalizarea jocului
        game.endGame(players);
    }
}
