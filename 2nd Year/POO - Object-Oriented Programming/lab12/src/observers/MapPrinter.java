package observers;

import entities.Hero;
import entities.Monster;
import game.GameState;
import entities.Treasure;

import java.util.Observable;
import java.util.Observer;

/**
 * Observer that prints the game's world (the map with all the treasures,
 * heroes, obstacles)
 */
public class MapPrinter implements Observer {

    private int[][] map;

    @Override
    public void update(Observable o, Object arg) {
        GameState gs = (GameState) o;

        // TODO nicer deep-copy
        this.map = new int[GameState.MAP_SIZE][GameState.MAP_SIZE];

        for (int i = 0; i < GameState.MAP_SIZE; i++)
            for (int j = 0; j < GameState.MAP_SIZE; j++)
                this.map[i][j] = gs.getMap()[i][j];


        for (Hero h : gs.getParty()) {
            this.map[h.getPosx()][h.getPosy()] = 2;
        }

        for (Treasure t : gs.getTreasures()) {
            this.map[t.getPosx()][t.getPosy()] = 3;
        }

        for (Monster m : gs.getMonsters()) {
            this.map[m.getPosx()][m.getPosy()] = 4;
        }

        StringBuffer sb = new StringBuffer();

        for (int i = 0; i < GameState.MAP_SIZE; i++) {
            for (int j = 0; j < GameState.MAP_SIZE; j++) {

                if (map[i][j] == 3)
                    sb.append('T');
                else if (map[i][j] == 2)
                    sb.append('H');
                else if (map[i][j] == 4)
                    sb.append('M');
                else sb.append(map[i][j]);
                for (int k = 0; k < 2; k++)
                    sb.append(" ");
            }
            sb.append("\n");
        }

        System.out.println(new String(sb));
    }
}
