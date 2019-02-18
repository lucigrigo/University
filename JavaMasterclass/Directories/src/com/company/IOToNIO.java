package com.company;

import java.io.File;
import java.nio.file.Path;

public class IOToNIO {

    public static void main(String[] args) {
        //  conversions from java.io to java.nio and vice-versa
        File file = new File("/Examples/file.txt");
        Path convertedPath = file.toPath();
        System.out.println("Converted path = " + convertedPath);

        File parent = new File("/Examples");
        File resolvedFile = new File(parent, "dir/file4.txt");
        System.out.println("Resolved path = " + resolvedFile);

        resolvedFile = new File("/Examples", "dir/file4.txt");
        System.out.println("Resolved path 2 = " + resolvedFile);

        File workingDirectory = new File("").getAbsoluteFile();
        System.out.println("Working directory = " + workingDirectory.getAbsolutePath());

        System.out.println("=== print Dir2 contents using list() ===");
        File dir2File = new File(workingDirectory, "/FileTree/Dir2");
        String[] dir2Contents = dir2File.list();
        for (int i = 0; i < dir2Contents.length; i++) {
            System.out.println(dir2Contents[i]);
        }

        System.out.println("=== print Dir2 contents using listFiles() ===");
        File[] dir2Files = dir2File.listFiles();
        for (int i = 0; i < dir2Files.length; i++) {
            System.out.println(dir2Files[i].getAbsolutePath());
        }
    }
}
