package game;

import commands.MoveCommand;
import entities.Hero;
import entities.Hero.Direction;
import entities.Hero.HeroType;
import factories.HeroFactory;
import observers.MapPrinter;
import observers.MonsterDiscoverer;
import observers.TreasureDiscoverer;

import java.util.Scanner;

public class Main {

    public static GameState gs = GameState.getInstance();

    private static String helpMessage() {

        String s = "Commands:\n"
                + "\t start - starts an adventure, must be called after adding heroes\n"
                + "\t add <hero-type> <hero-name>\n"
                + "\t\t hero types: warrior, mage, priest (any case)\n"
                + "\t move <hero-name> <direction>\n"
                + "\t\t directions: right, left, up, down\n"
                + "\t undo - undo last move\n"
                + "\t redo - redo last undo\n"
                + "\t stop - ends the program\n"
                + "\t attack <hero-name> - attacks monster, must be on same coordinates as monster\n"
                + "\t help - prints this menu\n";

        return s;
    }


    public static void main(String[] args) {

        while (true) {
            System.out.println(">");
            Scanner sc = new Scanner(System.in);
            String cmd = sc.nextLine();
            String[] cmdTokens = cmd.split(" ");

            switch (cmdTokens[0]) {

                case "help":
                    System.out.println(Main.helpMessage());
                    break;

                case "add":
                    if (gs.isAdventureStarted()) {
                        System.out.println("Adventure has already started..."
                                + "maybe next time!\n");
                        break;
                    }

                    if (cmdTokens.length < 3) {
                        System.out.println("Not enough parameters..!\n"
                                + Main.helpMessage());
                        break;
                    }

                    System.out.println("Adding " + cmdTokens[1]
                            + " named " + cmdTokens[2]
                            + " to the party.");

                    // check the hero's type and create the hero

                    HeroType heroType;

                    try {
                        heroType = HeroType.valueOf(cmdTokens[1].toUpperCase());
                        gs.getParty().add(HeroFactory.getInstance().createHero(heroType, cmdTokens[2]));
                        System.out.println("Party :" + gs.getParty());
                    } catch (IllegalArgumentException ex) {
                        System.out.println("Wrong hero type! Try again...\n"
                                + "Possible hero types: warrior, mage, priest (any case)");
                    }

                    break;


                case "start":

                    if (!gs.isAdventureStarted()) {
                        System.out.println("We're off on an adventure!");
                        gs.setAdventureStarted(true);
                        gs.addObserver(new MapPrinter());
                        gs.addObserver(new TreasureDiscoverer());
                        gs.addObserver(new MonsterDiscoverer());
                        gs.populateMonsters(4);
                        gs.populateTreasures(5);
                        gs.update();
                    }
                    break;

                case "undo":
                    if (gs.isAdventureStarted()) {
                        System.out.println("Undoing last move");
                        gs.undo();
                    }
                    break;

                case "redo":
                    if (gs.isAdventureStarted()) {
                        System.out.println("Redoing last undo");
                        gs.redo();
                    }
                    break;

                case "attack":
                    if (gs.isAdventureStarted()) {
                        Hero toRemove = null;

                        for (Hero h : gs.getParty())
                            if (h.getName().equals(cmdTokens[1])) {
                                h.attack();
                                if (h.canAttack()) {
                                    System.out.println("Hero hp left: " + h.getHP());
                                    System.out.println("Monster hp left: " + h.getTarget().getHP());
                                    if (h.getHP() <= 0)
                                        toRemove = h;
                                    if (h.getTarget().getHP() <= 0) {
                                        System.out.println("Monster " + h.getTarget().getName() + " has been vanquished !");
                                        gs.removeMonster(h.getTarget());
                                        gs.update();
                                    }
                                }
                            }

                        if (toRemove != null) {
                            gs.removeHero(toRemove);
                            System.out.println("Hero " + toRemove.getName() + " died !");
                            gs.update();
                            if (gs.getParty().size() == 0) {
                                System.out.println("All heroes died ! You lost !");
                                sc.close();
                                System.exit(0);
                            }

                        }

                        if (gs.getMonsters().size() == 0) {
                            System.out.println("You won !");
                            sc.close();
                            System.exit(0);
                        }
                    }
                    break;

                case "move":

                    if (gs.isAdventureStarted()) {

                        if (cmdTokens.length < 3) {
                            System.out.println("Not enough parameters..!\n"
                                    + Main.helpMessage());
                            break;
                        }

                        Direction dir = null;

                        switch (cmdTokens[2]) {
                            case "right":
                                dir = Direction.E;
                                break;
                            case "left":
                                dir = Direction.W;
                                break;
                            case "up":
                                dir = Direction.N;
                                break;
                            case "down":
                                dir = Direction.S;
                                break;
                            default:
                                System.out.println("Wrong direction! Try again...");
                        }

                        for (Hero h : gs.getParty())
                            if (h.getName().equals(cmdTokens[1])) {

                                h.setTarget(null);
                                MoveCommand mc = new MoveCommand(h, dir);
                                gs.executeCommand(mc);

                                System.out.println("Found hero " + h.getName());
                            }
                    } else {
                        System.out.println("First start the adventure, than move the heroes!");
                    }

                    break;

                case "stop":
                    if (gs.isAdventureStarted()) {
                        System.out.println("Adventure ended");
                    }

                    sc.close();

                    System.exit(0);

                default:
                    System.out.println("try again...\n" + Main.helpMessage());
            }
        }
    }
}