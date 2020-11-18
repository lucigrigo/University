package synchronizedSortedList;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;

public class Main {
    private final static int N_ITERATIONS = 100;
    private final static int NUMBER_OF_THREADS = 4;
    private static Semaphore sem;

    public static void main(String[] args) {
        // am avut ceva probleme cu working directory, de aia am pus afisarea asta aici
        System.out.println("Working Directory = " + System.getProperty("user.dir"));

        sem = new Semaphore(0);
        Thread[] threads = new Thread[4];
        boolean sw = true;

        for (int i = 0; i < N_ITERATIONS; i++) {
            List<Integer> list = Collections.synchronizedList(new ArrayList<>());

            threads[0] = new Reader("elemente1.txt", list, sem);
            threads[1] = new Reader("elemente2.txt", list, sem);
            threads[2] = new Reader("elemente3.txt", list, sem);
            threads[3] = new Sort(list, sem);

            for (int j = 0; j < NUMBER_OF_THREADS; j++) {
                threads[j].start();
            }

            for (int j = 0; j < NUMBER_OF_THREADS; j++) {
                try {
                    threads[j].join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            for (int j = 0; j < list.size() - 1; j++) {
                if (list.get(j) > list.get(j + 1)) {
                    sw = false;
                    System.out.println("Incorrect result: " + list.get(j) + " > " +  list.get(j + 1));
                    break;
                }
            }
        }

        if (sw) {
            System.out.println("Correct");
        }
    }
}
