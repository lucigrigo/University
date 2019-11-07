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
        int mostCommonAssetId = Utilities.getInstance().findMostCommonLegalAsset(ownCards);
        if (mostCommonAssetId >= Constants.getInstance().getSmallestIllegalId()) {
            if (coins > Constants.getInstance().getIllegalGoodPenalty()) {
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
                        if (Utilities.getInstance().searchIllegalItems(
                                player.getBag().getAssets(), player.getBag())) {
                            Utilities.getInstance().confiscateBag(this, player, freeGoods);
                        } else {
                            Utilities.getInstance().payPenalty(this, player);
                        }
                    } else {
                        Utilities.getInstance().acceptBribe(this, player);
                    }
                } else {
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
