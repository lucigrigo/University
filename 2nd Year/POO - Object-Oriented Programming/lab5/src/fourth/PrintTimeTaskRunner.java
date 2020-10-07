package fourth;

import first.Task;
import third.Strategy;

import java.text.SimpleDateFormat;
import java.util.Calendar;

public class PrintTimeTaskRunner extends AbstractTaskRunner{

    public PrintTimeTaskRunner(Strategy strategy) {
        super(strategy);
    }

    @Override
    protected void afterExecution(Task task) {
        Calendar cal = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
        System.out.println(sdf.format(cal.getTime()));
    }
}
