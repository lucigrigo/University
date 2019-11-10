package com.tema1.goods;

import com.tema1.main.Constants;

/**
 * Clasa care reprezinta bunul "Tomato".
 */
public final class Tomato extends LegalGoods {

    public Tomato() {
        super(Constants.getInstance().getGoodsIds().get("Tomato"),
                Constants.getInstance().getGoodsProfit().get("Tomato"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Tomato"),
                Constants.getInstance().getQueenBonus().get("Tomato"));
    }
}
