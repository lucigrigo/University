package bugConcurrentHashMap;

import java.util.Map.Entry;
import java.util.concurrent.ConcurrentHashMap;

/**
 *         DO NOT MODIFY
 */
public class Main {
	public static final int N = 100000;
	private final static int N_ITERATIONS = 100;

	public static void main(String[] args) {
		Thread[] threads = new Thread[2];
		boolean sw = true;
		System.out.println("Concurrent HashMap with Bug");
		
		for (int j = 0; j < N_ITERATIONS; j++) {
			MyThread.hashMap = new ConcurrentHashMap<>();

			for (int i = 0; i < 2; i++) {
				threads[i] = new Thread(new MyThread(i));
				threads[i].start();
			}

			for (int i = 0; i < 2; i++) {
				try {
					threads[i].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			
			for (Entry<Integer, Integer> entry : MyThread.hashMap.entrySet()) {
				if(entry.getKey() * 5 != entry.getValue()) {
					System.out.println("key " + entry.getKey() + " has incorrect value " + entry.getValue());
					sw = false;
				}
			}
		}
		if (sw)
			System.out.println("Correct");
	}
}
