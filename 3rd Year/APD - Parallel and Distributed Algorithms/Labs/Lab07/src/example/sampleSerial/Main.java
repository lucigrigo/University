package example.sampleSerial;

import java.io.File;

public class Main {
    public static void show(String path) {
        File file = new File(path);
        if (file.isFile()) {
            System.out.println(file.getPath());
        } else if (file.isDirectory()) {
            var files = file.listFiles();
            if (files != null) {
                for (var f : files) {
                    show(f.getPath());
                }
            }
        }
    }

    public static void main(String[] args) {
        show("files");
    }
}
