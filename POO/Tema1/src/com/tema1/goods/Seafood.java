package com.tema1.goods;

import com.tema1.main.Main;

import java.util.HashMap;

public class Seafood extends IllegalGoods {

    public Seafood() {
        super(Main.constants.getGoodsIds().get("Seafood"),
                Main.constants.getGoodsProfit().get("Seafood"),
                Main.constants.getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
                    {
                        put(new Tomato(), 2);
                        put(new Potato(), 3);
                        put(new Chicken(), 1);
                    }
                }

        );
    }
}
