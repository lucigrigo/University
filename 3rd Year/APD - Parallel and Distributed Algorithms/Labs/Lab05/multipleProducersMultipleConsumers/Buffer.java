package multipleProducersMultipleConsumers;
/**
 * @author cristian.chilipirea
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
