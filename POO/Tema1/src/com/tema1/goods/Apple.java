package com.tema1.goods;

import com.tema1.main.Main;

public class Apple extends LegalGoods {

    public Apple() {
        super(Main.constants.getGoodsIds().get("Apple"),
                Main.constants.getGoodsProfit().get("Apple"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Apple"),
                Main.constants.getQueenBonus().get("Apple"));
    }
}
