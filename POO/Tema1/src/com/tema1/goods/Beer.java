package com.tema1.goods;

import com.tema1.main.Main;

import java.util.HashMap;

public class Beer extends IllegalGoods {

    public Beer() {
        super(Main.constants.getGoodsIds().get("Beer"),
                Main.constants.getGoodsProfit().get("Beer"),
                Main.constants.getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
                    {
                        put(new Wine(),  4);
                    }
                });
    }
}
