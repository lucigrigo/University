package philosophersProblem;

/**
 * @author cristian.chilipirea
 * 
 */
public class Philosopher implements Runnable {
	Object leftFork, rightFork;
	int id;

	public Philosopher(int id, Object leftFork, Object rightFork) {
		this.leftFork = leftFork;
		this.rightFork = rightFork;
		this.id = id;
	}

	private void sleep() {
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void run() {
        /* inversam ordinea in care tacamurile sunt luate pentru filozofii
        asezati pe indici pari -- metoda lui Dijkstra
        */
        if(id % 2 == 0) {
            synchronized (rightFork) {
                sleep(); // delay added to make sure the dead-lock is visible
                synchronized (leftFork) {
                    System.out.println("Philosopher " + id + " is eating");
                }
            }
        } else {
            synchronized (leftFork) {
                sleep(); // delay added to make sure the dead-lock is visible
                synchronized (rightFork) {
                    System.out.println("Philosopher " + id + " is eating");
                }
            }
        }
	}
}
