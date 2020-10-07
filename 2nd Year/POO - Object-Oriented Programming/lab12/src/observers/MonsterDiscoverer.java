package observers;

import entities.Hero;
import entities.Monster;
import game.GameState;

import java.util.Observable;
import java.util.Observer;

/**
 * Prints the weakness of a monster when a hero discovers it.
 */
public class MonsterDiscoverer implements Observer {

    public void update(Observable o, Object arg) {

        GameState gs = GameState.getInstance();

        for (Hero h : gs.getParty()) {
            for (Monster t : gs.getMonsters())

                if (h.getPosx() == t.getPosx() &&
                        h.getPosy() == t.getPosy()) {
                    System.out.println("Hero " + h.getName() + " has found a monster: " + t.getName());
                    System.out.println(t);

                    h.setTarget(t);
                }
        }
    }
}
