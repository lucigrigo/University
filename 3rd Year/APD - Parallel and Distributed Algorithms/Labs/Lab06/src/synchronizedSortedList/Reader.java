package synchronizedSortedList;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class Reader extends Thread {
    private final String filename;
    private final List<Integer> list;
    private Semaphore sem;

    public Reader(String filename, List<Integer> list, Semaphore s) {
        super();
        this.filename = filename;
        this.list = list;
        this.sem = s;
    }

    @Override
    public void run() {
        try {
            Scanner scanner = new Scanner(new File(filename));
            while (scanner.hasNextInt()) {
                list.add(scanner.nextInt());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        try {
            sem.release();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
