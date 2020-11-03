package shortestPathsFloyd_Warshall;

import java.util.concurrent.CyclicBarrier;

/**
 * @author cristian.chilipirea
 *
 */
public class Main {
    static int M = 9;
    static int graph[][] = { { 0, 1, M, M, M }, 
                      { 1, 0, 1, M, M }, 
                      { M, 1, 0, 1, 1 }, 
                      { M, M, 1, 0, M },
                      { M, M, 1, M, 0 } };

    static CyclicBarrier barrier;
	public static void main(String[] args) {
		// Parallelize me (You might want to keep the original code in order to compare)
		// for (int k = 0; k < 5; k++) { // nu se poate paraleliza
		// 	for (int i = 0; i < 5; i++) { // se poate paraleliza
		// 		for (int j = 0; j < 5; j++) { // se poate paraleliza -> pe aceasta o vom paraleliza
		// 			graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
		// 		}
		// 	}
        // }
        int n_threads = 5; // number of cols / rows of given graph
        Thread[] threads = new Thread[n_threads];
        barrier = new CyclicBarrier(n_threads);

        for(int i = 0; i < n_threads; ++i) {
            threads[i] = new Thread(new FW(i, 5));
            threads[i].start();
        }

        try {
            for(int i = 0; i < n_threads; ++i) {
                threads[i].join();
            }
        } catch(Exception e) {
            e.printStackTrace();
        }

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(graph[i][j] + " ");
			}
			System.out.println();
		}
	}
}
