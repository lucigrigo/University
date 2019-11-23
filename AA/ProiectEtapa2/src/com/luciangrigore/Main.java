package com.luciangrigore;

class SubsequencesGenerator {

    void generateSubsequences(String array,
                              int index,
                              int[] temp) {
//        if (index == array.length()) {
//            if (subseqeunce.length() != 0) {
//                System.out.println(subseqeunce);
//            }
//        } else {
//            generateSubsequences(array, index + 1, subseqeunce);
//            generateSubsequences(array, index + 1, subseqeunce
//                    + Character.toString(subseqeunce.charAt(index)));
//        }

        if (index == array.length()) {
            print(array, temp);
            return;
        }
        temp[index] = 1;
        generateSubsequences(array, index + 1, temp);
        temp[index] = 0;
        generateSubsequences(array, index + 1, temp);
    }

    private void print(String array,
                       int[] vect) {
        String result = "";
        for (int i = 0; i < vect.length; i++) {
            if (vect[i] == 1)
                result = result
                        + array.charAt(i) + " ";
        }
        if (!result.equals("")) {
            System.out.println(result);
            // TODO apply KMP and RB algorithms to the result
        }
    }
}

public class Main {


    public static void main(String[] args) {

        String test = "abcdef";
        new SubsequencesGenerator()
                .generateSubsequences(test, 0, new int[test.length()]);
    }
}
