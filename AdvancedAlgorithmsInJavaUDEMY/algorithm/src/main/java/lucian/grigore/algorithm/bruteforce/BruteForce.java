package lucian.grigore.algorithm.bruteforce;

import java.util.Arrays;

public class BruteForce {

    public int firstMatch(char[] array, char[] pattern) {
        for (int i = 0; i <= array.length - pattern.length; i++) {
            for (int j = 0; j < pattern.length; j++) {
                if (array[i + j] != pattern[j]) {
                    break;
                }
                if (j == pattern.length - 1) {
                    return i;
                }
            }
        }
        return -1;
    }

    public int[] everyMatch(char[] array, char[] pattern) {
        int[] found = new int[array.length];
        int index = 0;
        Arrays.fill(found, -1);

        for (int i = 0; i <= array.length - pattern.length; i++) {
            for (int j = 0; j < pattern.length; j++) {
                if (array[i + j] != pattern[j]) {
                    break;
                }
                if (j == pattern.length - 1) {
                    found[index++] = i;
                }
            }
        }
        return found;
    }
}
