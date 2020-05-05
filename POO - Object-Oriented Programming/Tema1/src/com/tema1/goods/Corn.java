package com.tema1.goods;

import com.tema1.main.Constants;

/**
 * Clasa care reprezinta bunul "Corn".
 */
public class Corn extends LegalGoods {

    public Corn() {
        super(Constants.getInstance().getGoodsIds().get("Corn"),
                Constants.getInstance().getGoodsProfit().get("Corn"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Corn"),
                Constants.getInstance().getQueenBonus().get("Corn"));
    }
}
