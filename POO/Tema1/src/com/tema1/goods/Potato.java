package com.tema1.goods;

import com.tema1.main.Main;

public class Potato extends LegalGoods {

    public Potato() {
        super(Main.constants.getGoodsIds().get("Potato"),
                Main.constants.getGoodsProfit().get("Potato"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Potato"),
                Main.constants.getQueenBonus().get("Potato"));
    }
}
