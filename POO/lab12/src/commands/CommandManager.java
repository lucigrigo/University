package commands;

import java.util.Stack;

public class CommandManager {

    // TODO
    /* - void undo()
       - void redo()
       - void executeCommand(Command c)
       - maybe check if undo() and redo() are available ?
             -> check GameState class, see the errors
       - keep track of the commands somehow
    */
    private Stack<Command> commands = new Stack<>();

    public void executeCommand(Command c) {
        c.execute();
        commands.push(c);
    }

    public void undo() {
        Command lastCommand = commands.pop();
        lastCommand.undo();
    }

    public void redo() {
        Command lastCommand = commands.peek();
        lastCommand.execute();
    }

    public boolean isRedoAvailable() {
        return commands.isEmpty();
    }

    public boolean isUndoAvailable() {
        return commands.isEmpty();
    }
}
