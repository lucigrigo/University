package lucian.grigore.algorithm.boyermoore;

/**
 * Boyer Moore Horspool
 * This implementation is the simplified version of the Boyer Moore algorithm.
 * It only implements the bad character table.
 */
public class BoyerMooreHorspool {

    private final int ASCII_TABLE_SIZE = 256;

    public int search(char[] array, char[] pattern) {
        if (pattern == null || pattern.length == 0) return 0;
        if (array == null) return -1;
        int[] table = preprocessTable(pattern);
        for (int i = (pattern.length - 1); i < array.length; ) {
            for (int j = (pattern.length - 1); pattern[j] == array[i]; i--, j--) {
                if (j == 0) return i;
            }
            i += table[array[i]];
        }
        return -1;
    }

    /**
     * This method creates the bad character table.
     * It will add pattern.length() to every character that is not in the pattern.
     * It will also add pattern.length() to the last character of the pattern in case it is unique;
     * <p>
     * t e s        (t e s t)
     * 1 2 1
     * <p>
     * a b *        (a b c)
     * 2 1 3
     * <p>
     * max(1, p.length - index - 1)
     *
     * @param pattern
     * @return
     */
    public int[] preprocessTable(char[] pattern) {
        int[] table = new int[ASCII_TABLE_SIZE];
        for (int i = 0; i < ASCII_TABLE_SIZE; i++) {
            table[i] = pattern.length;
        }
        for (int t = 0; t < pattern.length - 1; t++) {
            table[pattern[t]] = Math.max(1, pattern.length - t - 1);
        }
        if (table[pattern[pattern.length - 1]] < pattern.length) {
            table[pattern[pattern.length - 1]] = 1;
        }
        return table;
    }
}
