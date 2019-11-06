package com.tema1.goods;

import com.tema1.main.Main;

public final class Tomato extends LegalGoods {

    public Tomato() {
        super(Main.constants.getGoodsIds().get("Tomato"),
                Main.constants.getGoodsProfit().get("Tomato"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Tomato"),
                Main.constants.getQueenBonus().get("Tomato"));
    }
}
