package bug4;
/**
 * @author cristian.chilipirea
 *
 *         Why doesn't this program end? (Hint: volatile)
 */
public class Main extends Thread {
	volatile boolean keepRunning = true; // fixed

	public void run() {
		long count = 0;
		while (keepRunning) {
			count++;
		}

		System.out.println("Thread terminated." + count);
	}

	public static void main(String[] args) throws InterruptedException {
		Main t = new Main();
		t.start();
		Thread.sleep(1000);
		t.keepRunning = false;
		System.out.println("keepRunning set to false.");
	}
}
