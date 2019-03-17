package lucian.grigore.algorithm.zalgorithm;

/**
 * Z-Algorithm
 * This algorithm uses the Z-Table.
 */
public class ZAlgorithm {

    private char SEPARATOR = '$';

    public int search(char[] pattern, char[] array) {
        int[] zTable = createZTable(pattern, array);
        for (int i = (pattern.length + 1); i < zTable.length; i++) {
            if (zTable[i] == pattern.length) {
                return (i - pattern.length - 1);
            }
        }
        return -1;
    }

    public int[] searchAll(char[] pattern, char[] array) {
        int[] zTable = createZTable(pattern, array);
        int[] newTable = new int[array.length];
        for (int i = 0; i < array.length; i++) {
            newTable[i] = zTable[i + 1 + pattern.length];
        }
        return newTable;
    }

    public int[] createZTable(char[] pattern, char[] array) {
        char[] longString = createLongString(pattern, array);
        int[] zTable = new int[longString.length];
        int left = 0, right = 0;
        for (int i = 1; i < longString.length; i++) {
            if (i > right) {
                left = right = i;
                while (right < longString.length && longString[right - left] == longString[right]) {
                    right++;
                }
                zTable[i] = right - left;
                right--;
            } else {
                int k = i - left;
                if (zTable[k] < right - i + 1) {
                    zTable[i] = zTable[k];
                } else {
                    left = i;
                    while (right < longString.length && longString[right - left] == longString[right]) {
                        right++;
                    }
                    zTable[i] = right - left;
                    right--;
                }
            }
        }

        return zTable;
    }

    public char[] createLongString(char[] pattern, char[] array) {
        char[] string = new char[pattern.length + array.length + 1];
        for (int i = 0; i < pattern.length; i++) {
            string[i] = pattern[i];
        }
        string[pattern.length] = SEPARATOR;
        for (int i = 0; i < array.length; i++) {
            string[i + pattern.length + 1] = array[i];
        }
        return string;
    }
}
