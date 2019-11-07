package com.tema1.goods;

import com.tema1.main.Constants;

public class Potato extends LegalGoods {

    public Potato() {
        super(Constants.getInstance().getGoodsIds().get("Potato"),
                Constants.getInstance().getGoodsProfit().get("Potato"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Potato"),
                Constants.getInstance().getQueenBonus().get("Potato"));
    }
}
