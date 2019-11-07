package com.tema1.goods;

import com.tema1.main.Constants;

import java.util.HashMap;

public class Pepper extends IllegalGoods {

    public Pepper() {
        super(Constants.getInstance().getGoodsIds().get("Pepper"),
                Constants.getInstance().getGoodsProfit().get("Pepper"),
                Constants.getInstance().getIllegalGoodPenalty(),
                new HashMap<Goods, Integer>() {
            {
                put(new Chicken(), Constants.getInstance().getPepperBonusChickenQuantity());
            }
        });
    }
}
