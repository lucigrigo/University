package com.luciangrigore;

public class Main {

    public static void main(String[] args) {
        StringUtilities utils = new StringUtilities();
        StringBuilder sb = new StringBuilder();

        while (sb.length() < 10) {
            utils.addChar(sb, 'a');

        }

        System.out.println("string builder = " + sb);

        String str = "abcdefg";
        String result = utils.upperAndPrefix(utils.addSufix(str));
    }
}
