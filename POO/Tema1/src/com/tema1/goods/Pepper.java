package com.tema1.goods;

import com.tema1.main.Main;

import java.util.HashMap;

public class Pepper extends IllegalGoods {

    public Pepper() {
        super(Main.constants.getGoodsIds().get("Pepper"),
                Main.constants.getGoodsProfit().get("Pepper"),
                Main.constants.getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
            {
                put(new Chicken(), 2);
            }
        });
    }
}
