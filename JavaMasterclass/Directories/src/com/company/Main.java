package com.company;

import java.io.File;
import java.io.IOException;
import java.nio.file.*;

public class Main {

    public static void main(String[] args) {

        //  REGULAR WAY
//        DirectoryStream.Filter<Path> filter = new DirectoryStream.Filter<Path>() {
//            public boolean accept(Path path) throws IOException {
//                return Files.isRegularFile(path);
//            }
//        };

        // LAMBDA EXPRESSION
        DirectoryStream.Filter<Path> filter = p -> Files.isRegularFile(p);

//        Path directory = FileSystems.getDefault().getPath("FileTree/Dir2");
        Path directory = FileSystems.getDefault().getPath("FileTree" + File.separator + "Dir2");

//        try(DirectoryStream<Path> contents = Files.newDirectoryStream(directory)) {
//        try (DirectoryStream<Path> contents = Files.newDirectoryStream(directory, "*.txt")) {
        try (DirectoryStream<Path> contents = Files.newDirectoryStream(directory, filter)) {
            for (Path file : contents) {
                System.out.println(file.getFileName());
            }
        } catch (IOException | DirectoryIteratorException e) {
            System.out.println(e.getMessage());
        }

        //  the file separator specific for each OS
        String separator = File.separator;
        System.out.println(separator);
        separator = FileSystems.getDefault().getSeparator();
        System.out.println(separator);

        try {
            //  create a temporary file
            Path tempFile = Files.createTempFile("myapp", ".appext");
            System.out.println("Temporary file path  = " + tempFile.toAbsolutePath());
        } catch (IOException ioe) {
            System.out.println(ioe.getMessage());
        }

        //  get system's filestores
        Iterable<FileStore> stores = FileSystems.getDefault().getFileStores();
        for (FileStore store : stores) {
            System.out.println("Volume name/Drive letter = " + store);
            System.out.println("file store = " + store.name());
        }
        //  root directories
        System.out.println("========\nROOT PATHS\n========");
        Iterable<Path> rootPaths = FileSystems.getDefault().getRootDirectories();
        for (Path path : rootPaths) {
            System.out.println(path);
        }


        System.out.println("\n\n=============WALKING TREE FOR DIR2===============\n\n");
        Path dir2Path = FileSystems.getDefault().getPath("FileTree" + File.separator + "Dir2");
        try {
            Files.walkFileTree(dir2Path, new PrintNames());
        } catch (IOException ioe) {
            System.out.println(ioe.getMessage());
        }


        System.out.println("\n\n============COPYING DIR2 TO DIR4/DIR2COPY===============\n\n");
        Path sourcePath = FileSystems.getDefault().getPath("FileTree", "Dir2");
        Path destPath = FileSystems.getDefault().getPath("FileTree", "Dir4/Dir2Copy");
        try {
            Files.walkFileTree(sourcePath, new CopyFiles(sourcePath, destPath));
        } catch (IOException ioe) {
            System.out.println(ioe.getMessage());
        }
    }
}
