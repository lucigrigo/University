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

    private final int prime = 3;

    /**
     * This method returns the index of the first match of the pattern in the array.
     *
     * @param array   text to search given pattern into
     * @param pattern given pattern
     * @return list of matches(can be empty)
     */
    List<Integer> search(char[] array, char[] pattern) {
        if (array == null || pattern == null) {
            return null;
        }
        List<Integer> matchesIndexes = new ArrayList<>();
        int n = array.length, m = pattern.length, lastCharacterIndex = (n - m);
        long patternHash = calculateHash(pattern, m), arrayHash = calculateHash(array, m);
        for (int i = 0; i <= lastCharacterIndex; i++) {
            if (patternHash == arrayHash) {
                if (match(array, pattern, i)) {
                    matchesIndexes.add(i);
                }
            }
            if (i < lastCharacterIndex) {
                arrayHash = recalculateHash(arrayHash, array[i], array[i + m], m);
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
    private boolean match(char[] array, char[] pattern, int index) {
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
     * Computes initial value of the hash
     *
     * @param text     given array
     * @param hashSize given length
     * @return hash value
     */
    private long calculateHash(char[] text, int hashSize) {
        long hash = 0;
        for (int i = 0; i < hashSize; i++) {
            hash += characterValue(text[i]) * Math.pow(prime, i);
        }
        return hash;
    }

    /**
     * Recomputes the hash value of a given array by removing first character's
     * value and adding a new one.
     *
     * @param oldValue  old hash value
     * @param oldChar   character to be removed
     * @param newChar   character to be added
     * @param maxLength array length
     * @return new hash value
     */
    private long recalculateHash(long oldValue, char oldChar, char newChar, int maxLength) {
        return (((oldValue - characterValue(oldChar))
                / prime) + (long) Math.pow(prime, maxLength - 1) * characterValue(newChar));
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

    // TODO add a bad hash function
}
