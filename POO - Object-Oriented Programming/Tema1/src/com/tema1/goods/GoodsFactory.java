package com.tema1.goods;

import com.tema1.main.Constants;

import java.util.HashMap;
import java.util.Map;

/**
 * Un 'factory' care initializeaza toate bunurile din joc.
 * Am facut-o singleton.
 */
public final class GoodsFactory {
    private static GoodsFactory instance = null;

    private final Map<Integer, Goods> goodsById;

    private GoodsFactory() {
        goodsById = new HashMap<>();

        initLegalGoods();
        initIllegalGoods();
    }

    private void initLegalGoods() {
        // crearea bunurilor legale
        Goods good0 = new Apple();
        Goods good1 = new Cheese();
        Goods good2 = new Bread();
        Goods good3 = new Chicken();
        Goods good4 = new Tomato();
        Goods good5 = new Corn();
        Goods good6 = new Potato();
        Goods good7 = new Wine();
        Goods good8 = new Salt();
        Goods good9 = new Sugar();

        // punerea bunurilor legale intr-un HashMap
        goodsById.put(Constants.getInstance().getGoodsIds().get("Apple"), good0);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Cheese"), good1);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Bread"), good2);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Chicken"), good3);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Tomato"), good4);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Corn"), good5);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Potato"), good6);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Wine"), good7);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Salt"), good8);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Sugar"), good9);
    }

    private void initIllegalGoods() {
        // crearea bunurilor ilegale
        Goods good0 = new Silk();
        Goods good1 = new Pepper();
        Goods good2 = new Barrel();
        Goods good3 = new Beer();
        Goods good4 = new Seafood();

        // punerea bunurilor ilegale intr-un HashMap
        goodsById.put(Constants.getInstance().getGoodsIds().get("Silk"), good0);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Pepper"), good1);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Barrel"), good2);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Beer"), good3);
        goodsById.put(Constants.getInstance().getGoodsIds().get("Seafood"), good4);
    }

    public static GoodsFactory getInstance() {
        if (instance == null) {
            instance = new GoodsFactory();
        }
        return instance;
    }

    public Goods getGoodsById(final int id) {
        return goodsById.get(id);
    }

    public Map<Integer, Goods> getAllGoods() {
        return goodsById;
    }
}
