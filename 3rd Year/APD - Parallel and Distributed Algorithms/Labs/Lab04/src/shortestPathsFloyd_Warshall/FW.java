package shortestPathsFloyd_Warshall;

public class FW implements Runnable {
    int thread_id;
    int no_steps;

    FW(int i, int n_steps) {
        thread_id = i;
        no_steps = n_steps;
    }

    @Override
    public void run() {
        for(int k = 0; k < no_steps; ++k) {
            for(int i = 0; i < no_steps; ++i) {
                Main.graph[i][thread_id] = Math.min(Main.graph[i][k] +
                                                    Main.graph[k][thread_id],
                                                    Main.graph[i][thread_id]);
            }

            // punem o bariera pentru sincronizarea thread-urilor
            try {
                Main.barrier.await();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
