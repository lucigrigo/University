package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.main.Bag;
import com.tema1.main.Constants;
import com.tema1.main.Utilities;

import java.util.ArrayList;
import java.util.List;

/**
 * Implementeaza strategia de joc BASIC.
 */
public class BaseStrategyPlayer implements Player {
    private int initialOrderNr;
    private int finalScore;
    private int coins;
    private Bag ownBag;
    private List<Goods> endGameGoods;
    private List<Goods> ownCards;

    public BaseStrategyPlayer(final int orderNr) {
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
     * @return bunurile de pe taraba
     */
    public List<Goods> getEndGameGoods() {
        return endGameGoods;
    }

    /**
     * @param finalScore scorul final
     */
    public void setFinalScore(final int finalScore) {
        this.finalScore = finalScore;
    }

    /**
     * @return scorul final
     */
    public int getFinalScore() {
        return finalScore;
    }

    /**
     * @return numarul initial de ordine
     */
    public int getInitialOrderNr() {
        return initialOrderNr;
    }

    /**
     * @return banii din mana jucatorului
     */
    public int getCoins() {
        return coins;
    }

    /**
     * @param nr numarul de coins
     */
    @Override
    public void setCoins(final int nr) {
        this.coins = nr;
    }

    /**
     * @return sacul jucatorului curent
     */
    @Override
    public Bag getBag() {
        return ownBag;
    }

    /**
     * @return tipul jucatorului curent
     */
    @Override
    public String getType() {
        return "BASIC";
    }

    /**
     * Crearea sacului din perspectiva BASIC.
     */
    @Override
    public void bagCreation() {
        ownBag = new Bag();
        ownBag.setBribe(0);
        int mostCommonAssetId = Utilities.getInstance().findMostCommonLegalAsset(ownCards);
        // cazul in care in mana sunt doar carti ilegale
        if (mostCommonAssetId >= Constants.getInstance().getSmallestIllegalId()) {
            if (coins > Constants.getInstance().getIllegalGoodPenalty()) {
                ownBag.setDominantAsset(0);
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
        } else {
            // punerea in sac a bunului legal cel mai frecvent si profitabil
            ownBag.setDominantAsset(mostCommonAssetId);
            for (int i = 0; i < ownCards.size(); i++) {
                if (ownCards.get(i).getId() == mostCommonAssetId) {
                    ownBag.getAssets().add(ownCards.get(i));
                }
            }
            int nr = 0;
            // scoaterea din mana a cartilor puse in sac
            for (int i = ownCards.size() - 1; i >= 0; i--) {
                if (ownCards.get(i).getId() == mostCommonAssetId
                        && nr < Constants.getInstance().getMaximumBagSize()) {
                    ownCards.remove(i);
                    nr++;
                }
            }
        }
    }

    /**
     * Inspectarea din perspectiva BASIC.
     *
     * @param players   lista de jucatori
     * @param freeGoods gramada de carti libere
     */
    @Override
    public void inspection(final List<Player> players,
                           final List<Integer> freeGoods) {
        int initCoins = coins;
        for (Player player : players) {
            if (this != player
                    && initCoins >= Constants.getInstance().getInspectionMinimumRequirement()) {
                // intoarcerea mitei in mana comerciantului
                player.setCoins(player.getCoins() + player.getBag().getBribe());
                player.getBag().setBribe(0);
                // verificarea sacilor
                if (Utilities.getInstance().searchIllegalItems(
                        player.getBag().getAssets(), player.getBag())) {
                    // confiscarea unui sac ilegal
                    Utilities.getInstance().confiscateBag(this, player, freeGoods);
                } else {
                    // cazul in care a cercetat un sac in regula
                    Utilities.getInstance().payPenalty(this, player);
                }
            } else if (this != player) {
                Utilities.getInstance().acceptBag(player);
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
