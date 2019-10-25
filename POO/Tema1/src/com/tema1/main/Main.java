package com.tema1.main;

import com.tema1.goods.GoodsFactory;
import com.tema1.player.BaseStrategyPlayer;
import com.tema1.player.BribeStrategyPlayer;
import com.tema1.player.GreedyStrategyPlayer;
import com.tema1.player.Player;

import java.util.ArrayList;
import java.util.List;

public class Main {

    //    private static Game game;
    public static Utilities utilities;
    public static GoodsFactory goodsFactory;


    public static void main(final String[] args) {
        // citirea datelor in fisierul de intrare
        GameInputLoader gameInputLoader = new GameInputLoader(args[0], args[1]);
        GameInput gameInput = gameInputLoader.load();

        // testarea daca input-ul este valid
        if (!gameInput.isValidInput()) {
            System.out.println("INPUT INVALID!");
            System.exit(1);
        }

        // initializarea unei instante a unei clase de utilitati
        utilities = Utilities.getInstance();

        // initializarea datelor legate de bunuri
        goodsFactory = GoodsFactory.getInstance();

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
            }
        }

        // initializarea unei instante de joc
        Game game = Game.getInstance();

        //  inceperea jocului
        game.startGame(players, gameInput.getAssetIds(), gameInput.getRounds());

        // finalizarea jocului
        // - calcularea scorului final pentru fiecare jucator
        // - adaugarea bonusurilor de King/Queen
        game.endGame(players);
    }
}
