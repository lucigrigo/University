package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.main.Bag;
import com.tema1.main.Main;

import java.util.ArrayList;
import java.util.List;

public class GreedyStrategyPlayer implements Player {
    private static final Strategy strategy = Strategy.GREEDY;
    private int initialOrderNr;
    private int finalScore;
    private int coins;
    private Bag ownBag;
    private List<Goods> endGameGoods;
    private List<Goods> ownCards;

    public GreedyStrategyPlayer(int orderNr) {
        coins = 80;
        finalScore = 0;
        initialOrderNr = orderNr;
        ownCards = new ArrayList<>();
        endGameGoods = new ArrayList<>();
    }

    public List<Goods> getOwnCards() {
        return ownCards;
    }

    public List<Goods> getEndGameGoods() {
        return endGameGoods;
    }

    public void setFinalScore(int finalScore) {
        this.finalScore = finalScore;
    }

    public int getFinalScore() {
        return finalScore;
    }

    public int getInitialOrderNr() {
        return initialOrderNr;
    }

    public int getCoins() {
        return coins;
    }

    @Override
    public void setCoins(int nr) {
        this.coins = nr;
    }

    @Override
    public Bag getBag() {
        return ownBag;
    }

    @Override
    public String getType() {
        return "GREEDY";
    }

    @Override
    public void bagCreation() {
        ownBag = new Bag();
        ownBag.setBribe(0);
        int mostCommonAssetId = Main.utilities.findMostCommonLegalAsset(ownCards);
        for (int i = 0; i < ownCards.size(); i++) {
            if (ownCards.get(i).getId() == mostCommonAssetId) {
                ownBag.getAssets().add(ownCards.get(i));
            }
        }
        if (mostCommonAssetId < 20) {
            ownBag.setDominantAsset(mostCommonAssetId);
        } else {
            ownBag.setDominantAsset(0);
        }
        if (Main.utilities.getRoundNr() % 2 == 0 &&
                ownBag.getAssets().size() < 8 &&
                Main.utilities.findMostCommonLegalAsset(ownCards) != -1) {
            for (int i = 0; i < ownCards.size(); i++) {
                if (ownCards.get(i).getId() == mostCommonAssetId) {
                    ownBag.getAssets().add(ownCards.get(i));
                    ownCards.remove(i);
                }
            }
        }
    }

    @Override
    public void inspection(List<Player> players, List<Integer> freeGoods) {
        for (Player player : players) {
            if (player != this) {
                if (player.getBag().getBribe() == 0) {
                    if (Main.utilities.searchIllegalItems(player.getBag().getAssets())) {
                        Main.utilities.confiscateBag(this, player, freeGoods);
                    } else {
                        Main.utilities.payPenalty(this, player);
                    }
                } else {
                    Main.utilities.acceptBribe(this, player);
                }
            }
        }
    }

    @Override
    public void handRefill(List<Integer> freeGoods) {
        Main.utilities.getCardsIntoHand(ownCards, freeGoods);
    }
}
