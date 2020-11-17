package synchronizationProblem;

import java.util.concurrent.atomic.AtomicInteger;

public class MyThread implements Runnable {
	private final int id;
	public static AtomicInteger value;

	public MyThread(int id) {
		this.id = id;
	}

	@Override
	public void run() {
		if (id == 0) {
			for (int i = 0; i < Main.N; i++) {
				value.addAndGet(3);
			}
		} else {
			for (int i = 0; i < Main.N; i++) {
				value.addAndGet(3);
			}
		}
	}
}
