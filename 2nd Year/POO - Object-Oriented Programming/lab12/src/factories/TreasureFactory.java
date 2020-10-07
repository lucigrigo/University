package factories;

import entities.Treasure;

import java.util.Random;

/**
 * Builds random treasure objects. Hides the treasure creation mechanism using
 * a factory method.
 */
public class TreasureFactory {
    private static TreasureFactory factory = null;

    private Treasure.DamageType[] types = Treasure.DamageType.values();
    // private int size = types.size();
    private Random rand = new Random();

    public Treasure.DamageType randomDamageType() {
        return types[rand.nextInt(types.length)];
    }

    public static TreasureFactory getInstance() {

        if (factory == null)
            factory = new TreasureFactory();
        return factory;
    }

    private TreasureFactory() {
    }

    public Treasure createTreasure() {

        String[] names = {"Sword of Justice",
                "Leg of St Andrew",
                "Rabbit's Foot",
                "5-leaf Clover",
                "Shield of the Wise",
                "Dumbbels"};
        String[] lore = {"it looks quite old",
                "you've heard of this before",
                "tales of this legendary item are told in each tavern",
                "the devourer of souls"};

        return new Treasure(names[rand.nextInt(names.length)], lore[rand.nextInt(lore.length)], randomDamageType(), rand.nextInt(30) + 10, rand.nextInt(10));
    }
}
