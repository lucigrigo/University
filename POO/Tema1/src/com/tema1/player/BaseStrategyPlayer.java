package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.main.Bag;
import com.tema1.main.Main;

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
            ownBag.setDominantAsset(mostCommonAssetId);
            for (int i = 0; i < ownCards.size(); i++) {
                if (ownCards.get(i).getId() == mostCommonAssetId) {
                    ownBag.getAssets().add(ownCards.get(i));
                }
            }
            ownCards.removeIf((Goods g) -> g.getId() == mostCommonAssetId);
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
                    && initCoins >= 16) {
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
