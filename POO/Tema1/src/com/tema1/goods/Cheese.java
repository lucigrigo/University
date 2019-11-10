package com.tema1.goods;

import com.tema1.main.Constants;

/**
 * Clasa care reprezinta bunul "Cheese".
 */
public class Cheese extends LegalGoods {

    public Cheese() {
        super(Constants.getInstance().getGoodsIds().get("Cheese"),
                Constants.getInstance().getGoodsProfit().get("Cheese"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Cheese"),
                Constants.getInstance().getQueenBonus().get("Cheese"));
    }
}
