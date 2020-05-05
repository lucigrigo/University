package fourth;

import first.Task;
import third.Strategy;

public class CounterTaskRunner extends AbstractTaskRunner{
    private static int nr = 0;

    public CounterTaskRunner(Strategy strategy) {
        super(strategy);
    }

    @Override
    protected void afterExecution(Task task) {
        nr++;
    }

    public int getCounter(){
        return nr;
    }
}
