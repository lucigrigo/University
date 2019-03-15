package lucian.grigore.algorithm.rabinkarp;

/**
 * Rabin-Karp Algorithm
 * It uses hashing to find a match between a pattern and an array of characters.
 * It uses rolling hashes function to recalculate the hash of the subsequent possible matches.
 * It will return the index of the match.
 * It will return -1 otherwise.
 */
public class RabinKarp {

    private final int prime = 3;

    /**
     * This method returns the index of the first match of the pattern in the array.
     *
     * @param array
     * @param pattern
     * @return
     */
    public int search(char[] array, char[] pattern) {
        if (array == null || pattern == null) {
            return -1;
        }
        int n = array.length, m = pattern.length, lastCharacterIndex = (n - m);
        long patternHash = calculateHash(pattern, m), arrayHash = calculateHash(array, m);
        for (int i = 0; i <= lastCharacterIndex; i++) {
            if (patternHash == arrayHash) {
                if (match(array, pattern, i)) {
                    return i;
                }
            }
            if (i < lastCharacterIndex) {
                arrayHash = recalculateHash(arrayHash, array[i], array[i + m], m);
            }
        }
        return -1;
    }

    public boolean match(char[] array, char[] pattern, int index) {
        int i = index;
        while (i < (index + pattern.length)) {
            if (pattern[i - index] != array[i]) {
                return false;
            }
            i++;
        }
        return true;
    }

    public long calculateHash(char[] text, int hashSize) {
        long hash = 0;
        for (int i = 0; i < hashSize; i++) {
            hash += characterValue(text[i]) * Math.pow(prime, i);
        }
        return hash;
    }

    public long recalculateHash(long oldValue, char oldChar, char newChar, int maxLength) {
        return (((oldValue - characterValue(oldChar)) / prime) + (long) Math.pow(prime, maxLength - 1) * characterValue(newChar));
    }

    public long characterValue(char val) {
        return (val - 96);
    }
}
