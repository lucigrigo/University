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
public class MatchingAdministrator {

  /**
   * Runs a given test from the input file
   * and writes the result to given output path.
   *
   * @param inputPath  input file
   * @param outputPath output file
   */
  void runSingleTest(final String inputPath, final String outputPath) {
    if (inputPath == null || outputPath == null) {
      System.out.println("Invalid arguments!");
      return;
    }

    File inputFile = new File(inputPath);
    String pattern = "";
    String text = "";
    // reading input data from file
    try {
      Scanner scanner = new Scanner(inputFile);

      pattern = scanner.nextLine(); // pattern on first line
      text = scanner.nextLine();    // text on second line

      scanner.close();
    } catch (IOException e) {
      e.printStackTrace();
      System.exit(2);
    }

    RabinKarp rabinKarp = new RabinKarp();
    KnuthMorrisPratt knuthMorrisPratt = new KnuthMorrisPratt();

    // search using Rabin-Karp
    long startTime = System.nanoTime();
    List<Integer> rabinKarpResult = rabinKarp.search(
        Arrays.copyOf(text.toCharArray(), text.length()),
        Arrays.copyOf(pattern.toCharArray(), pattern.length()), false);
    long endTime = System.nanoTime();
    long duration1 = endTime - startTime; // time taken

    // search using Rabin-Karp with inefficient and unsecure hash function
    startTime = System.nanoTime();
    List<Integer> badRKResult = rabinKarp.search(
        Arrays.copyOf(text.toCharArray(), text.length()),
        Arrays.copyOf(pattern.toCharArray(), pattern.length()), true);
    endTime = System.nanoTime();
    long duration3 = endTime - startTime;                  // time taken
    displayBadRKResults(duration1, duration3, outputPath); // display
                                                           // differences
    displayResult("Rabin-Karp (with an efficient hash function)", duration1,
                  rabinKarpResult, outputPath); // displaying results

    // search using Knuth-Morris-Pratt
    startTime = System.nanoTime();
    List<Integer> knuthMorrisPrattResult = knuthMorrisPratt.search(
        Arrays.copyOf(text.toCharArray(), text.length()),
        Arrays.copyOf(pattern.toCharArray(), pattern.length()));
    endTime = System.nanoTime();
    displayResult("Knuth-Morris-Pratt", (endTime - startTime),
                  knuthMorrisPrattResult, outputPath); // displaying results
    long duration2 = endTime - startTime;              // time it took

    // displaying conclusion
    displayConclusion(duration1, duration2, outputPath);
  }

  /**
   * Searches given pattern into given text.
   *
   * @param pattern given pattern
   * @param text    given text
   */
  void runManualTest(final String pattern, final String text) {
    if (pattern == null || text == null) {
      System.out.println("Invalid arguments!");
      return;
    }

    RabinKarp rabinKarp = new RabinKarp();
    KnuthMorrisPratt knuthMorrisPratt = new KnuthMorrisPratt();

    // search using Rabin-Karp
    long startTime = System.nanoTime();
    List<Integer> rabinKarpResult = rabinKarp.search(
        Arrays.copyOf(text.toCharArray(), text.length()),
        Arrays.copyOf(pattern.toCharArray(), pattern.length()), false);
    long endTime = System.nanoTime();
    long duration1 = endTime - startTime; // time taken

    // search using Rabin-Karp with inefficient and unsecure hash function
    startTime = System.nanoTime();
    List<Integer> badRKResult = rabinKarp.search(
        Arrays.copyOf(text.toCharArray(), text.length()),
        Arrays.copyOf(pattern.toCharArray(), pattern.length()), true);
    endTime = System.nanoTime();
    long duration3 = endTime - startTime;            // time taken
    displayBadRKResults(duration1, duration3, null); // displaying differences
    displayResult("Rabin-Karp (with an efficient hash function)", duration1,
                  rabinKarpResult, null); // displaying results

    // search using Knuth-Morris-Pratt
    startTime = System.nanoTime();
    List<Integer> knuthMorrisPrattResult = knuthMorrisPratt.search(
        Arrays.copyOf(text.toCharArray(), text.length()),
        Arrays.copyOf(pattern.toCharArray(), pattern.length()));
    endTime = System.nanoTime();
    displayResult("Knuth-Morris-Pratt", (endTime - startTime),
                  knuthMorrisPrattResult, null);
    long duration2 = endTime - startTime; // time taken

    // printing conclusion of this test
    displayConclusion(duration1, duration2, null);
  }

  /**
   * Writes algorithms' results to a file or prints them on screen.
   *
   * @param algorithmName name of the applied algorithm
   * @param duration      duration (in nanoseconds)
   * @param matches       list of matches (can be empty)
   * @param outputPath    output file to write to (can be null)
   */
  private void displayResult(final String algorithmName, long duration,
                             final List<Integer> matches,
                             final String outputPath) {
    if (outputPath == null) {
      System.out.println("Algorithm " + algorithmName + " took " + duration +
                         " nanoseconds (" + (double)duration / Math.pow(10, 9) +
                         " seconds)\n"
                         + "to search given pattern in the "
                         + "given text.");
      if (matches.isEmpty()) {
        System.out.println("No matches found!");
      } else {
        System.out.println("Matches(" + matches.size() +
                           ") found at index(es):");
        int match = 1;
        for (Integer integer : matches) {
          System.out.println("\tmatch " + match++ + " at index " + integer);
        }
        System.out.println();
      }
    } else {
      File outputFile = new File(outputPath);
      try {
        FileWriter fileWriter = new FileWriter(outputFile, true);
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("Algorithm ")
            .append(algorithmName)
            .append(" took ")
            .append(duration)
            .append(" nanoseconds (")
            .append((double)duration / Math.pow(10, 9))
            .append(" seconds)")
            .append("\nto search given pattern in the ")
            .append("given text.\n");
        if (matches.isEmpty()) {
          stringBuilder.append("No matches found!\n");
        } else {
          stringBuilder.append("Matches (")
              .append(matches.size())
              .append(") found at index(es):\n");
          int match = 1;
          for (Integer integer : matches) {
            stringBuilder.append("\tmatch ")
                .append(match++)
                .append(" at index ")
                .append(integer)
                .append("\n");
          }
        }
        stringBuilder.append("\n");
        fileWriter.write(stringBuilder.toString());
        fileWriter.flush();
        fileWriter.close();
      } catch (IOException e) {
        e.printStackTrace();
        System.exit(2);
      }
    }
  }

  /**
   * Prints a brief result of the two algorithms applied to the current test.
   *
   * @param RKDuration  duration of the RK algorithm
   * @param KMPDuration duration of the KMP algorithm
   * @param outputPath  path to the file to write to
   */
  private void displayConclusion(final long RKDuration, final long KMPDuration,
                                 final String outputPath) {

    if (outputPath == null) {
      System.out.println(
          "---------------------------------------\nThe conclusion of this test is:");
      if (RKDuration < KMPDuration) {
        System.out.println(
            "Algorithm Rabin-Karp was faster than Knuth-Morris-Pratt by " +
            (KMPDuration - RKDuration) + " nanoseconds (" +
            (double)(KMPDuration - RKDuration) / Math.pow(10, 9) +
            " seconds).");
      } else {
        System.out.println(
            "Algorithm Knuth-Morris-Pratt was faster than Rabin-Karp by " +
            (RKDuration - KMPDuration) + " nanoseconds (" +
            (double)(RKDuration - KMPDuration) / Math.pow(10, 9) +
            " seconds).");
      }
    } else {
      File outputFile = new File(outputPath);
      try {
        FileWriter fileWriter = new FileWriter(outputFile, true);
        StringBuilder stringBuilder = new StringBuilder(
            "\n---------------------------------------\nThe conclusion of this test is:\n");
        if (RKDuration < KMPDuration) {
          stringBuilder
              .append(
                  "Algorithm Rabin-Karp was faster than Knuth-Morris-Pratt by ")
              .append(KMPDuration - RKDuration)
              .append(" nanoseconds (")
              .append((double)(KMPDuration - RKDuration) / Math.pow(10, 9))
              .append(" seconds).\n");
        } else {
          stringBuilder
              .append(
                  "Algorithm Knuth-Morris-Pratt was faster than Rabin-Karp by ")
              .append(RKDuration - KMPDuration)
              .append(" nanoseconds (")
              .append((double)(RKDuration - KMPDuration) / Math.pow(10, 9))
              .append(" seconds).");
        }
        fileWriter.write(stringBuilder.toString());
        fileWriter.flush();
        fileWriter.close();
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }

  /**
   * Displays a brief description of the conclusion regarding using a bad hash
   * function or a efficient one.
   *
   * @param goodDuration time spent using efficient hash function
   * @param badDuration  time spend using a bad hashing function
   * @param outputPath   file to write to
   */
  private void displayBadRKResults(final long goodDuration,
                                   final long badDuration,
                                   final String outputPath) {
    if (outputPath == null) {
      System.out.println(
          "The Rabin-Karp version with a LESS EFFICIENT HASHING FUNCTION\nfinished the current test in " +
          badDuration + " nanoseconds (" +
          (double)badDuration / Math.pow(10, 9) + " seconds).");
      System.out.println(
          "The difference between the efficient version and this one is " +
          (badDuration - goodDuration) + " nanoseconds (" +
          (double)(badDuration - goodDuration) / Math.pow(10, 9) +
          " seconds).\n");
    } else {
      File outputFile = new File(outputPath);
      try {
        FileWriter fileWriter = new FileWriter(outputFile, true);

        String stringBuilder =
            "The Rabin-Karp version with a LESS EFFICIENT HASHING FUNCTION\nfinished the current test in " +
            badDuration + " nanoseconds (" +
            (double)badDuration / Math.pow(10, 9) + " seconds).\n"
            + "The difference between the efficient version and this one is " +
            (badDuration - goodDuration) + " nanoseconds (" +
            (double)(badDuration - goodDuration) / Math.pow(10, 9) +
            " seconds).\n\n";
        fileWriter.write(stringBuilder);
        fileWriter.flush();
        fileWriter.close();
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }
}
