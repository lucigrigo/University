import java.util.HashMap;
import java.util.concurrent.*;

public class App extends Thread {

    static ConcurrentHashMap<Integer, String> l = new ConcurrentHashMap<Integer, String>();

    public void run() {

        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            System.out.println("Child Thread going to add element");
        }

        l.put(103, "D");
        System.out.println("am terminat");
    }

    public static void main(String[] args) throws Exception {
        l.put(100, "A");
        l.put(101, "B");
        l.put(102, "C");
        App t = new App();
        t.start();

        for (Object o : l.entrySet()) {
            Object s = o;
            System.out.println(s);
            Thread.sleep(1000);
        }
        System.out.println(l);
    }
}
