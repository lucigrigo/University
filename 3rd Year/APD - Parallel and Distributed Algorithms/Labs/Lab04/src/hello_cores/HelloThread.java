package hello_cores;

public class HelloThread implements Runnable {
    int thread_id;

    HelloThread(int i) {
        thread_id = i;
    }

    @Override
    public void run() {
        System.out.println("Hello from thread " + thread_id);
    }
}
