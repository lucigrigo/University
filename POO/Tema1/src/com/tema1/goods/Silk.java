package com.tema1.goods;

import com.tema1.main.Main;

import java.util.HashMap;

public class Silk extends IllegalGoods {

    public Silk() {
        super(Main.constants.getGoodsIds().get("Silk"),
                Main.constants.getGoodsProfit().get("Silk"),
                Main.constants.getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
                    {
                        put(new Cheese(), 3);
                    }
                });
    }
}
