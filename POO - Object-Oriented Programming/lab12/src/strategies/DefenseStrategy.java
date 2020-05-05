package strategies;

import entities.Hero;
import entities.Monster;
import entities.Treasure;

public class DefenseStrategy implements Strategy {

    //TODO Implement constructor with a Hero as argument

    private Hero owner;

    public DefenseStrategy(Hero owner) {
        this.owner = owner;
    }

    @Override
    public void attack(Monster m) {
        // TODO implement me

	    /*	Attack algorithm
			if hero type weapon found boost HP with treasure.getHpBoost() + hero.getBaseHpBoost()
				else boost HP with getBaseHpBoost()
			Do a basic attack on the monster -> hero.getBaseDamage()
			--> In order to find the weapon, iterate through the inventory of the hero.
	    */

        m.setHP(m.getHP() - owner.getBaseDamage());
        for (Treasure treasure : owner.getInventory()) {
            if (treasure.getDamageType() == owner.getDamageType()) {
                owner.setHP(owner.getHP() + owner.getBaseHpBoost() + treasure.getBoostHp());
                return;
            }
        }

        owner.setHP((owner.getHP() + owner.getBaseHpBoost()));
    }

}
