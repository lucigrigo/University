package com.luciangrigore;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

/**
 * Takes the input and calls the RB and KMP algorithms to search
 * for matches of given pattern into given text.
 */
class MatchingAdministrator {

    /**
     * Runs a given test from the input file
     * and writes the result to given output path.
     *
     * @param inputPath  input file
     * @param outputPath output file
     */
    void runAllTests(final String inputPath,
                     final String outputPath) {
        if (inputPath == null || outputPath == null) {
            System.out.println("Invalid arguments!");
            return;
        }
        File inputFile = new File(inputPath);
        String pattern = "";
        String text = "";

        try {
            Scanner scanner = new Scanner(inputFile);
            pattern = scanner.next();
            text = scanner.next();
            scanner.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(2);
        }

        RabinKarp rabinKarp = new RabinKarp();
        KnuthMorrisPratt knuthMorrisPratt = new KnuthMorrisPratt();

        long startTime = System.nanoTime();
        List<Integer> rabinKarpResult =
                rabinKarp.search(Arrays.copyOf(text.toCharArray(), text.length()),
                        Arrays.copyOf(pattern.toCharArray(), pattern.length()));
        long endTime = System.nanoTime();
        displayResult("Rabin-Karp", (endTime - startTime),
                rabinKarpResult, outputPath);
        ;

        startTime = System.nanoTime();
        List<Integer> knuthMorrisPrattResult =
                knuthMorrisPratt.search(Arrays.copyOf(text.toCharArray(), text.length()),
                        Arrays.copyOf(pattern.toCharArray(), pattern.length()));
        endTime = System.nanoTime();
        displayResult("Knuth-Morris-Pratt", (endTime - startTime),
                knuthMorrisPrattResult, outputPath);
    }

    /**
     * Searches given pattern into given text.
     *
     * @param pattern given pattern
     * @param text    given text
     */
    void runOneTest(final String pattern,
                    final String text) {
        if (pattern == null || text == null) {
            System.out.println("Invalid arguments!");
            return;
        }

        RabinKarp rabinKarp = new RabinKarp();
        KnuthMorrisPratt knuthMorrisPratt = new KnuthMorrisPratt();

        long startTime = System.nanoTime();
        List<Integer> rabinKarpResult =
                rabinKarp.search(Arrays.copyOf(text.toCharArray(), text.length()),
                        Arrays.copyOf(pattern.toCharArray(), pattern.length()));
        long endTime = System.nanoTime();
        displayResult("Rabin-Karp", (endTime - startTime),
                rabinKarpResult, null);

        startTime = System.nanoTime();
        List<Integer> knuthMorrisPrattResult =
                knuthMorrisPratt.search(Arrays.copyOf(text.toCharArray(), text.length()),
                        Arrays.copyOf(pattern.toCharArray(), pattern.length()));
        endTime = System.nanoTime();
        displayResult("Knuth-Morris-Pratt", (endTime - startTime),
                knuthMorrisPrattResult, null);
    }

    /**
     * Writes algorithms' results to a file or prints them on screen.
     *
     * @param algorithmName name of the applied algorithm
     * @param duration      duration (in nanoseconds)
     * @param matches       list of matches (can be empty)
     * @param outputPath    output file to write to (can be null)
     */
    private void displayResult(final String algorithmName,
                               long duration,
                               final List<Integer> matches,
                               final String outputPath) {
        if (outputPath == null) {
            System.out.println("Algorithm " + algorithmName
                    + " took " + duration + " nanoseconds\n"
                    + "to search given pattern in the " + "given text.");
            if (matches.isEmpty()) {
                System.out.println("No matches found!");
            } else {
                System.out.println("Matches found at index(es):");
                int match = 1;
                for (Integer integer : matches) {
                    System.out.println("\tmatch " + match++ + " at " + integer);
                }
            }
        } else {
            File outputFile = new File(outputPath);
            try {
                FileWriter fileWriter = new FileWriter(outputFile);
                StringBuilder stringBuilder = new StringBuilder();
                stringBuilder.append("Algorithm ")
                        .append(algorithmName)
                        .append(" took ")
                        .append(duration)
                        .append(" nanosec\nto search given pattern in the ")
                        .append("given text.\n");
                if (matches.isEmpty()) {
                    stringBuilder.append("No matches found!\n");
                } else {
                    stringBuilder.append("Matches found at index(es):\n");
                    int match = 1;
                    for (Integer integer : matches) {
                        stringBuilder.append("\tmatch ")
                                .append(match++)
                                .append(" at ")
                                .append(integer);
                    }
                }
                fileWriter.write(stringBuilder.toString());
                fileWriter.flush();
                fileWriter.close();
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(2);
            }
        }
    }
}
