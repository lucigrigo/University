package game;

import commands.Command;
import commands.CommandManager;
import entities.Hero;
import entities.Monster;
import entities.Obstacle;
import entities.Treasure;
import factories.MonsterFactory;
import factories.TreasureFactory;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Random;

public class GameState extends Observable {

    public static final int MAP_SIZE = 5;

    private ArrayList<Hero> party = new ArrayList<Hero>();
    private ArrayList<Treasure> treasures = new ArrayList<Treasure>();
    private boolean adventureStarted = false;
    private CommandManager cm = new CommandManager();
    private ArrayList<Monster> monsters = new ArrayList<Monster>();
    private ArrayList<Obstacle> obstacles = new ArrayList<>();

    private void addObstacle(Obstacle o) {
        this.obstacles.add(o);
    }

    public ArrayList<Obstacle> getObstacles() {
        return obstacles;
    }

    // you can change how the map is created if you'd like
    private int[][] map = new int[][]
            {
                    {0, 1, 1, 1, 0},
                    {0, 0, 0, 1, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0}
            };


    private static GameState gs = null;

    private GameState() {
    }

    public static GameState getInstance() {

        if (gs == null)
            gs = new GameState();
        return gs;
    }

    public void update() {

        this.setChanged();
        this.notifyObservers();
    }

    public void populateTreasures(int numTreasures) {

        Random rand = new Random();

        if (numTreasures > MAP_SIZE * MAP_SIZE) {
            System.err.println("Too many treasures");
            return;
        }

        for (int i = 0; i < numTreasures; i++) {

            Treasure t = TreasureFactory.getInstance().createTreasure();

            int x, y;

            do {
                x = rand.nextInt(MAP_SIZE);
                y = rand.nextInt(MAP_SIZE);
            } while (map[x][y] != 0);

            t.setPosx(x);
            t.setPosy(y);

            //map[x][y] = 3;
            treasures.add(t);
        }
    }

    public void populateMonsters(int numMonsters) {

        Random rand = new Random();

        if (numMonsters > MAP_SIZE * MAP_SIZE) {
            System.err.println("Too many monsters");
            return;
        }

        for (int i = 0; i < numMonsters; i++) {

            Monster t = MonsterFactory.getInstance().createMonster();

            int x, y;

            do {
                x = rand.nextInt(MAP_SIZE);
                y = rand.nextInt(MAP_SIZE);
            } while (map[x][y] != 0);

            t.setPosx(x);
            t.setPosy(y);

            //map[x][y] = 4;
            monsters.add(t);
        }
    }

    public void removeTreasure(Treasure t) {
        treasures.remove(t);
    }

    public void removeMonster(Monster m) {
        monsters.remove(m);
    }

    public ArrayList<Hero> getParty() {
        return party;
    }

    public void removeHero(Hero h) {
        party.remove(h);
    }

    public void setParty(ArrayList<Hero> party) {
        this.party = party;
    }

    public ArrayList<Treasure> getTreasures() {
        return treasures;
    }

    public ArrayList<Monster> getMonsters() {
        return monsters;
    }

    public void setTreasures(ArrayList<Treasure> treasures) {
        this.treasures = treasures;
    }

    public void setMonsters(ArrayList<Monster> monsters) {
        this.monsters = monsters;
    }

    public boolean isAdventureStarted() {
        return adventureStarted;
    }

    public void setAdventureStarted(boolean adventureStarted) {
        this.adventureStarted = adventureStarted;
    }

    public int[][] getMap() {
        return map;
    }

    public void setMap(int[][] map) {
        this.map = map;
    }

    public void undo() {
        if (cm.isUndoAvailable())
            cm.undo();
    }

    public void redo() {
        if (cm.isRedoAvailable())
            cm.redo();
    }

    public void executeCommand(Command c) {
        cm.executeCommand(c);
    }
}
