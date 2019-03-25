package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;

public class Main {

    public static void main(String[] args) {
//        Path path = FileSystems.getDefault().getPath("WorkingDirectoryFile.txt");
//        Path path = FileSystems.getDefault().getPath("Files", "SubdirectoryFile.txt");
//        Path path = Paths.get("/Users/grigorelucian/Documents/CompleteJavaMasterclassUDEMY/outThere.txt");
//        printFile(path);

        /*
        Path path = Paths.get("../outThere.txt");
        System.out.println(path.toAbsolutePath());
        printFile(path);

        //  WRONG PATHS
        Path falsePath = FileSystems.getDefault().getPath("this_file_doesnt_exit.txt");
        System.out.println(falsePath.toAbsolutePath());

        Path path4 = Paths.get("/SmrBibi/NuENimic/Aicea", "acdef", "gucci.txt");
        System.out.println(path4.toAbsolutePath());

        path = FileSystems.getDefault().getPath("Files");
        System.out.println("Exists = " + Files.exists(path));

        System.out.println("Exists = " + Files.exists(path4));
        */

        try {
            //  copy a file
//            Path sourceFile = FileSystems.getDefault().getPath("Examples", "file1.txt");
//            Path copyFile = FileSystems.getDefault().getPath("Examples", "file1Copy.txt");
//            Files.copy(sourceFile, copyFile, StandardCopyOption.REPLACE_EXISTING);

            //  copy a folder
//            sourceFile = FileSystems.getDefault().getPath("Examples", "Dir1");
//            copyFile = FileSystems.getDefault().getPath("Examples", "Dir4");
//            Files.copy(sourceFile, copyFile);

            //  move a file
//            Path sourceFile = FileSystems.getDefault().getPath("Examples", "file1Copy.txt");
//            Path copyFile = FileSystems.getDefault().getPath("Examples", "Dir1", "file1Copy.txt");
//            Files.move(sourceFile, copyFile);

            //  rename a file
//            Path source = FileSystems.getDefault().getPath("Examples", "file1.txt");
//            Path dest = FileSystems.getDefault().getPath("Examples", "file1RENAMED.txt");
//            Files.move(source, dest);

            //  delete a file
//            Path file = FileSystems.getDefault().getPath("Examples", "Dir1", "file1Copy.txt");
//            Files.delete(file);
//            Files.deleteIfExists(file);

            //  create a file / directory
//            Path fileToCreate = FileSystems.getDefault().getPath("Examples", "file2.txt");
//            Files.createFile(fileToCreate);
//            Path dirToCreate = FileSystems.getDefault().getPath("Examples", "Dir4");
//            Files.createDirectory(dirToCreate);
//            Path dirToCreate = FileSystems.getDefault().getPath("Examples", "Dir2/Dir3/Dir4/Dir5/Dir6");
//            Files.createDirectories(dirToCreate);

            //  metadata
            Path filePath = FileSystems.getDefault().getPath("Examples/Dir1/file1.txt");
            long size = Files.size(filePath);
            System.out.println("Size = " + size);
            System.out.println("Last modified = " + Files.getLastModifiedTime(filePath));

            BasicFileAttributes bfa = Files.readAttributes(filePath, BasicFileAttributes.class);
            System.out.println("SIZE = " + bfa.size());
            System.out.println("LAST MODIFIED = " + bfa.lastModifiedTime());
            System.out.println("CREATED = " + bfa.creationTime());
            System.out.println("IS DIRECTORY = " + bfa.isDirectory());
            System.out.println("IS REGULAR FILE = " + bfa.isRegularFile());
        } catch (IOException ioe) {
            System.out.println(ioe.getMessage());
        }

    }

    private static void printFile(Path path) {
        try (BufferedReader bufferedReader = Files.newBufferedReader(path)) {
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }

}
