package factories;

import entities.Hero;
import entities.Mage;
import entities.Priest;
import entities.Warrior;

public class HeroFactory {
    private static HeroFactory factory = null;

    public static HeroFactory getInstance() {
        if (factory == null) {
            factory = new HeroFactory();
        }

        return factory;
    }

    private HeroFactory() {
    }

    private Hero createWarrior(String name) {

        return new Warrior(name, 15); // maybe replace 15 with smth random
    }

    private Hero createMage(String name) {

        return new Mage(name, 10);
    }

    private Hero createPriest(String name) {

        return new Priest(name, 20);
    }

    public Hero createHero(Hero.HeroType type, String name) {

        switch (type) {
            case WARRIOR:
                return createWarrior(name);

            case MAGE:
                return createMage(name);

            case PRIEST:
                return createPriest(name);

            default:
                return null;
        }
    }
}
