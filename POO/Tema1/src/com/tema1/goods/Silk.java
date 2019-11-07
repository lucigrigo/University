package com.tema1.goods;

import com.tema1.main.Constants;

import java.util.HashMap;

public class Silk extends IllegalGoods {

    public Silk() {
        super(Constants.getInstance().getGoodsIds().get("Silk"),
                Constants.getInstance().getGoodsProfit().get("Silk"),
                Constants.getInstance().getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
                    {
                        put(new Cheese(), Constants.getInstance().getSilkBonusCheeseQuantity());
                    }
                });
    }
}
