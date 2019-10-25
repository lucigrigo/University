package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.goods.GoodsType;
import com.tema1.main.Bag;
import com.tema1.main.Main;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class BribeStrategyPlayer implements Player {
    private static final Strategy strategy = Strategy.BRIBE;
    private int initialOrderNr;
    private int finalScore;
    private int coins;
    private Bag ownBag;
    private List<Goods> endGameGoods;
    private List<Goods> ownCards;

    public BribeStrategyPlayer(int orderNr) {
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
        return "BRIBE";
    }

    @Override
    public void bagCreation() {
        ownBag = new Bag();
        if (coins < 10 ||
                !Main.utilities.searchIllegalItems(ownCards)) {
            ownBag.setBribe(0);
            int mostCommonAssetId = Main.utilities.findMostCommonLegalAsset(ownCards);
            for (int i = 0; i < ownCards.size(); i++) {
                if (ownCards.get(i).getId() == mostCommonAssetId) {
                    ownBag.getAssets().add(ownCards.get(i));
                    ownCards.remove(i);
                }
            }
            if (mostCommonAssetId < 20) {
                ownBag.setDominantAsset(mostCommonAssetId);
            } else {
                ownBag.setDominantAsset(0);
            }
        } else {
            int nrIllegalGoods = 0;
            ownBag.setDominantAsset(0);
//            ownCards.sort((Goods good1, Goods good2) ->
//                    good2.getProfit() - good1.getProfit());
            ownCards.sort(Comparator.comparing(Goods::getProfit).thenComparing(Goods::getId));
            Collections.reverse(ownCards);
            while (!ownCards.isEmpty() &&
                    ownCards.get(0).getType() == GoodsType.Illegal &&
                    ownBag.getAssets().size() < 8) {
                ownBag.getAssets().add(ownCards.get(0));
                ownCards.remove(0);
                nrIllegalGoods++;
            }
            if (nrIllegalGoods <= 2) {
                ownBag.setBribe(5);
                coins -= 5;
            } else {
                ownBag.setBribe(10);
                coins -= 10;
            }
            ownBag.setDominantAsset(0);
            while (!ownCards.isEmpty() &&
                    ownBag.getAssets().size() < 8) {
                ownBag.getAssets().add(ownCards.get(0));
                ownCards.remove(0);
            }
        }
    }

    @Override
    public void inspection(List<Player> players, List<Integer> freeGoods) {
        for (Player player : players) {
            if (player != this) {
                if (Math.abs(player.getInitialOrderNr() - initialOrderNr) == 1
                        || Math.abs(player.getInitialOrderNr()) - initialOrderNr == (players.size() - 1)) {
                    if (this.coins > 16) {
                        // intoarcerea mitei in mana comerciantului
                        player.setCoins(player.getCoins() + player.getBag().getBribe());
                        player.getBag().setBribe(0);
                        if (Main.utilities.searchIllegalItems(player.getBag().getAssets())) {
                            Main.utilities.confiscateBag(this, player, freeGoods);
                        } else {
                            Main.utilities.payPenalty(this, player);
                        }
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
