package com.tema1.main;

import com.tema1.goods.Goods;
import com.tema1.goods.GoodsType;
import com.tema1.goods.IllegalGoods;
import com.tema1.goods.LegalGoods;
import com.tema1.player.Player;

import java.util.*;

/**
 * O clasa de utilitati, folosita pentru task-uri adiacente, care nu tin neaparat de un player,
 * sau precum scrierea rezultatlor finale ale jocului etc.
 */
public final class Utilities {

    private static Utilities instance = null;
    private int nrRounds = 0;

    /**
     * @return instanta clasei de Utilitati
     */
    public static Utilities getInstance() {
        if (instance == null) {
            instance = new Utilities();
        }
        return instance;
    }

    /**
     * @return numarul rundei curente de joc
     */
    public int getRoundNr() {
        return this.nrRounds;
    }

    /**
     * Seteaza numarul curent al rundei de joc.
     *
     * @param nrRounds numarul rundei
     */
    public void setNrRounds(final int nrRounds) {
        this.nrRounds = nrRounds;
    }

    /**
     * Functia care realizeaza scrierea rezultatelor finale ale jocului.
     *
     * @param players lista cu jucatorii
     */
    public void writeEndGameResults(final List<Player> players) {
        players.sort((Player p1, Player p2) -> p2.getFinalScore() - p1.getFinalScore());
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

    /**
     * Functia care calculeaza scorul final al fiecarui jucator, fara king si queen bonus.
     *
     * @param players lista cu jucatorii
     */
    public void computeFinalScore(final List<Player> players) {
        for (Player player : players) {
            int score = 0;
            score += player.getCoins();
            for (Goods good : player.getEndGameGoods()) {
                score += good.getProfit();
                if (good.getType() == GoodsType.Illegal) {
                    for (Map.Entry<Goods, Integer> entry
                            : ((IllegalGoods) good).getIllegalBonus().entrySet()) {
                        score += entry.getKey().getProfit() * entry.getValue();
                    }
                }
            }
//            System.out.println(score);
            player.setFinalScore(score);
        }
    }

    /**
     * Functia care adauga la scorul final bonus-urile de king si queen.
     *
     * @param players lista cu jucatori
     */
    public void addKQFinalBonus(final List<Player> players) {
        int[] frequency;
//        int[] illGoodsChecked;
//        int kqbonus = 0;
//        players.sort((Player p1, Player p2) ->
//                p2.getFinalScore() - p1.getFinalScore());
        for (int i = 0; i < Main.constants.getNrLegalItems(); i++) {
            frequency = new int[players.size()];
            for (Player player : players) {
//                illGoodsChecked = new int[Main.constants.getNrIllegalItems()];
                for (Goods good : player.getEndGameGoods()) {
                    if (good.getId() == i) {
                        frequency[player.getInitialOrderNr()]++;
                    }
                    if (good.getType() == GoodsType.Illegal) {
//                            && illGoodsChecked[good.getId() % 20] == 0) {
//                        illGoodsChecked[good.getId() % 20] = 1;
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

    /**
     * Functia care se ocupa de confiscarea unui sac ilegal.
     *
     * @param sheriff   seriful la momentul apelului
     * @param merchant  comerciantului la momentul apelului
     * @param freeGoods lista cu cartile nefolosite de vreun jucator
     */
    public void confiscateBag(final Player sheriff,
                              final Player merchant,
                              final List<Integer> freeGoods) {
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

    /**
     * Functia care se ocupa de platirea unu penalty in cazul verificarii unui comerciant sincer.
     *
     * @param sheriff  seriful la momentul apelului
     * @param merchant comerciantului la momentul apelului
     */
    public void payPenalty(final Player sheriff,
                           final Player merchant) {
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

    /**
     * Functia care se ocupa cu acceptarea mitei de la un comerciant, de catre seriful
     * de la momentul respectiv.
     *
     * @param sheriff  seriful de la momentul respectiv
     * @param merchant comerciantul de la momentul respectiv
     */
    public void acceptBribe(final Player sheriff,
                            final Player merchant) {
        sheriff.setCoins(sheriff.getCoins() + merchant.getBag().getBribe());
        merchant.getEndGameGoods().addAll(merchant.getBag().getAssets());
        merchant.getBag().getAssets().clear();
        merchant.getBag().setBribe(0);
    }

    /**
     * Functia care gaseste cel mai profitabil bun ilegal.
     *
     * @param goods lista de bunuri
     * @return id-ul bunului ilegal cel mai profitabil; -1, daca nu gaseste niciunul
     */
    public int findMostProfitableIllegalAsset(final List<Goods> goods) {
        List<Goods> goodsCopy = new ArrayList<>(goods);
        goodsCopy.sort((Goods g1, Goods g2) -> g2.getProfit() - g1.getProfit());
        if (goodsCopy.get(0).getType() == GoodsType.Illegal) {
            return goodsCopy.get(0).getId();
        }
        return -1;
    }

    /**
     * Functia care gaseste cel mai comun bun ilegal; intoarce id-ul celui mai profitabil
     * bun ilegal, daca sunt doar bunuri ilegale
     *
     * @param goods lista de bunuri
     * @return id-ul unui bun
     */
    public int findMostCommonLegalAsset(final List<Goods> goods) {
        boolean hasLegalAssets = false;
        for (Goods good : goods) {
            if (good.getType() == GoodsType.Legal) {
                hasLegalAssets = true;
            }
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
                    } else if (Main.goodsFactory.getGoodsById(i).getProfit()
                            > Main.goodsFactory.getGoodsById(id).getProfit()) {
                        id = i;
                        max = countArray[i];
                    }
                    if (countArray[i] == max
                            && Main.goodsFactory.getGoodsById(i).getProfit()
                            == Main.goodsFactory.getGoodsById(id).getProfit()
                            && i > id) {
                        id = i;
                        max = countArray[i];
                    }
                }
            }
            return id;
        }
    }

    /**
     * Functia care se ocupa de acceptarea sacului unui comerciant, dar nu si a mitei.
     * Este folosita atunci cand un inspector nu mai are bani sa inspecteze pe cine trebuie.
     *
     * @param sheriff  seriful la momentul respectiv
     * @param merchant comerciantul la momentul respectiv
     */
    public void acceptBag(Player sheriff,
                          final Player merchant) {
//        for(Goods good : merchant.getBag().getAssets()) {
//            merchant.getEndGameGoods().add(good);
//        }
        merchant.setCoins(merchant.getCoins() + merchant.getBag().getBribe());
        merchant.getBag().setBribe(0);
        merchant.getEndGameGoods().addAll(merchant.getBag().getAssets());
        merchant.getBag().getAssets().clear();
    }

    /**
     * Functia care se ocupe cu re/completarea cartilor din mana unui jucator.
     *
     * @param hand  cartile din mana la momentul curent
     * @param cards gramada de carti libere
     * @return o noua lista cu noile carti
     */
    public List<Goods> getCardsIntoHand(List<Goods> hand,
                                        final List<Integer> cards) {
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

    /**
     * Functia care se ocupa cu verificarea unei liste de bunuri pentru bunuri ilegale.
     *
     * @param goods lista de bunuri
     * @return true sau false daca lista de bunuri are sau nu bunuri ilegale
     */
    public boolean searchIllegalItems(final List<Goods> goods) {
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

    /**
     * Functia care cauta intr-un sac ori un bun ilegal, ori un bun nedeclarat.
     *
     * @param goods lista de bunuri
     * @param bag   sacul
     * @return true sau false daca sacul este sau nu in regula
     */
    public boolean searchIllegalItems(final List<Goods> goods,
                                      final Bag bag) {
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
