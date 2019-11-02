import first.*;
import second.*;
import third.*;
import fourth.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    private static final int TASK_NO = 6;

    private static Task[] taskList;

    private static void test1() {
        taskList = new Task[TASK_NO];

        taskList[0] = new OutTask("First message task");
        taskList[1] = new RandomOutTask();
        taskList[2] = new CounterOutTask();
        taskList[3] = new OutTask("Second message task");
        taskList[4] = new CounterOutTask();
        taskList[5] = new RandomOutTask();

        for (Task task : taskList) {
            task.execute();
        }
    }

    static private void testContainer(Strategy strategy) {
        Container container = ContainerFactory.INSTANCE.createContainer(strategy);

        for (Task task : taskList) {
            container.push(task);
        }

        System.out.println("Testing order: " + strategy.toString());

        while (!container.isEmpty()) {
            container.pop().execute();
        }

        System.out.println();
    }

    private static void test2_3() {
        testContainer(Strategy.LIFO);
        testContainer(Strategy.FIFO);
    }

    private static void testTaskRunner(AbstractTaskRunner taskRunner) {
        System.out.println("Testing: " + taskRunner);

        for (Task task : taskList) {
            taskRunner.addTask(task);
        }

        taskRunner.executeAll();

        System.out.println();
    }

    private static void test4_5() {
        testTaskRunner(new PrintTimeTaskRunner(Strategy.LIFO));

        CounterTaskRunner counterTaskRunner = new CounterTaskRunner(Strategy.FIFO);

        testTaskRunner(counterTaskRunner);
        System.out.println("#Executed tasks: " + counterTaskRunner.getCounter());

        RedoBackTaskRunner redoTaskRunner = new RedoBackTaskRunner(Strategy.LIFO);

        testTaskRunner(redoTaskRunner);
        System.out.println("Reexecuting: ");
        redoTaskRunner.redo();
    }

    public static void main(String[] args) {
        test1();
        System.out.println("------\tTEST EX 1 FINISHED\t------");

        test2_3();
        System.out.println("------\tTEST EX 2 SI EX 3 FINISHED\t------");

        test4_5();
        System.out.println("------\tTEST EX 4 SI EX 5 FINISHED\t------");
    }
}