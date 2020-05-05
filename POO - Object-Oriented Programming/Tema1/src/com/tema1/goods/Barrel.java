package com.tema1.goods;

import com.tema1.main.Constants;

import java.util.HashMap;

/**
 * Clasa care reprezinta bunul "Barrel".
 */
public class Barrel extends IllegalGoods {

    public Barrel() {
        super(Constants.getInstance().getGoodsIds().get("Barrel"),
                Constants.getInstance().getGoodsProfit().get("Barrel"),
                Constants.getInstance().getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
                    {
                        put(new Bread(), Constants.getInstance().getBarrelBonusBreadQuantity());
                    }
                });
    }
}
