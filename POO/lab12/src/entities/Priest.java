package entities;

import entities.Treasure.DamageType;
import strategies.AttackStrategy;
import strategies.DefenseStrategy;

public class Priest extends Hero {

    private int knowledge;

    public Priest(String name, int i) {

        this.name = name;
        this.knowledge = i;
        this.hp = 100;
        this.baseHp = 50;
        this.damageType = DamageType.Poison;
    }

    @Override
    public String toString() {
        return new String("Sneaky Priest " + name + " of knowledge " + knowledge);
    }

    public int getBaseDamage() {
        return knowledge;
    }

	@Override
	public DamageType getDamageType() {
		return this.damageType;
	}
}
