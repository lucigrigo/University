package commands;

import entities.Hero;
import game.GameState;

public class MoveCommand implements Command {

    private Hero.Direction d;
    private Hero h;

    public MoveCommand(Hero h, Hero.Direction d) {
        this.h = h;
        this.d = d;
    }

    @Override
    public void undo() {
        // TODO Auto-generated method stub
        if (d == Hero.Direction.N) {
            h.move(Hero.Direction.S);
        }
        if (d == Hero.Direction.S) {
            h.move(Hero.Direction.N);
        }
        if (d == Hero.Direction.E) {
            h.move(Hero.Direction.W);
        }
        if (d == Hero.Direction.W) {
            h.move(Hero.Direction.E);
        }
    }

    @Override
    public void execute() {
        // TODO Auto-generated method stub
        if (d == Hero.Direction.E) {
            h.move(Hero.Direction.E);
        }
        if (d == Hero.Direction.W) {
            h.move(Hero.Direction.W);
        }
        if (d == Hero.Direction.S) {
            h.move(Hero.Direction.S);
        }
        if (d == Hero.Direction.N) {
            h.move(Hero.Direction.N);
        }
    }

    // TODO implement the move command
    /*  - MoveCommand(Hero, Direction)
        - void undo()
        - void execute()
        - maybe helper method for undo ?
    */
}
