package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.main.Bag;
import com.tema1.main.Constants;
import com.tema1.main.Utilities;

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
        coins = Constants.getInstance().getStandardInitialCoins();
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
        // aplicarea strategiei de baza
        int mostCommonAssetId = Utilities.getInstance().findMostCommonLegalAsset(ownCards);
        if (mostCommonAssetId >= Constants.getInstance().getSmallestIllegalId()) {
            if (coins > Constants.getInstance().getIllegalGoodPenalty()) {
                // cazul cand in mana are doar carti ilegale
                ownBag.setDominantAsset(0);
                for (int i = 0; i < ownCards.size(); i++) {
                    if (ownCards.get(i).getId() == mostCommonAssetId) {
                        ownBag.getAssets().add(ownCards.get(i));
                        ownCards.remove(i);
                        break;
                    }
                }
            }
        } else {
            // punerea in sac a bunului cel mai frecvent si profitabil
            ownBag.setDominantAsset(mostCommonAssetId);
            for (int i = 0; i < ownCards.size()
                    && ownBag.getAssets().size()
                    < Constants.getInstance().getMaximumBagSize(); i++) {
                if (ownCards.get(i).getId() == mostCommonAssetId) {
                    ownBag.getAssets().add(ownCards.get(i));
                }
            }
            int nr = 0;
            for (int i = ownCards.size() - 1; i >= 0; i--) {
                if (ownCards.get(i).getId() == mostCommonAssetId
                        && nr < Constants.getInstance().getMaximumBagSize()) {
                    ownCards.remove(i);
                    nr++;
                }
            }
        }
        // punerea in sac a unui bun ilegal in rundele pare
        if (!ownCards.isEmpty()) {
            if (Utilities.getInstance().getRoundNr() % 2 == 0
                    && ownBag.getAssets().size() < Constants.getInstance().getMaximumBagSize()
                    && Utilities.getInstance().findMostProfitableIllegalAsset(ownCards) != -1
                    && coins > Constants.getInstance().getIllegalGoodPenalty()) {
                int mostProfitableIllegalAsset
                        = Utilities.getInstance().findMostProfitableIllegalAsset(ownCards);
                for (int i = 0; i < ownCards.size(); i++) {
                    if (ownCards.get(i).getId() == mostProfitableIllegalAsset) {
                        ownBag.getAssets().add(ownCards.get(i));
                        ownCards.remove(i);
                        break;
                    }
                }
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
                if (initCoins >= Constants.getInstance().getInspectionMinimumRequirement()) {
                    if (player.getBag().getBribe() == 0) {
                        // inspectarea sacilor fara mita
                        if (Utilities.getInstance().searchIllegalItems(
                                player.getBag().getAssets(), player.getBag())) {
                            // confiscarea unui sac nonconform
                            Utilities.getInstance().confiscateBag(this, player, freeGoods);
                        } else {
                            // platirea amenzii pentru un sac corect
                            Utilities.getInstance().payPenalty(this, player);
                        }
                    } else {
                        // acceptarea mitei
                        Utilities.getInstance().acceptBribe(this, player);
                    }
                } else {
                    // acceptarea sacilor, dar nu si a mitei cand jucatorul nu are destui bani
                    Utilities.getInstance().acceptBag(player);
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
        ownCards = Utilities.getInstance().getCardsIntoHand(freeGoods);
    }
}
