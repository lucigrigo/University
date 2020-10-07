package com.tema1.goods;

import com.tema1.main.Constants;

import java.util.HashMap;

/**
 * Clasa care reprezinta bunul "Beer".
 */
public class Beer extends IllegalGoods {

    public Beer() {
        super(Constants.getInstance().getGoodsIds().get("Beer"),
                Constants.getInstance().getGoodsProfit().get("Beer"),
                Constants.getInstance().getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
                    {
                        put(new Wine(),  Constants.getInstance().getBeerBonusWineQuantity());
                    }
                });
    }
}
