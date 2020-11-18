package synchronizedSortedList;

import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;

public class Sort extends Thread {
    private final List<Integer> list;
    private Semaphore sem;

    public Sort(List<Integer> list, Semaphore s) {
        super();
        this.list = list;
        this.sem = s;
    }

    @Override
    public void run() {
        try {
            sem.acquire(3);
            Collections.sort(list);
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}
