package com.tema1.goods;

import com.tema1.main.Main;

public class Salt extends LegalGoods {

    public Salt() {
        super(Main.constants.getGoodsIds().get("Salt"),
                Main.constants.getGoodsProfit().get("Salt"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Salt"),
                Main.constants.getQueenBonus().get("Salt"));
    }
}
