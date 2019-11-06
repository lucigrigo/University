package com.tema1.goods;

import com.tema1.main.Main;

public class Bread extends LegalGoods {

    public Bread() {
        super(Main.constants.getGoodsIds().get("Bread"),
                Main.constants.getGoodsProfit().get("Bread"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Bread"),
                Main.constants.getQueenBonus().get("Bread"));
    }
}
