package com.tema1.goods;

import com.tema1.main.Main;

public class Chicken extends LegalGoods {

    public Chicken() {
        super(Main.constants.getGoodsIds().get("Chicken"),
                Main.constants.getGoodsProfit().get("Chicken"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Chicken"),
                Main.constants.getQueenBonus().get("Chicken"));
    }
}
