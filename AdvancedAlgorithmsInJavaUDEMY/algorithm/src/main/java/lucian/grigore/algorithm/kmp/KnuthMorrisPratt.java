package lucian.grigore.algorithm.kmp;

public class KnuthMorrisPratt {

    /**
     * This computes the table of the longest suffix and longest prefix for the pattern.
     * This is to be used by the Knuth-Morris-Pratt main algorithm.
     *
     * @param pattern
     * @return
     */
    public int[] computeLSPTable(char[] pattern) {
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
     * @param array
     * @param pattern
     * @return
     */
    public int search(char[] array, char[] pattern) {
        int[] lsp = computeLSPTable(pattern);
        int j = 0;
        for (int i = 0; i < array.length; i++) {
            while (j > 0 && array[i] != pattern[j]) {
                j = lsp[j - 1];
            }
            if (array[i] == pattern[j]) {
                j++;
                if (j == pattern.length) {
                    return (i - (j - 1));
                }
            }
        }
        return -1;
    }
}
