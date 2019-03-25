package com.luciangrigore;

public class Utilities {

    //  returns a char[] containing every n-th char
    //  when source array's length < n, returns source array
    public char[] everyNthChar(char[] sourceArray, int n) {
        if (sourceArray == null || sourceArray.length < n) {
            return sourceArray;
        }

        int returnedLength = sourceArray.length / n;
        char[] result = new char[returnedLength];
        int index = 0;

        for (int i = n - 1; i < sourceArray.length; i += n) {
            result[index++] = sourceArray[i];
        }

        return result;
    }

    //  removes pairs of the same character that are next to each other
    public String removePairs(String source) {
        if (source == null || source.length() < 2) {
            return source;
        }

        StringBuilder sb = new StringBuilder();
        char[] sourceArray = source.toCharArray();

        for (int i = 0; i < (source.length() - 1); i++) {
            if (sourceArray[i] != sourceArray[i + 1]) {
                sb.append(sourceArray[i]);
            }
        }
        if (sourceArray[source.length() - 1] == sourceArray[source.length() - 2]) {
            sb.append(sourceArray[source.length() - 1]);
        }
        if (sourceArray[source.length() - 1] != sourceArray[source.length() - 2]) {
            sb.append(sourceArray[source.length() - 1]);
        }

        return sb.toString();
    }

    //  performs a conversion based on some internal business rule
    public int converter(int a, int b) {
        return (a / b) + (a * 30) - 2;
    }

    public String nullIfOddLength(String source) {
        if (source.length() % 2 == 0) {
            return source;
        }

        return null;
    }
}
