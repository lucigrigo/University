package com.tema1.goods;

import com.tema1.main.Main;

public class Wine extends LegalGoods {

    public Wine() {
        super(Main.constants.getGoodsIds().get("Wine"),
                Main.constants.getGoodsProfit().get("Wine"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Wine"),
                Main.constants.getQueenBonus().get("Wine"));
    }
}
