import java.util.concurrent.Semaphore;
import java.util.Random;
import java.util.concurrent.CyclicBarrier;
import MySearchThread;

/**
 * DISCLAIMER:
 * La unele rulari, nu mi se opreste din rulare, desi gaseste valoarea in vector.
 * Am incercat in mai multe feluri sa rezolv aceasta problema, dar nu am reusit.
 * Am lasat niste printari in MySearchThread care arata ca thread-urile cauta doar
 * in zona de interes si ca intr-un final un thread gaseste valoarea cautata, dar
 * programul nu se opreste din executare.
 */

public class Main {
    // nr de threaduri si de elemente in vector
    public static int NO_THREADS = 4;
    public static int NO_ELEMS = 100000;

    // variabile folosite pentru cautare de fiecare thread
    public static boolean found; // daca s-a gasit valoarea cautata
    public static int start_interest, end_interest; // indici pt zona de interes
    public static int[] v; // vectorul de elemente
    public static int x; // valoarea cautata
    public static int index = -1;
    public static CyclicBarrier barrier;
    public static int thread_index = -1;
    public static Semaphore writing_sem;

    public static void main(String[] args) {
        // initializare elemente in vector
        v = new int[NO_ELEMS];
        for(int i = 0; i < NO_ELEMS; ++i)
            v[i] = i;
        
        // initializare valoarea cautata
        Random r = new Random();
        x = Math.abs(r.nextInt()) % NO_ELEMS;
        start_interest = 0;
        end_interest = NO_ELEMS;
        found = false;

        // initializare bariera & semafor
        barrier = new CyclicBarrier(NO_THREADS);
        writing_sem = new Semaphore(1);

        // initializare thread-uri
        Thread[] threads = new Thread[NO_THREADS];
        for(int i = 0; i < NO_THREADS; ++i) {
            threads[i] = new Thread(new MySearchThread(i));
        }

        System.out.println("Pornire cautare paralela ...");
        // pornire thread-uri
        for(int i = 0; i < NO_THREADS; ++i) {
            threads[i].start();
        }

        // asteptare oprire thread-uri
        try {
            for(int i = 0; i < NO_THREADS; ++i) {
                threads[i].join();
            }
        } catch(Exception e) {
            e.printStackTrace();
        }

        if(index == -1) {
            System.out.println("[EROARE] Valoarea nu a fost gasita!");
        } else {
            System.out.println("Valoarea " + x + " a fost gasita in vector la pozitia " + index +
            " de catre thread-ul #" + thread_index + "\n");
        }
    }
}