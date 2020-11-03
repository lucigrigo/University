package hello_cores;

public class Main {
	public static void main(String[] args) {
        int cores = Runtime.getRuntime().availableProcessors();

        Thread[] threads = new Thread[cores];
        for(int i = 0; i < cores; ++i) {
            threads[i] = new Thread(new HelloThread(i));
            threads[i].start();
        }
    }
}
