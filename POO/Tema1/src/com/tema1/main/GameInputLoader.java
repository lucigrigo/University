package com.tema1.main;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public final class GameInputLoader {
    private final String mInputPath;
    private final String mOutputPath;

    public GameInputLoader(final String inputPath, final String outputPath) {
        mInputPath = inputPath;
        mOutputPath = outputPath;
    }

    public String getmOutputPath() {
        return mOutputPath;
    }

    public GameInput load() {
        List<Integer> assetsIds = new ArrayList<>();
        List<String> playerOrder = new ArrayList<>();
        int rounds = 0;
        int noPlayers = 0;
        int noGoods = 0;
        File inputFile = new File(mInputPath);

        try {
            Scanner scanner = new Scanner(inputFile);
            rounds = scanner.nextInt();
            noPlayers = scanner.nextInt();
            for (int i = 0; i < noPlayers; i++) {
                playerOrder.add(scanner.next());
            }
            noGoods = scanner.nextInt();
            for (int i = 0; i < noGoods; i++) {
                assetsIds.add(scanner.nextInt());
            }
            scanner.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
        return new GameInput(rounds, assetsIds, playerOrder);
    }
}
