package com.luciangrigore;

import java.util.Map;

public class Main {
    private static StockList stockList = new StockList();

    public static void main(String[] args) {
        StockItem temp = new StockItem("bread", 0.86, 100);
        stockList.addStock(temp);

        temp = new StockItem("cake", 1.10, 7);
        stockList.addStock(temp);

        temp = new StockItem("car", 12.50, 2);
        stockList.addStock(temp);

        temp = new StockItem("chair", 62.0, 10);
        stockList.addStock(temp);

        temp = new StockItem("cup", 0.50, 200);
        stockList.addStock(temp);
        temp = new StockItem("cup", 0.45, 7);
        stockList.addStock(temp);

        temp = new StockItem("door", 72.95, 4);
        stockList.addStock(temp);

        temp = new StockItem("juice", 2.50, 36);
        stockList.addStock(temp);

        temp = new StockItem("phone", 99.99, 35);
        stockList.addStock(temp);

        temp = new StockItem("towel", 2.40, 80);
        stockList.addStock(temp);

        temp = new StockItem("vase", 8.76, 40);
        stockList.addStock(temp);

        System.out.print("=============================================");
        System.out.println(stockList.toString());
        System.out.println("=============================================");

        for (String s : stockList.Items().keySet()) {
            System.out.println(s);
        }

        Basket lucisBasket = new Basket("Luci");
        sellItem(lucisBasket, "car", 1);
        System.out.println(lucisBasket);

        sellItem(lucisBasket, "car", 1);
        System.out.println(lucisBasket);

        sellItem(lucisBasket, "car", 1);
        sellItem(lucisBasket, "laptee", 1);
        System.out.println(lucisBasket);

        sellItem(lucisBasket, "juice", 4);
        sellItem(lucisBasket, "cup", 12);
        sellItem(lucisBasket, "bread", 1);
        System.out.println(lucisBasket);
        System.out.println(stockList);

//        temp = new StockItem("pen",1.12);
//        stockList.Items().put(temp.getName(),temp);
        stockList.Items().get("car").adjustStock(2000);
        stockList.get("car").adjustStock(-1000);

        System.out.println(stockList);
        System.out.println("--------------------------------------------");
        for (Map.Entry<String, Double> price : stockList.PriceList().entrySet()) {
            System.out.println(price.getKey() + " costs " + price.getValue());
        }
    }

    public static int sellItem(Basket basket, String item, int quantity) {
        //  retrieve the item from the stock list
        StockItem stockItem = stockList.get(item);
        if (stockItem == null) {
            System.out.println("We do not sell " + item + "!");
            return 0;
        }
        if (stockList.sellStock(item, quantity) != 0) {
            basket.addToBasket(stockItem, quantity);
            return quantity;
        }
        return 0;
    }
}
