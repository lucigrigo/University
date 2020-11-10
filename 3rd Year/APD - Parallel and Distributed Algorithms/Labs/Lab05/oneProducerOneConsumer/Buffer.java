package oneProducerOneConsumer;
/**
 * @author gabriel.gutu@upb.ro
 *
 */
public class Buffer {
	int a;

	void put(int value) {
		a = value;
	}

	int get() {
		return a;
	}
}
