package com.tema1.goods;

import com.tema1.main.Main;

public class Cheese extends LegalGoods {

    public Cheese() {
        super(Main.constants.getGoodsIds().get("Cheese"),
                Main.constants.getGoodsProfit().get("Cheese"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Cheese"),
                Main.constants.getQueenBonus().get("Cheese"));
    }
}
