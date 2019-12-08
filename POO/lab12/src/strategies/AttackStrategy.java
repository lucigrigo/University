package strategies;

import entities.Hero;
import entities.Monster;
import entities.Treasure;

import java.util.concurrent.TransferQueue;

public class AttackStrategy implements Strategy {

    //TODO Implement constructor with a Hero as argument

    private Hero owner;

    public AttackStrategy(Hero owner) {
        this.owner = owner;
    }

    @Override
    public void attack(Monster m) {
        // TODO implement me

	    /*	Attack algorithm
			if hero type weapon found use it (x3 weapon damage)
				else if counter weapon found use it (x2 weapon damage)
				else basic attack (no bonus)
			--> In order to find the weapon, iterate through the inventory of the hero.
	    */

        for (Treasure treasure : owner.getInventory()) {
            if (treasure.getDamageType() == owner.getDamageType()) {
                m.setHP(m.getHP() - 3 * treasure.getDmg());
                return;
            }
        }

        for (Treasure treasure : owner.getInventory()) {
            if (treasure.getDamageType() == m.getWeakness()) {
                m.setHP(m.getHP() - 2 * treasure.getDmg());
                return;
            }
        }

        m.setHP(m.getHP() - owner.getBaseDamage());
    }

}
