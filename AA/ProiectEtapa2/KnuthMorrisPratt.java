import java.util.ArrayList;
import java.util.List;

/**
 * Knuth-Morris-Pratt Algorithm.
 * It uses a special table named failure-function table or longest-suffix-prefix
 * table to skip a number of characters when a partial match has been made.
 */
public class KnuthMorrisPratt {

  /**
   * This computes the table of the longest suffix and longest prefix for the
   * pattern.
   * This is to be used by the Knuth-Morris-Pratt main algorithm.
   *
   * @param pattern given pattern
   * @return failure-function table
   */
  private int[] computeLSPTable(char[] pattern) {
    int[] lsp = new int[pattern.length];
    int j = 0;
    for (int i = 1; i < pattern.length; i++) {
      while (j > 0 && pattern[i] != pattern[j]) {
        j = lsp[j - 1]; // returning to last preffix start index
      }
      if (pattern[i] == pattern[j]) {
        lsp[i] = j + 1; // increase preffix index
        j++;
      } else {
        lsp[i] = 0; // no preffix
      }
    }
    return lsp;
  }

  /**
   * This method returns the indexes of the matches found or an empty list
   * if no matches are made.
   *
   * @param array   text to search the pattern into
   * @param pattern given pattern
   * @return list of matches (can be empty)
   */
  List<Integer> search(char[] array, char[] pattern) {
    if (array == null || pattern == null) {
      return null;
    }
    List<Integer> matchesIndexes = new ArrayList<>();
    int[] lsp = computeLSPTable(pattern);
    int j = 0;
    for (int i = 0; i < array.length; i++) {
      while (j > 0 && array[i] != pattern[j]) {
        j = lsp[j - 1]; // returning to last preffix index
      }
      if (array[i] == pattern[j]) {
        j++; // increasing index if character matches are currently done
        if (j == pattern.length) {
          matchesIndexes.add((i - (j - 1))); // match found
          j = lsp[j - 1]; // returning to last preffix index after a match
        }
      }
    }
    return matchesIndexes;
  }
}
