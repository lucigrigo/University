import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class MySearchThread implements Runnable {
    private int id;

    MySearchThread(int i) {
        id = i;
    }

    @Override
    public void run() {
        int l = id * Main.NO_ELEMS / Main.NO_THREADS;
        int r = Math.min((id + 1) * Main.NO_ELEMS / Main.NO_THREADS, Main.NO_ELEMS - 1);

        while (l <= r && !Main.found) {
            System.out.println("Thread " + id + " l = " + l + " r = " + r);
            if (Main.v[l] == Main.x && !Main.found) { // found on the left index
                try {
                    Main.writing_sem.acquire();
                    if (!Main.found) {
                        Main.found = true;
                        Main.index = l;
                        Main.thread_index = id;
                    }
                    Main.writing_sem.release();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                System.out.println("Thread " + id + " STANGA " + Main.found);
            } else if (Main.v[r] == Main.x && !Main.found) { // found on the right index

                try {
                    Main.writing_sem.acquire();
                    if (!Main.found) {
                        Main.found = true;
                        Main.index = r;
                        Main.thread_index = id;
                    }
                    Main.writing_sem.release();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                System.out.println("Thread " + id + " DREAPTA " + Main.found);
            } else if (Main.x > Main.v[l] && Main.x < Main.v[r] && !Main.found) { // update interest area
                try {
                    Main.writing_sem.acquire();
                    if (!Main.found) {
                        Main.end_interest = r;
                        Main.start_interest = l;
                    }
                    Main.writing_sem.release();
                } catch (Exception e) {
                    e.printStackTrace();
                }

            }

            // waiting for all threads to do these checks
            try {
                Main.barrier.await();
            } catch (Exception e) {
                e.printStackTrace();
            }

            // updating left and right indexes according to interest area
            int no_elems = Main.end_interest - Main.start_interest + 1;
            l = Main.start_interest + id * no_elems / Main.NO_THREADS;
            r = Main.start_interest + Math.min(no_elems, (id + 1) * no_elems / Main.NO_THREADS) - 1;
        }
    }
}
