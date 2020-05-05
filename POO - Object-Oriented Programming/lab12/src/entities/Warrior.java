package entities;

import entities.Treasure.DamageType;
import strategies.AttackStrategy;
import strategies.DefenseStrategy;

public class Warrior extends Hero {

    private int damage;

    public Warrior(String name, int i) {

        this.name = name;
        this.damage = i;
        this.hp = 120;
        this.baseHp = 60;
        this.damageType = DamageType.Blunt;
    }


    @Override
    public String toString() {
        return new String("Mighty Warrior " + name + " of strength " + damage);
    }

    public int getBaseDamage() {
        return damage;
    }

	@Override
	public DamageType getDamageType() {
		return this.damageType;
	}
}
