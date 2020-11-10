package multipleProducersMultipleConsumers;
/**
 * @author cristian.chilipirea
 * 
 *         DO NOT MODIFY
 */
public class Main {
	public static final int N = 100000;
	public static final int N_CONSUMERS = 5;
	public static final int N_PRODUCERS = 3;
	public static int[] results = new int[N];

	public static void main(String[] args) {
		Buffer buffer = new Buffer();

		Thread threads[] = new Thread[N_CONSUMERS + N_PRODUCERS];
		for (int i = 0; i < N_PRODUCERS; i++)
			threads[i] = new Thread(new Producer(buffer, i));
		for (int i = N_PRODUCERS; i < N_CONSUMERS + N_PRODUCERS; i++)
			threads[i] = new Thread(new Consumer(buffer, i - N_PRODUCERS));

		for (int i = 0; i < N_CONSUMERS + N_PRODUCERS; i++)
			threads[i].start();
		for (int i = 0; i < N_CONSUMERS + N_PRODUCERS; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		for (int i = 0; i < N; i++) {
			if (results[i] != N_PRODUCERS) {
				System.out.println("FAILED, the produced data does not match the consumed data");
				System.exit(1);
			}
		}
		System.out.println("CORRECT");
	}
}
/* DO NOT MODIFY */