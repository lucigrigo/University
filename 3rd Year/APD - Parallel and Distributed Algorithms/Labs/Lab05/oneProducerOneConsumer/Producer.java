package oneProducerOneConsumer;
/**
 * @author gabriel.gutu@upb.ro
 * 
 */
public class Producer implements Runnable {
	Buffer buffer;

	Producer(Buffer buffer) {
		this.buffer = buffer;
	}

	@Override
	public void run() {
		for (int i = 0; i < Main.N; i++) {
			buffer.put(i);
		}
	}

}
