package com.tema1.player;

import com.tema1.goods.Goods;
import com.tema1.goods.GoodsType;
import com.tema1.main.Bag;
import com.tema1.main.Main;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class BribeStrategyPlayer implements Player {
    private static final Strategy strategy = Strategy.BRIBE;
    private int initialOrderNr;
    private int finalScore;
    private int coins;
    private Bag ownBag;
    private List<Goods> endGameGoods;
    private List<Goods> ownCards;
    public boolean canBeInspector = true;

    public BribeStrategyPlayer(int orderNr) {
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
        return "BRIBED";
    }

    @Override
    public void bagCreation() {
        ownBag = new Bag();
        if (coins < 10 ||
                !Main.utilities.searchIllegalItems(ownCards)) {
            ownBag.setBribe(0);
//            if (coins < 2) {
//            System.out.println("aici>? " + coins);
            List<Goods> cardsCopy = new ArrayList<>(ownCards);
            int mostCommonAssetId = Main.utilities.findMostCommonLegalAsset(cardsCopy);
//            int potentialPenalty = 0;
            for (int i = 0; i < cardsCopy.size(); i++) {
                if (cardsCopy.get(i).getId() == mostCommonAssetId) {
//                    potentialPenalty += cardsCopy.get(i).getPenalty();
//                    if (potentialPenalty >= coins) {
//                        break;
//                    }
                    ownBag.getAssets().add(cardsCopy.get(i));
                    // TODO 2r3pm20 WTF?
                    if (cardsCopy.get(i).getType() == GoodsType.Illegal) {
                        break;
                    }
//                    System.out.println(cardsCopy.get(i).getId());
//                    cardsCopy.remove(i);
                }
            }
//            ownBag.getAssets().add(ownCards.get((Goods g) -> g.getId() == mostCommonAssetId));
//            if (mostCommonAssetId < 20) {
//                ownBag.setDominantAsset(mostCommonAssetId);
//            } else {
            ownCards.removeIf((Goods g) -> g.getId() == mostCommonAssetId);
            ownBag.setDominantAsset(mostCommonAssetId >= 20 ? 0 : mostCommonAssetId);
//            }
//            }
        } else {
            int nrIllegalGoods = 0;
            int possiblePenalty = 0;
            ownBag.setDominantAsset(0);
            List<Goods> ownCardsCopy = new ArrayList<>(ownCards);
//            ownCardsCopy.sort((Goods g1, Goods g2) -> g2.getProfit() - g1.getProfit());
            ownCardsCopy.sort(Comparator.comparing(Goods::getProfit).thenComparing(Goods::getId));
            Collections.reverse(ownCardsCopy);
//            possiblePenalty += ownCardsCopy.get(0).getPenalty();
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
                    possiblePenalty += ownCardsCopy.get(i).getPenalty();
//                System.out.println(possiblePenalty);
                    if (possiblePenalty >= coins) {
                        break;
                    }
                    ownBag.getAssets().add(ownCardsCopy.get(i));
//                System.out.println("se adauga" + ownCardsCopy.get(0).getId());
//                    ownCardsCopy.remove(i);
                }
            }

            if (nrIllegalGoods <= 2) {
                ownBag.setBribe(5);
                coins -= 5;
//                    System.out.println("si aicea");
            } else {
                ownBag.setBribe(10);
                coins -= 10;
<<<<<<< HEAD
            }
//            possiblePenalty -=
            ownBag.setDominantAsset(0);
            while (!ownCardsCopy.isEmpty() &&
                    ownBag.getAssets().size() < 8
                    && possiblePenalty < coins - 2) {
                possiblePenalty += ownCardsCopy.get(0).getPenalty();
                ownBag.getAssets().add(ownCardsCopy.get(0));
                ownCardsCopy.remove(0);
=======
//                    System.out.println("aici de cate ori?");
>>>>>>> df91f3181055b19c86a79eaa0fcab5c280f7f1db
            }
        }
    }

    @Override
    public void inspection(List<Player> players, List<Integer> freeGoods) {
        for (Player player : players) {
            if (player != this
                    && canBeInspector) {
                if (Math.abs(player.getInitialOrderNr() - initialOrderNr) == 1
                        || (initialOrderNr == 0 && player.getInitialOrderNr() == (players.size() - 1))
                        || (initialOrderNr == (players.size() - 1) && player.getInitialOrderNr() == 0)) {
                    if (this.coins >= 16) {
                        if (canBeInspector) {
                            // intoarcerea mitei in mana comerciantului
                            player.setCoins(player.getCoins() + player.getBag().getBribe());
                            player.getBag().setBribe(0);
                            if (Main.utilities.searchIllegalItems(player.getBag().getAssets(), player.getBag())) {
                                Main.utilities.confiscateBag(this, player, freeGoods);
                            } else {
                                Main.utilities.payPenalty(this, player);
                            }
                        }
                    } else {
//                        System.out.println("jucatorul " + this.getType() + " " + this.getInitialOrderNr()
//                                + " nu mai are bani de inspectat pe " + player.getType() + " " + player.getInitialOrderNr());
//                        Main.utilities.acceptBribe(this, player);
                        Main.utilities.acceptBag(this, player);
//                        canBeInspector = false;
                    }
                } else {
//                    System.out.println("se si accepta mita?");
                    Main.utilities.acceptBribe(this, player);
//                    Main.utilities.acceptBribe(this, player);

                }
            }
        }
    }

    @Override
    public void handRefill(List<Integer> freeGoods) {
        ownCards = Main.utilities.getCardsIntoHand(ownCards, freeGoods);
    }
}
