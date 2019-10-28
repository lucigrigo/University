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
//        System.out.println("are in mana cartile");
//        for(Goods good : ownCards) {
////            System.out.print(good.getId() + ",");
//        }
//        System.out.println(" ======== ");
//        if (coins >= 4) {
        ownBag = new Bag();
        ownBag.setBribe(0);
        int mostCommonAssetId = Main.utilities.findMostCommonLegalAsset(ownCards);
        if (mostCommonAssetId >= 20) {
            if (coins >= 4) {
                ownBag.setDominantAsset(0);
                for (int i = 0; i < ownCards.size(); i++) {
                    if (ownCards.get(i).getId() == mostCommonAssetId) {
                        ownBag.getAssets().add(ownCards.get(i));
                        ownCards.remove(i);
                        break;
                    }
                }
            }
//            System.out.println("---" + ownBag.getAssets().get(0).getId());
        } else {
            ownBag.setDominantAsset(mostCommonAssetId);
            int potentialPenalty = 0;
            for (int i = 0; i < ownCards.size(); i++) {
                if (ownCards.get(i).getId() == mostCommonAssetId) {
//                    System.out.println("adauga - " + ownCards.get(i).getId());
                    potentialPenalty += ownCards.get(i).getPenalty();
                    if (potentialPenalty > coins) {
                        break;
                    }
                    ownBag.getAssets().add(ownCards.get(i));
                }
            }
            ownCards.removeIf((Goods g) -> g.getId() == mostCommonAssetId);
        }
        if (!ownCards.isEmpty()) {
            if (Main.utilities.getRoundNr() % 2 == 0
                    && ownBag.getAssets().size() < 8
                    && Main.utilities.findMostProfitableIllegalAsset(ownCards) != -1
                    && coins >= 4) {
                int mostProfitableIllegalAsset = Main.utilities.findMostProfitableIllegalAsset(ownCards);
                for (int i = 0; i < ownCards.size(); i++) {
                    if (ownCards.get(i).getId() == mostProfitableIllegalAsset) {
                        ownBag.getAssets().add(ownCards.get(i));
                        break;
                    }
                }
                ownCards.removeIf((Goods g) -> g.getId() == mostProfitableIllegalAsset);
            }
        }
//        }

        for (Goods good : ownBag.getAssets()) {
//            System.out.println(good.getId());
        }
//        System.out.println("\n");
    }

    @Override
    public void inspection(List<Player> players, List<Integer> freeGoods) {
        for (Player player : players) {
            if (player != this) {
                if (coins >= 16) {
                    if (player.getBag().getBribe() == 0) {
                        if (Main.utilities.searchIllegalItems(player.getBag().getAssets(), player.getBag())) {
                            Main.utilities.confiscateBag(this, player, freeGoods);
                        } else {
//                        System.out.println("de 2 ori aici");
                            Main.utilities.payPenalty(this, player);
                        }
                    } else {
                        Main.utilities.acceptBribe(this, player);
                    }
                } else {
                    Main.utilities.acceptBag(this, player);
                }
            }
        }
    }

    @Override
    public void handRefill(List<Integer> freeGoods) {
        ownCards = Main.utilities.getCardsIntoHand(ownCards, freeGoods);
    }
}
