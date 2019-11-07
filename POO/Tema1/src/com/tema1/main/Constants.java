package com.tema1.main;

import java.util.HashMap;
import java.util.Map;

/**
 * O clasa care e menita sa memoreze constante folosite prin intreg codul.
 */
public final class Constants {
    private static Constants instance = null;

    public static Constants getInstance() {
        if (instance == null) {
            instance = new Constants();
        }
        return instance;
    }

    private static final int LEGAL_GOODS_NUMBER = 10;
    private static final int ILLEGAL_GOODS_NUMBER = 5;
    private static final int STANDARD_INITIAL_COINS = 80;
    private static final int SMALLEST_ILLEGAL_ID = 20;
    private static final int INSPECTION_MINMUM_REQUIREMENT = 16;
    private static final int LEGAL_GOOD_PENALTY = 2;
    private static final int ILLEGAL_GOOD_PENALTY = 4;
    private static final int MAXIMUM_BAG_SIZE = 8;
    private static final int MAXIMUM_ROUNDS_NUMBER = 5;
    private static final int MAXIMUM_BRIBE = 10;
    private static final int MINIMUM_BRIBE = 5;
    private static final int CARDS_IN_HAND_NR = 10;

    private static final int APPLE_ID = 0;
    private static final int CHEESE_ID = 1;
    private static final int BREAD_ID = 2;
    private static final int CHICKEN_ID = 3;
    private static final int TOMATO_ID = 4;
    private static final int CORN_ID = 5;
    private static final int POTATO_ID = 6;
    private static final int WINE_ID = 7;
    private static final int SALT_ID = 8;
    private static final int SUGAR_ID = 9;
    private static final int SILK_ID = 20;
    private static final int PEPPER_ID = 21;
    private static final int BARREL_ID = 22;
    private static final int BEER_ID = 23;
    private static final int SEAFOOD_ID = 24;
    private static final Map<String, Integer> GOODS_IDS = new HashMap<String, Integer>() {
        {
            put("Apple", APPLE_ID);
            put("Cheese", CHEESE_ID);
            put("Bread", BREAD_ID);
            put("Chicken", CHICKEN_ID);
            put("Tomato", TOMATO_ID);
            put("Corn", CORN_ID);
            put("Potato", POTATO_ID);
            put("Wine", WINE_ID);
            put("Salt", SALT_ID);
            put("Sugar", SUGAR_ID);
            put("Silk", SILK_ID);
            put("Pepper", PEPPER_ID);
            put("Barrel", BARREL_ID);
            put("Beer", BEER_ID);
            put("Seafood", SEAFOOD_ID);
        }
    };

    private static final int APPLE_PROFIT = 2;
    private static final int CHEESE_PROFIT = 3;
    private static final int BREAD_PROFIT = 4;
    private static final int CHICKEN_PROFIT = 4;
    private static final int TOMATO_PROFIT = 3;
    private static final int CORN_PROFIT = 2;
    private static final int POTATO_PROFIT = 3;
    private static final int WINE_PROFIT = 5;
    private static final int SALT_PROFIT = 2;
    private static final int SUGAR_PROFIT = 3;
    private static final int SILK_PROFIT = 9;
    private static final int PEPPER_PROFIT = 8;
    private static final int BARREL_PROFIT = 7;
    private static final int BEER_PROFIT = 6;
    private static final int SEAFOOD_PROFIT = 12;
    private static final Map<String, Integer> GOODS_PROFIT = new HashMap<String, Integer>() {
        {
            put("Apple", APPLE_PROFIT);
            put("Cheese", CHEESE_PROFIT);
            put("Bread", BREAD_PROFIT);
            put("Chicken", CHICKEN_PROFIT);
            put("Tomato", TOMATO_PROFIT);
            put("Corn", CORN_PROFIT);
            put("Potato", POTATO_PROFIT);
            put("Wine", WINE_PROFIT);
            put("Salt", SALT_PROFIT);
            put("Sugar", SUGAR_PROFIT);
            put("Silk", SILK_PROFIT);
            put("Pepper", PEPPER_PROFIT);
            put("Barrel", BARREL_PROFIT);
            put("Beer", BEER_PROFIT);
            put("Seafood", SEAFOOD_PROFIT);
        }
    };

    private static final int APPLE_KING_BONUS = 20;
    private static final int CHEESE_KING_BONUS = 19;
    private static final int BREAD_KING_BONUS = 18;
    private static final int CHICKEN_KING_BONUS = 17;
    private static final int TOMATO_KING_BONUS = 16;
    private static final int CORN_KING_BONUS = 15;
    private static final int POTATO_KING_BONUS = 14;
    private static final int WINE_KING_BONUS = 13;
    private static final int SALT_KING_BONUS = 12;
    private static final int SUGAR_KING_BONUS = 11;
    private static final Map<String, Integer> KING_BONUS = new HashMap<String, Integer>() {
        {
            put("Apple", APPLE_KING_BONUS);
            put("Cheese", CHEESE_KING_BONUS);
            put("Bread", BREAD_KING_BONUS);
            put("Chicken", CHICKEN_KING_BONUS);
            put("Tomato", TOMATO_KING_BONUS);
            put("Corn", CORN_KING_BONUS);
            put("Potato", POTATO_KING_BONUS);
            put("Wine", WINE_KING_BONUS);
            put("Salt", SALT_KING_BONUS);
            put("Sugar", SUGAR_KING_BONUS);
        }
    };

    private static final int APPLE_QUEEN_BONUS = 10;
    private static final int CHEESE_QUEEN_BONUS = 9;
    private static final int BREAD_QUEEN_BONUS = 9;
    private static final int CHICKEN_QUEEN_BONUS = 8;
    private static final int TOMATO_QUEEN_BONUS = 7;
    private static final int CORN_QUEEN_BONUS = 6;
    private static final int POTATO_QUEEN_BONUS = 5;
    private static final int WINE_QUEEN_BONUS = 4;
    private static final int SALT_QUEEN_BONUS = 3;
    private static final int SUGAR_QUEEN_BONUS = 2;
    private static final Map<String, Integer> QUEEN_BONUS = new HashMap<String, Integer>() {
        {
            put("Apple", APPLE_QUEEN_BONUS);
            put("Cheese", CHEESE_QUEEN_BONUS);
            put("Bread", BREAD_QUEEN_BONUS);
            put("Chicken", CHICKEN_QUEEN_BONUS);
            put("Tomato", TOMATO_QUEEN_BONUS);
            put("Corn", CORN_QUEEN_BONUS);
            put("Potato", POTATO_QUEEN_BONUS);
            put("Wine", WINE_QUEEN_BONUS);
            put("Salt", SALT_QUEEN_BONUS);
            put("Sugar", SUGAR_QUEEN_BONUS);
        }
    };

    private static final int SILK_BONUS_CHEESE_QUANTITY = 3;
    private static final int PEPPER_BONUS_CHICKEN_QUANTITY = 2;
    private static final int BARREL_BONUS_BREAD_QUANTITY = 2;
    private static final int BEER_BONUS_WINE_QUANTITY = 4;
    private static final int SEAFOOD_BONUS_TOMATO_QUANTITY = 2;
    private static final int SEAFOOD_BONUS_POTATO_QUANTITY = 3;
    private static final int SEAFOOD_BONUS_CHICKEN_QUANTITY = 1;

    public int getLegalGoodsNumber() {
        return LEGAL_GOODS_NUMBER;
    }

    public int getIllegalGoodsNumber() {
        return ILLEGAL_GOODS_NUMBER;
    }

    public int getStandardInitialCoins() {
        return STANDARD_INITIAL_COINS;
    }

    public int getSmallestIllegalId() {
        return SMALLEST_ILLEGAL_ID;
    }

    public int getInspectionMinimumRequirement() {
        return INSPECTION_MINMUM_REQUIREMENT;
    }

    public int getIllegalGoodPenalty() {
        return ILLEGAL_GOOD_PENALTY;
    }

    public int getMaximumBagSize() {
        return MAXIMUM_BAG_SIZE;
    }

    public int getMaximumRoundsNumber() {
        return MAXIMUM_ROUNDS_NUMBER;
    }

    public Map<String, Integer> getGoodsIds() {
        return GOODS_IDS;
    }

    public int getMaximumBribe() {
        return MAXIMUM_BRIBE;
    }

    public int getMinimumBribe() {
        return MINIMUM_BRIBE;
    }

    public Map<String, Integer> getGoodsProfit() {
        return GOODS_PROFIT;
    }

    public int getLegalGoodPenalty() {
        return LEGAL_GOOD_PENALTY;
    }

    public int getCardsInHandNr() {
        return CARDS_IN_HAND_NR;
    }

    public Map<String, Integer> getKingBonus() {
        return KING_BONUS;
    }

    public Map<String, Integer> getQueenBonus() {
        return QUEEN_BONUS;
    }

    public static int getSilkBonusCheeseQuantity() {
        return SILK_BONUS_CHEESE_QUANTITY;
    }

    public static int getPepperBonusChickenQuantity() {
        return PEPPER_BONUS_CHICKEN_QUANTITY;
    }

    public static int getBarrelBonusBreadQuantity() {
        return BARREL_BONUS_BREAD_QUANTITY;
    }

    public static int getBeerBonusWineQuantity() {
        return BEER_BONUS_WINE_QUANTITY;
    }

    public static int getSeafoodBonusTomatoQuantity() {
        return SEAFOOD_BONUS_TOMATO_QUANTITY;
    }

    public static int getSeafoodBonusPotatoQuantity() {
        return SEAFOOD_BONUS_POTATO_QUANTITY;
    }

    public static int getSeafoodBonusChickenQuantity() {
        return SEAFOOD_BONUS_CHICKEN_QUANTITY;
    }
}
