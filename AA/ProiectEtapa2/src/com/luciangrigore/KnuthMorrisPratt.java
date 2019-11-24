package com.luciangrigore;

import java.util.ArrayList;
import java.util.List;

/**
 * Knuth-Morris-Pratt Algorithm.
 * It uses a special table named failure-function table or longest-suffix-prefix table
 * to skip a number of characters when a partial match has been made.
 */
class KnuthMorrisPratt {

    /**
     * This computes the table of the longest suffix and longest prefix for the pattern.
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
                j = lsp[j - 1];
            }
            if (pattern[i] == pattern[j]) {
                lsp[i] = j + 1;
                j++;
            } else {
                lsp[i] = 0;
            }
        }
        return lsp;
    }

    /**
     * This method returns the index for the first match of the pattern into the array;
     * It will return -1 in case it does not match.
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
                j = lsp[j - 1];
            }
            if (array[i] == pattern[j]) {
                j++;
                if (j == pattern.length) {
                    matchesIndexes.add((i - (j - 1)));
                    j = lsp[j - 1];
                }
            }
        }
        return matchesIndexes;
    }
}
