package com.tema1.main;

import com.tema1.goods.Goods;
import com.tema1.goods.GoodsType;
import com.tema1.goods.IllegalGoods;
import com.tema1.goods.LegalGoods;
import com.tema1.player.Player;

import java.util.*;

public final class Utilities {

    private static Utilities instance = null;
    private int nrRounds = 0;

    public static Utilities getInstance() {
        if (instance == null) {
            instance = new Utilities();
        }
        return instance;
    }

    public int getNrRounds() {
        return nrRounds;
    }

    public void setNrRounds(final int nrRounds) {
        this.nrRounds = nrRounds;
    }

    public void writeEndGameResults(final List<Player> players) {
        players.sort((Player p1, Player p2) ->
                p2.getFinalScore() - p1.getFinalScore());
//        players.sort(Comparator.comparing(Player::getFinalScore).thenComparing(Player::getInitialOrderNr));
//        Collections.reverse(players);
        StringBuilder sb = new StringBuilder();
        for (Player player : players) {
            sb.append(player.getInitialOrderNr());
            sb.append(" ");
            sb.append(player.getType());
            sb.append(" ");
            sb.append(player.getFinalScore());
            sb.append("\n");
        }
        System.out.println(sb.toString());
    }

    public void computeFinalScore(final List<Player> players) {
        for (Player player : players) {
            int score = 0;
            score += player.getCoins();
            for (Goods good : player.getEndGameGoods()) {
                score += good.getProfit();
                if (good.getType() == GoodsType.Illegal) {
                    for (Map.Entry<Goods, Integer> entry :
                            ((IllegalGoods) good).getIllegalBonus().entrySet()) {
                        score += entry.getKey().getProfit() * entry.getValue();
                    }
                }
            }
//            System.out.println(score);
            player.setFinalScore(score);
        }
    }

    public void addKQFinalBonus(final List<Player> players) {
        int[] frequency;
        int[] illGoodsChecked;
//        int kqbonus = 0;
//        players.sort((Player p1, Player p2) ->
//                p2.getFinalScore() - p1.getFinalScore());
        for (int i = 0; i < Main.constants.getNrLegalItems(); i++) {
            frequency = new int[players.size()];
            for (Player player : players) {
                illGoodsChecked = new int[Main.constants.getNrIllegalItems()];
                for (Goods good : player.getEndGameGoods()) {
                    if (good.getId() == i) {
                        frequency[player.getInitialOrderNr()]++;
                    }
                    if (good.getType() == GoodsType.Illegal) {
//                            && illGoodsChecked[good.getId() % 20] == 0) {
                        illGoodsChecked[good.getId() % 20] = 1;
                        for (Map.Entry<Goods, Integer> entry :
                                ((IllegalGoods) good).getIllegalBonus().entrySet()) {
                            if (entry.getKey().getId() == i) {
                                frequency[player.getInitialOrderNr()] += entry.getValue();
                            }
                        }
                    }
                }
            }
            int max = 0;
            int maxIndex = -1;
            for (int j = 0; j < frequency.length; j++) {
                if (frequency[j] > max) {
                    maxIndex = j;
                    max = frequency[j];
                }
            }
            if (maxIndex != -1) {
//                System.out.println("KING bonus pt itemul " + i + " la playerul " + maxIndex);
//                kqbonus += ((LegalGoods) Main.goodsFactory.getGoodsById(i)).getKingBonus();
                players.get(maxIndex).setFinalScore(players.get(maxIndex).getFinalScore()
                        + ((LegalGoods) Main.goodsFactory.getGoodsById(i)).getKingBonus());
//                players.sort((Player p1, Player p2) ->
//                        p2.getFinalScore() - p1.getFinalScore());
                boolean equalGoodsNr = false;
                int otherIndex = -1;
                for (int j = 0; j < frequency.length; j++) {
//                    System.out.print(frequency[j] + " ");
//                for (int j = frequency.length - 1; j >= 0; j--) {
                    if (frequency[j] == max && j != maxIndex) {
                        equalGoodsNr = true;
                        otherIndex = j;
                        break;
                    }
                }
//                System.out.println();
                if (equalGoodsNr) {
//                    System.out.println("aici clar nu");
//                    System.out.println("se ajunge aici pt itemul " + i);
//                    System.out.println("QUEEN bonus pt itemul " + i + " la playerul " + otherIndex);
                    players.get(otherIndex).setFinalScore(players.get(otherIndex).getFinalScore()
                            + ((LegalGoods) Main.goodsFactory.getGoodsById(i)).getQueenBonus());
                    continue;
                }
                frequency[maxIndex] = 0;
                otherIndex = maxIndex;
                max = 0;
                maxIndex = -1;
                for (int j = 0; j < frequency.length; j++) {
//                for (int j = frequency.length - 1; j >= 0; j--) {
                    if (frequency[j] > max) {
//                            && otherIndex != j) {
                        maxIndex = j;
                        max = frequency[j];
//                        break;
                    }
                }
                if (maxIndex != -1) {
//                    System.out.println("aici clar nu");
//                    System.out.println("QUEEN bonus pt itemul " + i + " la playerul " + maxIndex);
                    players.get(maxIndex).setFinalScore(players.get(maxIndex).getFinalScore()
                            + ((LegalGoods) Main.goodsFactory.getGoodsById(i)).getQueenBonus());
                }
            }
        }
//        System.out.println(kqbonus);
    }

    public int getRoundNr() {
        return this.nrRounds;
    }

    public void confiscateBag(Player sheriff, Player merchant, List<Integer> freeGoods) {
        int penalty = 0;
        int counterPenalty = 0;
        for (Goods good : merchant.getBag().getAssets()) {
            if (good.getId() != merchant.getBag().getDominantAsset()
                    || good.getType() == GoodsType.Illegal) {
                penalty += good.getPenalty();
            }
            if (good.getId() == merchant.getBag().getDominantAsset()
                    && good.getType() != GoodsType.Illegal) {
                counterPenalty += good.getPenalty();
            }
        }
//        penalty -= counterPenalty;
//        System.out.println(penalty);
        // platirea amenzii catre serif
        merchant.setCoins(merchant.getCoins() - penalty);
        sheriff.setCoins(sheriff.getCoins() + penalty);
        // mutarea bunurilor confiscate la gramada de carti
        for (Goods good : merchant.getBag().getAssets()) {
            if (good.getId() != merchant.getBag().getDominantAsset()
                    || good.getType() == GoodsType.Illegal) {
                freeGoods.add(good.getId());
            }
            if (good.getId() == merchant.getBag().getDominantAsset()
                    && good.getType() == GoodsType.Legal) {
                merchant.getEndGameGoods().add(good);
            }
        }
        merchant.getBag().getAssets().clear();
    }

    public void payPenalty(Player sheriff, Player merchant) {
        int initialCoins = sheriff.getCoins();
        int penalty = 0;
        int counterPenalty = 0;
//        System.out.println(sheriff.getType() + " " + sheriff.getInitialOrderNr() + " il verifica pe " +
//                merchant.getType() + " " + merchant.getInitialOrderNr());
        for (Goods good : merchant.getBag().getAssets()) {
//            System.out.print(good.getId() + ",");
            if (good.getId() != merchant.getBag().getDominantAsset()
                    || good.getType() == GoodsType.Illegal) {
//                penalty += good.getPenalty();
                counterPenalty += good.getPenalty();
            }
            if (good.getId() == merchant.getBag().getDominantAsset()
                    && good.getType() != GoodsType.Illegal) {
//                System.out.println("aici se ajunge");
//                counterPenalty += good.getPenalty();
                penalty += good.getPenalty();

            }
        }
//        System.out.println();
//        penalty -= counterPenalty;
        merchant.getEndGameGoods().addAll(merchant.getBag().getAssets());
        merchant.getBag().getAssets().clear();
        sheriff.setCoins(initialCoins - penalty);
        merchant.setCoins(merchant.getCoins() + penalty);
//        System.out.println(merchant.getCoins());
//        System.out.println(penalty);
    }

    public void acceptBribe(Player sheriff, Player merchant) {
        sheriff.setCoins(sheriff.getCoins() + merchant.getBag().getBribe());
        merchant.getEndGameGoods().addAll(merchant.getBag().getAssets());
        merchant.getBag().getAssets().clear();
        merchant.getBag().setBribe(0);
    }

    public int findMostProfitableIllegalAsset(List<Goods> goods) {
        List<Goods> goodsCopy = new ArrayList<>(goods);
        goodsCopy.sort((Goods g1, Goods g2) -> g2.getProfit() - g1.getProfit());
        if (goodsCopy.get(0).getType() == GoodsType.Illegal) {
            return goodsCopy.get(0).getId();
        }
        return -1;
    }

    public int findMostCommonLegalAsset(List<Goods> goods) {
        boolean hasLegalAssets = false;
        for (Goods good : goods) {
            if (good.getType() == GoodsType.Legal)
                hasLegalAssets = true;
        }
        if (!hasLegalAssets) {
//            goods.sort((Goods g1, Goods g2) -> g2.getProfit() - g1.getProfit());
            List<Goods> goodsCopy = new ArrayList<>(goods);
//            goodsCopy.sort((Goods g1, Goods g2) -> g2.getProfit() - g1.getProfit());
            goodsCopy.sort(Comparator.comparing(Goods::getProfit).thenComparing(Goods::getId));
            Collections.reverse(goodsCopy);
            return goodsCopy.get(0).getId();
        } else {
            int[] countArray = new int[10];
            for (Goods good : goods) {
                if (good.getType() == GoodsType.Legal) {
                    countArray[good.getId()]++;
                }
            }
            int max = 0;
            int id = -1;
            for (int i = 0; i < countArray.length; i++) {
                if (countArray[i] >= max && countArray[i] != 0) {
                    if (countArray[i] > max) {
                        id = i;
                        max = countArray[i];
                        continue;
                    }
                    if (id == -1) {
                        id = i;
                        max = countArray[i];
                    } else if (Main.goodsFactory.getGoodsById(i).getProfit() >
                            Main.goodsFactory.getGoodsById(id).getProfit()) {
                        id = i;
                        max = countArray[i];
                    }
                    if (countArray[i] == max
                            && Main.goodsFactory.getGoodsById(i).getProfit() ==
                            Main.goodsFactory.getGoodsById(id).getProfit()
                            && i > id) {
                        id = i;
                        max = countArray[i];
                    }
                }
            }
            return id;
        }
    }

    public void acceptBag(Player sheriff, Player merchant) {
        merchant.setCoins(merchant.getCoins() + merchant.getBag().getBribe());
        merchant.getBag().setBribe(0);
        merchant.getEndGameGoods().addAll(merchant.getBag().getAssets());
        merchant.getBag().getAssets().clear();
    }

    public List<Goods> getCardsIntoHand(List<Goods> hand, List<Integer> cards) {
        if (hand.size() != 0) {
            hand = new ArrayList<>();
        }
        int count = 0;
        while (count < 10 && !cards.isEmpty()) {
            hand.add(Main.goodsFactory.getGoodsById(cards.get(0)));
            cards.remove(0);
            count++;
        }
        return hand;
    }

    public boolean searchIllegalItems(List<Goods> goods) {
        if (goods == null || goods.isEmpty()) {
            return false;
        }
        for (Goods good : goods) {
            if (good.getType() == GoodsType.Illegal) {
                return true;
            }
        }
        return false;
    }

    public boolean searchIllegalItems(List<Goods> goods, Bag bag) {
        if (goods == null || goods.isEmpty()) {
            return false;
        }
        for (Goods good : goods) {
            if (good.getType() == GoodsType.Illegal
                    || good.getId() != bag.getDominantAsset()) {
                return true;
            }
        }
        return false;
    }
}
