package first;

import java.util.Random;

public class RandomOutTask implements Task {
    private int number;

    public RandomOutTask() {
        Random rand = new Random();
        number = rand.nextInt();
    }

    @Override
    public void execute() {
        System.out.println("Random number " +number);
    }
}
