package com.tema1.goods;

import com.tema1.main.Constants;

/**
 * Clasa care reprezinta bunul "Sugar".
 */
public class Sugar extends LegalGoods {

    public Sugar() {
        super(Constants.getInstance().getGoodsIds().get("Sugar"),
                Constants.getInstance().getGoodsProfit().get("Sugar"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Sugar"),
                Constants.getInstance().getQueenBonus().get("Sugar"));
    }
}
