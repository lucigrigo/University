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
    private boolean canBeInspector = true;

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
        if (mostCommonAssetId >= 20) {
            if (coins > 4) {
                ownBag.setDominantAsset(0);
                int mostProfitableIllegalAsset = Main.utilities.findMostProfitableIllegalAsset(ownCards);
                for (int i = 0; i < ownCards.size(); i++) {
                    if (ownCards.get(i).getId() == mostProfitableIllegalAsset) {
                        ownBag.getAssets().add(ownCards.get(i));
                        ownCards.remove(i);
                        break;
                    }
                }
            }
        } else {
//            int possiblePenalty = 0;
            ownBag.setDominantAsset(mostCommonAssetId);
            for (int i = 0; i < ownCards.size(); i++) {
                if (ownCards.get(i).getId() == mostCommonAssetId) {
//                    possiblePenalty += ownCards.get(i).getPenalty();
//                    if (possiblePenalty >= coins) {
//                        break;
//                    }
                    ownBag.getAssets().add(ownCards.get(i));
                }
            }
            ownCards.removeIf((Goods g) -> g.getId() == mostCommonAssetId);
        }
    }

    @Override
    public void inspection(List<Player> players, List<Integer> freeGoods) {
        for (Player player : players) {
            if (this != player
                    && coins >= 16
                    && canBeInspector) {
                // intoarcerea mitei in mana comerciantului
                player.setCoins(player.getCoins() + player.getBag().getBribe());
                player.getBag().setBribe(0);
                // verificarea sacilor
                if (Main.utilities.searchIllegalItems(player.getBag().getAssets(), player.getBag())) {
                    // confiscarea unui sac ilegal
                    Main.utilities.confiscateBag(this, player, freeGoods);
                } else {
                    // cazul in care a cercetat un sac in regula
                    Main.utilities.payPenalty(this, player);
                }
            } else if (this != player) {
//                System.out.println("jucatorul " + this.getType() + " " + this.getInitialOrderNr()
//                        + " nu mai are bani de inspectat pe " + player.getType() + " " + player.getInitialOrderNr());
                Main.utilities.acceptBag(this, player);
//                canBeInspector = false;
            }
        }
    }

    @Override
    public void handRefill(List<Integer> freeGoods) {
        ownCards = Main.utilities.getCardsIntoHand(ownCards, freeGoods);
    }
}
