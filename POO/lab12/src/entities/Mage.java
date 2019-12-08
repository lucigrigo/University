package entities;

import entities.Treasure.DamageType;
import strategies.AttackStrategy;
import strategies.DefenseStrategy;

public class Mage extends Hero {

    private int magicalDamage;

    public Mage(String name, int i) {

        this.name = name;
        this.magicalDamage = i;
        this.hp = 90;
        this.baseHp = 45;
        this.damageType = DamageType.Magic;
    }

    @Override
    public String toString() {
        return new String("Powerful Mage " + name + " of strength " + magicalDamage);
    }

    public int getBaseDamage() {
        return magicalDamage;
    }

	@Override
	public DamageType getDamageType() {
		return this.damageType;
	}
}
