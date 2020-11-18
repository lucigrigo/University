package parallelTree;

import java.util.concurrent.CyclicBarrier;

public class Main {
    static int N_ITERATIONS = 100;
    private static CyclicBarrier bar;

    public static void main(String[] args) {
        // just to make sure i'm in the right working directory
        System.out.println("Working Directory = " + System.getProperty("user.dir"));
        bar = new CyclicBarrier(3);

        Thread[] threads = new Thread[3];
        System.out.println("Parallel tree problem");

        for (int j = 0; j < N_ITERATIONS; j++) {
            TreeNode tree = new TreeNode(1);
            threads[0] = new Thread(new ReadTreePart(tree, "treePart1.txt", bar));
            threads[1] = new Thread(new ReadTreePart(tree, "treePart2.txt", bar));
            threads[2] = new Thread(new VerifyTree(tree, bar));

            for (int i = 0; i < 3; i++) {
                threads[i].start();
            }

            for (int i = 0; i < 3; i++) {
                try {
                    threads[i].join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}