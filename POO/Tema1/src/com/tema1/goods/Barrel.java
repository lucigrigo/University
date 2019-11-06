package com.tema1.goods;

import com.tema1.main.Main;

import java.util.HashMap;

public class Barrel extends IllegalGoods {

    public Barrel() {
        super(Main.constants.getGoodsIds().get("Barrel"),
                Main.constants.getGoodsProfit().get("Barrel"),
                Main.constants.getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
                    {
                        put(new Bread(), 2);
                    }
                });
    }
}
