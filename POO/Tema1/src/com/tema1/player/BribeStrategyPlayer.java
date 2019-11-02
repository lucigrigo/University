package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.goods.GoodsType;
import com.tema1.main.Bag;
import com.tema1.main.Main;

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
        if (coins <= 5
                || !Main.utilities.searchIllegalItems(ownCards)) {
            ownBag = new Bag();
            ownBag.setBribe(0);
            int mostCommonAssetId = Main.utilities.findMostCommonLegalAsset(ownCards);
            if (mostCommonAssetId >= 20) {
                if (coins >= 4) {
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
                for (int i = 0; i < ownCards.size() && ownBag.getAssets().size() < 8; i++) {
                    if (ownCards.get(i).getId() == mostCommonAssetId) {
                        ownBag.getAssets().add(ownCards.get(i));
                    }
                }
                ownCards.removeIf((Goods g) -> g.getId() == mostCommonAssetId);
            }
//            ownBag.setBribe(0);
////            System.out.println("aici>? " + coins);
//            List<Goods> cardsCopy = new ArrayList<>(ownCards);
//            cardsCopy.sort(Comparator.comparing(Goods::getProfit).thenComparing(Goods::getId));
////            cardsCopy.sort((Goods g1, Goods g2) -> g2.getProfit() - g1.getProfit());
//            Collections.reverse(cardsCopy);
////            if (coins == 5
////                    && cardsCopy.get(0).getType() == GoodsType.Illegal) {
////                ownBag.setBribe(5);
////                coins -= 5;
////                ownBag.getAssets().add(cardsCopy.get(0));
////                for (int i = 0; i < ownCards.size(); i++) {
////                    if (ownCards.get(i).getId() == ownBag.getAssets().get(0).getId()) {
////                        ownCards.remove(i);
////                        break;
////                    }
////                }
////            }
////            else {
//            int mostCommonAssetId = Main.utilities.findMostCommonLegalAsset(cardsCopy);
//            int potentialPenalty = 0;
//            if (mostCommonAssetId < 20) {
//                for (int i = 0; i < cardsCopy.size(); i++) {
//                    if (cardsCopy.get(i).getId() == mostCommonAssetId) {
//                        potentialPenalty += cardsCopy.get(i).getPenalty();
//                        if (potentialPenalty > coins
//                                && cardsCopy.get(i).getType() == GoodsType.Illegal) {
//                            break;
//                        }
//                        ownBag.getAssets().add(cardsCopy.get(i));
////                    if (cardsCopy.get(i).getType() == GoodsType.Illegal) {
//////                            if (coins == 5) {
//////                                ownBag.setBribe(5);
//////                                coins -= 5;
//////                            }
////////                        } else {
////////                            ownBag.getAssets().clear();
////////                        }
//////                            break;
////                    }
////                    System.out.println(cardsCopy.get(i).getId());
////                    cardsCopy.remove(i);
//                    }
//                }
//                ownCards.removeIf((Goods g) -> g.getId() == mostCommonAssetId);
//                ownBag.setDominantAsset(mostCommonAssetId >= 20 ? 0 : mostCommonAssetId);
//            }
//
////                if (!ownBag.getAssets().isEmpty()
////                        && ownBag.getAssets().get(0).getType() == GoodsType.Illegal
////                        && coins == 5) {
////                    coins -= 5;
////                    ownBag.setBribe(0);
////                }
////            ownBag.getAssets().add(ownCards.get((Goods g) -> g.getId() == mostCommonAssetId));
////            if (mostCommonAssetId < 20) {
////                ownBag.setDominantAsset(mostCommonAssetId);
////            } else {
//
////            }
        } else {
            int nrIllegalGoods = 0;
            int possiblePenalty = 0;
            ownBag.setDominantAsset(0);
            List<Goods> ownCardsCopy = new ArrayList<>(ownCards);
//            ownCardsCopy.sort((Goods g1, Goods g2) -> g2.getProfit() - g1.getProfit());
            ownCardsCopy.sort(Comparator.comparing(Goods::getProfit).thenComparing(Goods::getId));
            Collections.reverse(ownCardsCopy);
            while (!ownCardsCopy.isEmpty()
                    && ownCardsCopy.get(0).getType() == GoodsType.Illegal
                    && ownBag.getAssets().size() < 8) {
                possiblePenalty += ownCardsCopy.get(0).getPenalty();
                if (possiblePenalty >= coins) {
                    possiblePenalty -= ownCardsCopy.get(0).getPenalty();
                    break;
                }
//                System.out.println("se adauga" + ownCardsCopy.get(0).getId());
                ownBag.getAssets().add(ownCardsCopy.get(0));
                ownCardsCopy.remove(0);
                nrIllegalGoods++;
            }
//            if (possiblePenalty >= coins) {
//            }
//            ownBag.setDominantAsset(0);
//            while (!ownCardsCopy.isEmpty() &&
//                    ownBag.getAssets().size() < 8) {
//                    && possiblePenalty < coins - 2) {
//                System.out.println(possiblePenalty);
            for (int i = 0; i < ownCardsCopy.size() && ownBag.getAssets().size() < 8; i++) {
                if (ownCardsCopy.get(i).getType() == GoodsType.Legal) {
//                    ownBag.setDominantAsset(ownCardsCopy.get(i).getId());
//                    if (ownCardsCopy.get(i).getId() != 0) {
                    possiblePenalty += ownCardsCopy.get(i).getPenalty();
//                    }
//                System.out.println(possiblePenalty);
                    if (possiblePenalty >= coins) {
                        break;
                    }
                    ownBag.getAssets().add(ownCardsCopy.get(i));
//                System.out.println("se adauga" + ownCardsCopy.get(0).getId());
//                    ownCardsCopy.remove(i);

                }
            }

//            int i = 0;
//            while (i < ownCardsCopy.size()
//                    && ownBag.getAssets().size() < 8) {
//                if (ownCardsCopy.get(i).getId() == 0) {
//                    ownBag.getAssets().add(ownCardsCopy.get(i));
//                }
//                i++;
//            }

            if (nrIllegalGoods <= 2) {
                ownBag.setBribe(5);
                coins -= 5;
//                    System.out.println("si aicea");
            } else {
                ownBag.setBribe(10);
                coins -= 10;
//                    System.out.println("aici de cate ori?");
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
    public void inspection(final List<Player> players, final List<Integer> freeGoods) {
        int initCoins = coins;
        for (Player player : players) {
            if (player != this) {
                if (Math.abs(player.getInitialOrderNr() - initialOrderNr) == 1
                        || (initialOrderNr == 0 && player.getInitialOrderNr() == (players.size() - 1))
                        || (initialOrderNr == (players.size() - 1) && player.getInitialOrderNr() == 0)) {
                    if (initCoins >= 16) {
                        // intoarcerea mitei in mana comerciantului
                        player.setCoins(player.getCoins() + player.getBag().getBribe());
                        player.getBag().setBribe(0);
                        if (Main.utilities.searchIllegalItems(player.getBag().getAssets(), player.getBag())) {
//                                System.out.println("se confisca bunurile");
                            Main.utilities.confiscateBag(this, player, freeGoods);
                        } else {
//                                System.out.println("plateste penalty seriful");
                            Main.utilities.payPenalty(this, player);
                        }

                    } else {
//                        System.out.println("jucatorul " + this.getType() + " " + this.getInitialOrderNr()
//                                + " nu mai are bani de inspectat pe " + player.getType() + " " + player.getInitialOrderNr());
//                        Main.utilities.acceptBribe(this, player);
//                        System.out.println("nu mai are bani de inspectat seriful");
                        Main.utilities.acceptBag(this, player);
                    }
                } else {
//                    if (this.coins >= 16) {
//                        Main.utilities.acceptBribe(this, player);
////
//                    } else {
//                        Main.utilities.acceptBag(this, player);

//                    }
//                    System.out.println("se si accepta mita?");
//                    System.out.println("se accepta mita si bunurile");
                    Main.utilities.acceptBribe(this, player);

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
