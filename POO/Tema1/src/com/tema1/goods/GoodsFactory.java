package com.tema1.goods;

import com.tema1.main.Main;

import java.util.HashMap;
import java.util.Map;

public final class GoodsFactory {
    private static GoodsFactory instance = null;

    private final Map<Integer, Goods> goodsById;

    private GoodsFactory() {
        goodsById = new HashMap<>();

        initLegalGoods();
        initIllegalGoods();
    }

    private void initLegalGoods() {
        // create the types of legal goods
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

        // insert legal goods into a hashMap
        goodsById.put(Main.constants.getGoodsIds().get("Apple"), good0);
        goodsById.put(Main.constants.getGoodsIds().get("Cheese"), good1);
        goodsById.put(Main.constants.getGoodsIds().get("Bread"), good2);
        goodsById.put(Main.constants.getGoodsIds().get("Chicken"), good3);
        goodsById.put(Main.constants.getGoodsIds().get("Tomato"), good4);
        goodsById.put(Main.constants.getGoodsIds().get("Corn"), good5);
        goodsById.put(Main.constants.getGoodsIds().get("Potato"), good6);
        goodsById.put(Main.constants.getGoodsIds().get("Wine"), good7);
        goodsById.put(Main.constants.getGoodsIds().get("Salt"), good8);
        goodsById.put(Main.constants.getGoodsIds().get("Sugar"), good9);
    }

    private void initIllegalGoods() {
//         create the types of illegal goods
        Goods good0 = new Silk();
        Goods good1 = new Pepper();
        Goods good2 = new Barrel();
        Goods good3 = new Beer();
        Goods good4 = new Seafood();

        // insert illegal goods into a hashMap
        goodsById.put(Main.constants.getGoodsIds().get("Silk"), good0);
        goodsById.put(Main.constants.getGoodsIds().get("Pepper"), good1);
        goodsById.put(Main.constants.getGoodsIds().get("Barrel"), good2);
        goodsById.put(Main.constants.getGoodsIds().get("Beer"), good3);
        goodsById.put(Main.constants.getGoodsIds().get("Seafood"), good4);
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
