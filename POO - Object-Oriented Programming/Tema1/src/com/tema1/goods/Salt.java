package com.tema1.goods;

import com.tema1.main.Constants;

/**
 * Clasa care reprezinta bunul "Salt".
 */
public class Salt extends LegalGoods {

    public Salt() {
        super(Constants.getInstance().getGoodsIds().get("Salt"),
                Constants.getInstance().getGoodsProfit().get("Salt"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Salt"),
                Constants.getInstance().getQueenBonus().get("Salt"));
    }
}
