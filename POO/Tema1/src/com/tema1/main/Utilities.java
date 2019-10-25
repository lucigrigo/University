package com.tema1.main;

import com.tema1.goods.Goods;
import com.tema1.goods.GoodsType;
import com.tema1.goods.IllegalGoods;
import com.tema1.goods.LegalGoods;
import com.tema1.player.Player;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

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

    public void setNrRounds(int nrRounds) {
        this.nrRounds = nrRounds;
    }

    public void writeEndGameResults(List<Player> players) {
        players.sort((Player p1, Player p2) ->
                p2.getFinalScore() - p1.getFinalScore());
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

    public void computeFinalScore(List<Player> players) {
        for (Player player : players) {
            int score = 0;
            score += player.getCoins();
            for (Goods good : player.getEndGameGoods()) {
                score += good.getProfit();
                if (good.getType() == GoodsType.Illegal) {
                    for (Map.Entry<Goods, Integer> entry : ((IllegalGoods) good).getIllegalBonus().entrySet()) {
                        score += entry.getKey().getProfit() * entry.getValue();
                    }
                }
            }
            player.setFinalScore(score);
        }
    }

    public void addKQFinalBonus(List<Player> players) {
        int[] frequency;
        int[] illGoodsChecked;
        for (int i = 0; i < 10; i++) {
            frequency = new int[players.size()];
            illGoodsChecked = new int[5];
            for (Player player : players) {
                for (Goods good : player.getEndGameGoods()) {
                    if (good.getId() == i) {
                        frequency[player.getInitialOrderNr()]++;
                    }
                    if (good.getType() == GoodsType.Illegal
                            && illGoodsChecked[good.getId() % 20] == 0) {
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
                players.get(maxIndex).setFinalScore(players.get(maxIndex).getFinalScore()
                        + ((LegalGoods) Main.goodsFactory.getGoodsById(i)).getKingBonus());
                boolean equalGoodsNr = false;
                int otherIndex = -1;
                for (int j = 0; j < frequency.length; j++) {
                    if (frequency[j] == max
                            && j != maxIndex) {
                        equalGoodsNr = true;
                        otherIndex = j;
                    }
                }
                if (equalGoodsNr) {
                    players.get(otherIndex).setFinalScore(players.get(otherIndex).getFinalScore()
                            + ((LegalGoods) Main.goodsFactory.getGoodsById(i)).getQueenBonus());
                    continue;
                }
                otherIndex = maxIndex;
                max = 0;
                maxIndex = -1;
                for (int j = 0; j < frequency.length; j++) {
                    if (frequency[j] > max
                            && otherIndex != j) {
                        maxIndex = j;
                        max = frequency[j];
                    }
                }
                if (maxIndex != -1) {
                    players.get(maxIndex).setFinalScore(players.get(maxIndex).getFinalScore()
                            + ((LegalGoods) Main.goodsFactory.getGoodsById(i)).getQueenBonus());
                }
            }
        }
    }

    public int getRoundNr() {
        return this.nrRounds;
    }

    public void confiscateBag(Player sheriff, Player merchant, List<Integer> freeGoods) {
        int penalty = 0;
        for (Goods good : merchant.getBag().getAssets()) {
            if (good.getId() != merchant.getBag().getDominantAsset() ||
                    good.getType() == GoodsType.Illegal) {
                penalty += good.getPenalty();
            }
        }
        // platirea amenzii catre serif
        merchant.setCoins(merchant.getCoins() - penalty);
        sheriff.setCoins(sheriff.getCoins() + penalty);
        // mutarea bunurilor confiscate la gramada de carti
        for (Goods good : merchant.getBag().getAssets()) {
            freeGoods.add(good.getId());
        }
        merchant.getBag().getAssets().clear();
    }

    public void payPenalty(Player sheriff, Player merchant) {
        int initialCoins = sheriff.getCoins();
        int penalty = 0;
        for (Goods good : merchant.getBag().getAssets()) {
//            if (good.getId() == merchant.getBag().getDominantAsset()) {
            penalty += good.getPenalty();
//            }
        }
        merchant.getEndGameGoods().addAll(merchant.getBag().getAssets());
        merchant.getBag().getAssets().clear();
        sheriff.setCoins(initialCoins - penalty);
        merchant.setCoins(merchant.getCoins() + penalty);
//        System.out.println(merchant.getCoins());
    }

    public void acceptBribe(Player sheriff, Player merchant) {
        sheriff.setCoins(sheriff.getCoins() + merchant.getBag().getBribe());
        merchant.getEndGameGoods().addAll(merchant.getBag().getAssets());
        merchant.getBag().getAssets().clear();
    }

    // TODO de vazut daca o sa imi trebuiasca vreodata
    public int findMostProfitableIllegalAsset(List<Goods> goods) {
        int profit = 0;
        int id = -1;
        for (Goods good : goods) {
            if (good.getType() == GoodsType.Illegal &&
                    good.getProfit() >= profit) {
                profit = good.getProfit();
                id = good.getId();
            }
        }
        return id;
    }

    public int findMostCommonLegalAsset(List<Goods> goods) {
        boolean hasLegalAssets = false;
        for (Goods good : goods) {
            if (good.getType() == GoodsType.Legal)
                hasLegalAssets = true;
        }
        if (!hasLegalAssets) {
            goods.sort((Goods g1, Goods g2) -> g2.getProfit() - g1.getProfit());
            return goods.get(0).getId();
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
                }
            }
            return id;
        }
    }

    public void getCardsIntoHand(List<Goods> hand, List<Integer> cards) {
        if (hand.size() != 0) {
            hand = new ArrayList<>();
        }
        int count = 0;
        while (count < 10 && !cards.isEmpty()) {
            hand.add(Main.goodsFactory.getGoodsById(cards.get(0)));
            cards.remove(0);
            count++;
        }
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
}
