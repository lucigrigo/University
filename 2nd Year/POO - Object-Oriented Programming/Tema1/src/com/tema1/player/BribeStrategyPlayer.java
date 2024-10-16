package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.goods.GoodsType;
import com.tema1.main.Bag;
import com.tema1.main.Constants;
import com.tema1.main.Utilities;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * Implementeaza strategia de joc BRIBE.
 */
public class BribeStrategyPlayer implements Player {
    private int initialOrderNr;
    private int finalScore;
    private int coins;
    private Bag ownBag;
    private List<Goods> endGameGoods;
    private List<Goods> ownCards;

    public BribeStrategyPlayer(final int orderNr) {
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
     * @return taraba cu bunuri
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
     * @return numarul de ordine initial
     */
    public int getInitialOrderNr() {
        return initialOrderNr;
    }

    /**
     * @return banii din mana
     */
    public int getCoins() {
        return coins;
    }

    /**
     * @param nr banii din mana
     */
    @Override
    public void setCoins(final int nr) {
        this.coins = nr;
    }

    /**
     * @return sacul curent
     */
    @Override
    public Bag getBag() {
        return ownBag;
    }

    /**
     * @return tipul jucatorului
     */
    @Override
    public String getType() {
        return "BRIBED";
    }

    /**
     * Crearea sacului din perspectiva BRIBED.
     */
    @Override
    public void bagCreation() {
        ownBag = new Bag();
        if (coins <= Constants.getInstance().getMinimumBribe()
                || !Utilities.getInstance().searchIllegalItems(ownCards)) {
            ownBag = new Bag();
            ownBag.setBribe(0);
            int mostCommonAssetId = Utilities.getInstance().findMostCommonLegalAsset(ownCards);
            if (mostCommonAssetId >= Constants.getInstance().getSmallestIllegalId()) {
                // cazul cand joaca strategia de baza doar cu carti ilegale
                if (coins >= Constants.getInstance().getIllegalGoodPenalty()) {
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
                // aplicarea strategiei de baza cand sunt bunuri legale in sac
                ownBag.setDominantAsset(mostCommonAssetId);
                for (int i = 0; i < ownCards.size()
                        && ownBag.getAssets().size()
                        < Constants.getInstance().getMaximumBagSize(); i++) {
                    if (ownCards.get(i).getId() == mostCommonAssetId) {
                        ownBag.getAssets().add(ownCards.get(i));
                    }
                }
                int nr = 0;
                // scoaterea din sac a bunurilor puse in sac
                for (int i = ownCards.size() - 1; i >= 0; i--) {
                    if (ownCards.get(i).getId() == mostCommonAssetId
                            && nr < Constants.getInstance().getMaximumBagSize()) {
                        ownCards.remove(i);
                        nr++;
                    }
                }
            }
        } else {
            // aplicarea strategiei "BRIBE"
            int nrIllegalGoods = 0;
            int possiblePenalty = 0;
            // declararea sacului ca fiind doar cu mere
            ownBag.setDominantAsset(0);
            List<Goods> ownCardsCopy = new ArrayList<>(ownCards);
            ownCardsCopy.sort(Comparator.comparing(Goods::getProfit).thenComparing(Goods::getId));
            Collections.reverse(ownCardsCopy);
            // punerea in sac a cator mai multe bunuri ilegale
            while (!ownCardsCopy.isEmpty()
                    && ownCardsCopy.get(0).getType() == GoodsType.Illegal
                    && ownBag.getAssets().size() < Constants.getInstance().getMaximumBagSize()) {
                possiblePenalty += ownCardsCopy.get(0).getPenalty();
                if (possiblePenalty >= coins) {
                    possiblePenalty -= ownCardsCopy.get(0).getPenalty();
                    break;
                }
                ownBag.getAssets().add(ownCardsCopy.get(0));
                ownCardsCopy.remove(0);
                nrIllegalGoods++;
            }
            // completarea sacului cu bunuri legale
            for (int i = 0; i < ownCardsCopy.size()
                    && ownBag.getAssets().size()
                    < Constants.getInstance().getMaximumBagSize(); i++) {
                if (ownCardsCopy.get(i).getType() == GoodsType.Legal) {
                    possiblePenalty += ownCardsCopy.get(i).getPenalty();
                    if (possiblePenalty >= coins) {
                        break;
                    }
                    ownBag.getAssets().add(ownCardsCopy.get(i));
                }
            }
            // stabilirea mitei puse in sac in functie de numarul
            // de bunuri ilegale
            if (nrIllegalGoods <= 2) {
                ownBag.setBribe(Constants.getInstance().getMinimumBribe());
                coins -= Constants.getInstance().getMinimumBribe();
            } else {
                ownBag.setBribe(Constants.getInstance().getMaximumBribe());
                coins -= Constants.getInstance().getMaximumBribe();
            }
        }

    }

    /**
     * Inspectarea jucatorilor din perspectiva BRIBED.
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
                if (Math.abs(player.getInitialOrderNr() - initialOrderNr) == 1
                        || (initialOrderNr == 0
                        && player.getInitialOrderNr() == (players.size() - 1))
                        || (initialOrderNr == (players.size() - 1)
                        && player.getInitialOrderNr() == 0)) {
                    if (initCoins >= Constants.getInstance().getInspectionMinimumRequirement()) {
                        // intoarcerea mitei in mana comerciantului
                        player.setCoins(player.getCoins() + player.getBag().getBribe());
                        player.getBag().setBribe(0);
                        // cautarea unei neregularitati in sacul celui inspectat
                        if (Utilities.getInstance().searchIllegalItems(
                                player.getBag().getAssets(), player.getBag())) {
                            // confiscarea sacului
                            Utilities.getInstance().confiscateBag(this, player, freeGoods);
                        } else {
                            // platirea penalty-ul in cazul unui sac regulamentar
                            Utilities.getInstance().payPenalty(this, player);
                        }

                    } else {
                        // acceptarea sacului, dar nu si a mitei, cand seriful nu are destui
                        // bani ca sa inspecteze
                        Utilities.getInstance().acceptBag(player);
                    }
                } else {
                    // acceptarea mitei de la jucatorii care nu sunt vecinii serifului
                    Utilities.getInstance().acceptBribe(this, player);

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
