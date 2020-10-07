package commands;

public interface Command {
    void undo();

    void execute();
}
