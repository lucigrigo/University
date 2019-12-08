package entities;

import game.GameState;
import strategies.AttackStrategy;
import strategies.DefenseStrategy;
import strategies.Strategy;

import java.util.ArrayList;
import java.util.List;

import entities.Treasure.DamageType;

public abstract class Hero {

    protected String name;
    protected List<Treasure> inventory;
    protected int posx, posy;
    protected int hp;
    protected Monster target;
    protected Strategy strategy;
    protected DamageType damageType;
    protected int hpBoost = 20;
    protected int baseHp;

    /* Hero actions */
    public void move(Direction direction) {
        GameState gs = GameState.getInstance();
        setTarget(null);

        if (direction == Direction.E)
            posy = (posy + 1) % GameState.MAP_SIZE;
        if (direction == Direction.W)
            posy = (posy + GameState.MAP_SIZE - 1) % GameState.MAP_SIZE;
        if (direction == Direction.S)
            posx = (posx + 1) % GameState.MAP_SIZE;
        if (direction == Direction.N)
            posx = (posx + GameState.MAP_SIZE - 1) % GameState.MAP_SIZE;

        gs.update();
    }

    public void collect(Treasure treasure) {

        // "removing the treasure from the map...ugly hack"
        treasure.setPosx(-1);
        treasure.setPosy(-1);

        if (inventory == null)
            inventory = new ArrayList<>();

        // this hero now has the treasure
        inventory.add(treasure);

    }

    public void attack() {
        // TODO check if hero can attack (at his position, there should be a monster)
        //       ->use canAttack() method from the base class
        // * choose what strategy you should use according to the Hero's HP
        //       -> use the Strategy object from the base class
        // * if it can use the strategy to attack and update Hero HP (deduct target damage)
        // * and print a message
        if (this.getHP() >= 50) {
            this.strategy = new AttackStrategy(this);
        } else {
            this.strategy = new DefenseStrategy(this);
        }
        this.strategy.attack(target);
    }

    public abstract DamageType getDamageType();

    public abstract int getBaseDamage();


    /* Getters and setters */
    public int getPosy() {
        return posy;
    }

    public void setPosy(int posy) {
        this.posy = posy;
    }

    public int getPosx() {
        return posx;
    }

    public void setPosx(int posx) {
        this.posx = posx;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<Treasure> getInventory() {
        return inventory;
    }

    public void setHP(int hp) {
        this.hp = hp;
    }

    public int getHP() {
        return this.hp;
    }

    public void setTarget(Monster m) {
        this.target = m;
    }

    public Monster getTarget() {
        return target;
    }

    public boolean canAttack() {
        return this.target != null;
    }

    public int getBaseHpBoost() {
        return hpBoost;
    }

    public enum HeroType {
        WARRIOR, MAGE, PRIEST
    }

    public enum Direction {
        S, N, E, W//, NV, NE, SE, SV
    }
}
