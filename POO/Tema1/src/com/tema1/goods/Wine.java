package com.tema1.goods;

import com.tema1.main.Constants;

public class Wine extends LegalGoods {

    public Wine() {
        super(Constants.getInstance().getGoodsIds().get("Wine"),
                Constants.getInstance().getGoodsProfit().get("Wine"),
                Constants.getInstance().getLegalGoodPenalty(),
                Constants.getInstance().getKingBonus().get("Wine"),
                Constants.getInstance().getQueenBonus().get("Wine"));
    }
}
