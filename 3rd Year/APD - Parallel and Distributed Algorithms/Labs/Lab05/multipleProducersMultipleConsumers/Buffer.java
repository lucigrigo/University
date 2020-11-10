package multipleProducersMultipleConsumers;

import java.util.concurrent.Semaphore;

/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	int a;
    Semaphore prod = new Semaphore(1);
    Semaphore cons = new Semaphore(0);

	void put(int value) {
        try {
            prod.acquire();
            a = value;
            cons.release();
        } catch (Exception e) {
            e.printStackTrace();
        }
	}

	int get() {
        int val = Integer.MAX_VALUE;
        try {
            cons.acquire();
            val = a;
            prod.release();
        } catch(Exception e) {
            e.printStackTrace();
        }
        return val;
	}
}
