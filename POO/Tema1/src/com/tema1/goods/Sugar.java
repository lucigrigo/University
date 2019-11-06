package com.tema1.goods;

import com.tema1.main.Main;

public class Sugar extends LegalGoods {

    public Sugar() {
        super(Main.constants.getGoodsIds().get("Sugar"),
                Main.constants.getGoodsProfit().get("Sugar"),
                Main.constants.getLegalGoodPenalty(),
                Main.constants.getKingBonus().get("Sugar"),
                Main.constants.getQueenBonus().get("Sugar"));
    }
}
