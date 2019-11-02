package fourth;

import first.Task;
import second.Container;
import third.ContainerFactory;
import third.Strategy;

import java.util.ArrayList;

public class RedoBackTaskRunner extends AbstractTaskRunner {
    private Container container;

    public RedoBackTaskRunner(Strategy strategy) {
        super(strategy);
        ContainerFactory containerFactory = new ContainerFactory();
        container = containerFactory.createContainer(strategy);
    }

    public void redo() {
        while(!container.isEmpty()) {
            Task lastTask = container.pop();
            lastTask.execute();
        }
    }

    @Override
    protected void afterExecution(Task task) {
        container.push(task);
    }
}
