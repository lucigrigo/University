package oneProducerOneConsumer;
/**
 * @author gabriel.gutu@upb.ro
 *
 */
public class Buffer {
    int a;
    /*
    --------- Rezolvarea este in exemplul cu mai multi consumatori si producatori.
    */
    
	void put(int value) {
		a = value;
	}

	int get() {
		return a;
	}
}
