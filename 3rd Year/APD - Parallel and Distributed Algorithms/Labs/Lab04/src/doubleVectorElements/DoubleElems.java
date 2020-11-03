package doubleVectorElements;

public class DoubleElems implements Runnable {
    int thread_id;
    int no_elems;
    int no_threads;

    DoubleElems(int id, int n, int p) {
        thread_id = id;
        no_elems = n;
        no_threads = p;
    }

    @Override
    public void run() {
        int start = (int) (thread_id * (double) no_elems / no_threads);
        int end = (int) Math.min((thread_id + 1) * (double) no_elems / no_threads, no_elems);

        for(int i = start; i < end; ++i) {
            Main.v[i] *= 2;
        }
    }
}
