package com.tema1.goods;

import com.tema1.main.Constants;

/**
 * Clasa care reprezinta bunul "Bread".
 */
public class Bread extends LegalGoods {

    public Bread() {
        super(Constants.getInstance().getGoodsIds().get("Bread"),
                Constants.getInstance().getGoodsProfit().get("Bread"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Bread"),
                Constants.getInstance().getQueenBonus().get("Bread"));
    }
}
