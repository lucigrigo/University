package com.tema1.goods;

import com.tema1.main.Constants;

/**
 * Clasa care reprezinta bunul "Apple".
 */
public class Apple extends LegalGoods {

    public Apple() {
        super(Constants.getInstance().getGoodsIds().get("Apple"),
                Constants.getInstance().getGoodsProfit().get("Apple"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Apple"),
                Constants.getInstance().getQueenBonus().get("Apple"));
    }
}
