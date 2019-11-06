package com.tema1.goods;

import com.tema1.main.Main;

public class Corn extends LegalGoods {

    public Corn() {
        super(Main.constants.getGoodsIds().get("Corn"),
                Main.constants.getGoodsProfit().get("Corn"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Corn"),
                Main.constants.getQueenBonus().get("Corn"));
    }
}
