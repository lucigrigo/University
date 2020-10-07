package third;

import second.Container;
import second.Queue;
import second.Stack;

public class ContainerFactory implements IFactory {
    public static final ContainerFactory INSTANCE = new ContainerFactory();

    public ContainerFactory() {
    }

    public Container createContainer(Strategy strategy) {
        Container container;
        if(strategy == Strategy.FIFO) {
            container = new Queue();
        } else {
            container = new Stack();
        }
        return container;
    }
}