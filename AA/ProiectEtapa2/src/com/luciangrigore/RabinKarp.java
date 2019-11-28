package com.luciangrigore;

import java.util.ArrayList;
import java.util.List;

/**
 * Rabin-Karp Algorithm
 * It uses hashing to find a match between a pattern and an array of characters.
 * It uses rolling hashes function to recalculate the hash of the subsequent possible matches.
 * It will return the index of the match.
 * It will return -1 otherwise.
 */
class RabinKarp {

    /**
     * This method returns the index of the first match of the pattern in the array.
     *
     * @param array   text to search given pattern into
     * @param pattern given pattern
     * @return list of matches(can be empty)
     */
    List<Integer> search(final char[] array,
                         final char[] pattern,
                         final boolean useBadHash) {
        if (array == null || pattern == null) {
            return null;
        }
        List<Integer> matchesIndexes = new ArrayList<>();
        int n = array.length, m = pattern.length, lastCharacterIndex = (n - m);
        long patternHash, arrayHash;
        if (!useBadHash) {
            patternHash = calculateHash(pattern, m, 0);
            arrayHash = calculateHash(array, m, 0);
        } else {
            patternHash = calculateBADHashValue(pattern, m, 0);
            arrayHash = calculateBADHashValue(array, m, 0);
        }
        for (int i = 0; i <= lastCharacterIndex; i++) {
            if (patternHash == arrayHash) {
                if (match(array, pattern, i)) {
                    matchesIndexes.add(i);
                }
            }
            if (i < lastCharacterIndex) {
                if (!useBadHash) {
                    arrayHash = calculateHash(array, m, i + 1);
                } else {
                    arrayHash = calculateBADHashValue(array, m, i);
                }
            }
        }
        return matchesIndexes;
    }

    /**
     * Verifies the possible match character by character.
     *
     * @param array   given array
     * @param pattern given pattern
     * @param index   starting index of the possible match
     * @return true or false if a match has been found or not
     */
    private boolean match(final char[] array,
                          final char[] pattern,
                          final int index) {
        int i = index;
        while (i < (index + pattern.length)) {
            if (pattern[i - index] != array[i]) {
                return false;
            }
            i++;
        }
        return true;
    }

    /**
     * Computes initial value of the hash.
     *
     * @param text     given array
     * @param hashSize given length
     * @return hash value
     */
    private long calculateHash(final char[] text,
                               final int hashSize,
                               final int startIndex) {
        long hash = 0;
        for (int i = startIndex; i < (startIndex + hashSize); i++) {
            hash = 33 * hash + text[i];
        }
        return hash;
    }

//        return (((oldValue - characterValue(oldChar))
//                / prime) + (long) Math.pow(prime, maxLength - 1) * characterValue(newChar));

    /**
     * Function that computes initial hash value of an array using an inefficient approach.
     *
     * @param text     given array
     * @param hashSize array length
     * @return hash value
     */
    private long calculateBADHashValue(final char[] text,
                                       final int hashSize,
                                       final int index) {
        long hash = 0;
        for (int i = index; i < hashSize + index; i++) {
            hash = hash + characterValue(text[i]);
        }
        return hash;
    }

    /**
     * Converts ascii values to decimal ones.
     *
     * @param val ascii value
     * @return actual value
     */
    private long characterValue(char val) {
        return (val - 96);
    }
}
