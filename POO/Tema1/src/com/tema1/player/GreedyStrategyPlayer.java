package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.main.Bag;
import com.tema1.main.Main;

import java.util.ArrayList;
import java.util.List;

/**
 * Implementeaza strategia de joc GREEDY.
 */
public class GreedyStrategyPlayer implements Player {
    private int initialOrderNr;
    private int finalScore;
    private int coins;
    private Bag ownBag;
    private List<Goods> endGameGoods;
    private List<Goods> ownCards;

    public GreedyStrategyPlayer(final int orderNr) {
        coins = 80;
        finalScore = 0;
        initialOrderNr = orderNr;
        ownCards = new ArrayList<>();
        endGameGoods = new ArrayList<>();
    }

    /**
     * @return cartile din mana
     */
    public List<Goods> getOwnCards() {
        return ownCards;
    }

    /**
     * @return taraba cu bunurile finale
     */
    public List<Goods> getEndGameGoods() {
        return endGameGoods;
    }

    /**
     * @param finalScore scorul final al jucatorului
     */
    public void setFinalScore(final int finalScore) {
        this.finalScore = finalScore;
    }

    /**
     * @return scorul final al player-ului
     */
    public int getFinalScore() {
        return finalScore;
    }

    /**
     * @return numarul initial de ordine al player-ului
     */
    public int getInitialOrderNr() {
        return initialOrderNr;
    }

    /**
     * @return numarul de bani ai jucatorului curent
     */
    public int getCoins() {
        return coins;
    }

    /**
     * @param nr setarea banutilor jocului curent
     */
    @Override
    public void setCoins(final int nr) {
        this.coins = nr;
    }

    /**
     * @return sacul player-ului curent
     */
    @Override
    public Bag getBag() {
        return ownBag;
    }

    /**
     * @return numele tipului de player
     */
    @Override
    public String getType() {
        return "GREEDY";
    }

    /**
     * Crearea sacului din perspectiva GREEDY.
     */
    @Override
    public void bagCreation() {
        ownBag = new Bag();
        ownBag.setBribe(0);
        int mostCommonAssetId = Main.utilities.findMostCommonLegalAsset(ownCards);
        if (mostCommonAssetId >= 20) {
            if (coins > 4) {
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
//            int potentialPenalty = 0;
            for (int i = 0; i < ownCards.size(); i++) {
                if (ownCards.get(i).getId() == mostCommonAssetId) {
//                    System.out.println("adauga - " + ownCards.get(i).getId());
//                    potentialPenalty += ownCards.get(i).getPenalty();
//                    if (potentialPenalty > coins) {
//                        break;
//                    }
                    ownBag.getAssets().add(ownCards.get(i));
                }
            }
            ownCards.removeIf((Goods g) -> g.getId() == mostCommonAssetId);
        }
        if (!ownCards.isEmpty()) {
            if (Main.utilities.getRoundNr() % 2 == 0
                    && ownBag.getAssets().size() < 8
                    && Main.utilities.findMostProfitableIllegalAsset(ownCards) != -1
                    && coins > 4) {
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
    }

    /**
     * Inspectarea jucatorilor din perspectiva GREEDY.
     *
     * @param players   lista de jucatori
     * @param freeGoods gramada de carti libere
     */
    @Override
    public void inspection(final List<Player> players,
                           final List<Integer> freeGoods) {
        int initCoins = coins;
        for (Player player : players) {
            if (player != this) {
                if (initCoins >= 16) {
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
//                    Main.utilities.acceptBribe(this, player);
                }
            }
        }
    }

    /**
     * Re/completarea cartilor din mana.
     *
     * @param freeGoods gramada de carti libere
     */
    @Override
    public void handRefill(final List<Integer> freeGoods) {
        ownCards = Main.utilities.getCardsIntoHand(ownCards, freeGoods);
    }
}
