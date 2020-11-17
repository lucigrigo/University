package multipleProducersMultipleConsumers;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class Buffer {
    BlockingQueue<Integer> q = new ArrayBlockingQueue<>(10);

    void put(int value) {
        try {
            q.put(value);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    int get() {
        try {
            return q.take();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return -1;
    }
}
