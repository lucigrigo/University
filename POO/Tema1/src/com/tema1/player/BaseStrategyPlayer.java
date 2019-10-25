package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.main.Bag;
import com.tema1.main.Main;

import java.util.ArrayList;
import java.util.List;

public class BaseStrategyPlayer implements Player {
    private static final Strategy strategy = Strategy.BASE;
    private int initialOrderNr;
    private int finalScore;
    private int coins;
    private Bag ownBag;
    private List<Goods> endGameGoods;
    private List<Goods> ownCards;

    public BaseStrategyPlayer(int orderNr) {
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
        return "BASIC";
    }

    @Override
    public void bagCreation() {
        ownBag = new Bag();
        ownBag.setBribe(0);
        int mostCommonAssetId = Main.utilities.findMostCommonLegalAsset(ownCards);
        for (int i = 0; i < ownCards.size(); i++) {
            if (ownCards.get(i).getId() == mostCommonAssetId) {
                ownBag.getAssets().add(ownCards.get(i));
//                ownCards.remove(i);
            }
        }
        if (mostCommonAssetId < 20) {
            ownBag.setDominantAsset(mostCommonAssetId);
        } else {
            ownBag.setDominantAsset(0);
        }
    }

    @Override
    public void inspection(List<Player> players, List<Integer> freeGoods) {
        for (Player player : players) {
            if (this != player
                    && coins > 16) {
                // intoarcerea mitei in mana comerciantului
                player.setCoins(player.getCoins() + player.getBag().getBribe());
                player.getBag().setBribe(0);
                // verificarea sacilor
                if (Main.utilities.searchIllegalItems(player.getBag().getAssets())) {
                    // cazul in care gaseste un sac ilegal
                    Main.utilities.confiscateBag(this, player, freeGoods);
                } else {
                    // cazul in care a cercetat un sac in regula
                    Main.utilities.payPenalty(this, player);
                }
            }
        }
    }

    @Override
    public void handRefill(List<Integer> freeGoods) {
        Main.utilities.getCardsIntoHand(ownCards, freeGoods);
    }
}
