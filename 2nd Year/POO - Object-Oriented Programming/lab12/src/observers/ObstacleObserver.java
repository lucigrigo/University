package observers;

import entities.Hero;
import entities.Obstacle;
import game.GameState;

import java.io.ObjectStreamClass;
import java.util.Observable;
import java.util.Observer;

public class ObstacleObserver implements Observer {

    @Override
    public void update(Observable o, Object arg) {
        for (Hero hero : ((GameState) o).getParty()) {
            int x = hero.getPosx();
            int y = hero.getPosy();
            for (Obstacle obstacle : ((GameState) o).getObstacles()) {
                if (obstacle.getxPos() == x && obstacle.getyPos() == y) {
                    System.out.println("CAN'T MOVE THERE");
                    ((GameState) o).undo();
                }
            }
        }
    }
}
