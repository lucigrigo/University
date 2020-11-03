package bug5;
/**
 * @author cristian.chilipirea
 * 
 *         Solve the dead-lock
 */
public class MyThreadB implements Runnable {

	@Override
	public void run() {
		synchronized (Main.lockB) {
			for (int i = 0; i < Main.N; i++)
				Main.valueB++;
			synchronized (Main.lockA) {
				for (int i = 0; i < Main.N; i++)
					Main.valueA++;
			}
		}
	}
}
