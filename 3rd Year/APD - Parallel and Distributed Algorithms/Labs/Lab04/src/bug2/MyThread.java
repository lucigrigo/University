package bug2;
/**
 * @author cristian.chilipirea
 * 
 *         Why does this code not block? We took the same lock twice!
 */
public class MyThread implements Runnable {
	static int i;

	@Override
	public void run() {
		synchronized (this) { // in Java it works -- fixed (by doing nothing)
			synchronized (this) {
				i++;
			}
		}
	}
}
