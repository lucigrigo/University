package lucian.grigore.algorithm.boyermoore;

/**
 * Boyer Moore Algorithm<br>
 * This algorithm will search for a pattern into an array of characters.
 * Returns the index of the first match of -1 for no match.
 * This algorithm uses two tables that helps to improve the time complexity and return
 * the search result in less time than Brute Force Algorithm.
 */
public class BoyerMoore {

    private final int ASCII_TABLE_SIZE = 256;

    public int search(char[] array, char[] pattern) {
        if (pattern == null || pattern.length == 0) {
            return 0;
        }
        if (array == null) {
            return -1;
        }
        int[] badCharacterTable = preprocessBadCharacterTable(pattern), suffixTable = preprocessSuffixTable(pattern);
        for (int i = pattern.length - 1, j; i < array.length; ) {
            for (j = pattern.length - 1; pattern[j] == array[i]; --i, --j) {
                if (j == 0) {
                    return i;
                }
            }
            i += Math.max(suffixTable[pattern.length - 1 - j], badCharacterTable[array[i]]);
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
    public int[] preprocessBadCharacterTable(char[] pattern) {
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

    public int[] preprocessSuffixTable(char[] pattern) {
        int[] table = new int[pattern.length];
        computePrefix(pattern, table);
        computeSuffix(pattern, table);
        return table;
    }

    public void computeSuffix(char[] pattern, int[] table) {
        for (int i = 0; i < pattern.length - 1; i++) {
            int len = suffixLength(pattern, i);
            table[len] = pattern.length - 1 - i + len;
        }
    }

    public void computePrefix(char[] pattern, int[] table) {
        int lastPrefixPosition = pattern.length;
        for (int i = pattern.length; i > 0; i--) {
            if (isPrefix(pattern, i)) {
                lastPrefixPosition = i;
            }
            table[pattern.length - i] = lastPrefixPosition - i + pattern.length;
        }
    }

    public boolean isPrefix(char[] pattern, int index) {
        for (int i = index, j = 0; i < pattern.length; i++, j++) {
            if (pattern[i] != pattern[j]) return false;
        }
        return true;
    }

    public int suffixLength(char[] pattern, int index) {
        int len = 0, j = pattern.length - 1;
        for (int i = index; i >= 0 && pattern[i] == pattern[j]; i--, j--) {
            len++;
        }
        return len;
    }
}
