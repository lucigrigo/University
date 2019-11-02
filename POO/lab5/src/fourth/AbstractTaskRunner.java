package fourth;

import first.Task;
import second.Container;
import third.ContainerFactory;
import third.Strategy;

public abstract class AbstractTaskRunner {
	private Container container;

    protected AbstractTaskRunner(Strategy strategy) {
        container = ContainerFactory.INSTANCE.createContainer(strategy);
    }

    public void addTask(Task task) {
        container.push(task);
    }

    public void executeAll() {
        while (!container.isEmpty()) {
            Task task = container.pop();

            task.execute();

            afterExecution(task);
        }
    }

    protected abstract void afterExecution(Task task);
}
