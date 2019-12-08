package factories;

import entities.Monster;
import entities.Treasure;

import java.util.Random;

/**
 * Builds random monster objects. Hides the monster creation mechanism using
 * a factory method.
 */
public class MonsterFactory {
    private static MonsterFactory factory = null;

    private Treasure.DamageType[] types = Treasure.DamageType.values();
    private Random rand = new Random();

    public Treasure.DamageType randomDamageType() {
        return types[rand.nextInt(types.length)];
    }

    public static MonsterFactory getInstance() {

        if (factory == null)
            factory = new MonsterFactory();
        return factory;
    }

    private MonsterFactory() {
    }

    public Monster createMonster() {

        String[] names = {"Krark", "Okur", "Krerag", "Nukorg", "Ikag", "Krougrok",
                "Xaarut", "Yuwegruk", "Niukug", "Exikor"};

        return new Monster(names[rand.nextInt(names.length)], randomDamageType());
    }
}