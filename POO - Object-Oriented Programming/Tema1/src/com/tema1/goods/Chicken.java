package com.tema1.goods;

import com.tema1.main.Constants;

/**
 * Clasa care reprezinta bunul "Chicken".
 */
public class Chicken extends LegalGoods {

    public Chicken() {
        super(Constants.getInstance().getGoodsIds().get("Chicken"),
                Constants.getInstance().getGoodsProfit().get("Chicken"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Chicken"),
                Constants.getInstance().getQueenBonus().get("Chicken"));
    }
}
