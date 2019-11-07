package com.tema1.goods;

import com.tema1.main.Constants;

import java.util.HashMap;

public class Seafood extends IllegalGoods {

    public Seafood() {
        super(Constants.getInstance().getGoodsIds().get("Seafood"),
                Constants.getInstance().getGoodsProfit().get("Seafood"),
                Constants.getInstance().getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
                    {
                        put(new Tomato(), Constants.getInstance().getSeafoodBonusTomatoQuantity());
                        put(new Potato(), Constants.getInstance().getSeafoodBonusPotatoQuantity());
                        put(new Chicken(), Constants.getInstance().
                                getSeafoodBonusChickenQuantity());
                    }
                }

        );
    }
}
