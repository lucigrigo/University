package com.company;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    public static void main(String[] args) {
        String challenge1 = "I want a bike.";
        System.out.println(challenge1.replaceAll(".", "X"));
        System.out.println(challenge1.matches("I want a bike."));

        String challenge2 = "I want a ball";
        System.out.println(challenge1.matches("(I want a).*"));
        System.out.println(challenge2.matches("(I want a).*"));

        String challenge3Exp = "(I want a).*";
        Pattern challenge3Pattern = Pattern.compile(challenge3Exp);
        Matcher challenge3Matcher = challenge3Pattern.matcher(challenge1);
        System.out.println(challenge3Matcher.matches());
        challenge3Matcher = challenge3Pattern.matcher(challenge2);
        System.out.println(challenge3Matcher.matches());

        String challenge4 = "Replace all blanks with underscores.";
        System.out.println(challenge4.replaceAll("\\s", "_"));

        String challenge5 = "aaabccccccccdddefffg";
        System.out.println(challenge5.matches("^[a]{3}b[c]{8}[d]{3}e[f]{3}g$"));

        String challenge7 = "abcd.123";
        String challenge7_2 = "f23.34a";
        System.out.println(challenge7.matches("^([a-zA-Z]+)\\.([0-9]+)$"));
        System.out.println(challenge7_2.matches("^([a-zA-Z]+)\\.([0-9]+)$"));

        String challenge8 = "abcd.135uvqz.7tzik.999";
//        String challenge8Exp = "([0-9]+)";
        String challenge8Exp = "[A-Za-z]+\\.(\\d+)";
        Pattern challenge8Pattern = Pattern.compile(challenge8Exp);
        Matcher challenge8Matcher = challenge8Pattern.matcher(challenge8);
        while (challenge8Matcher.find()) {
            System.out.println(challenge8Matcher.group(1));
        }

        String challenge9 = "abcd.135\tuvqz.7\ttzik.999\n";
        String challenge9Exp = "[A-Za-z]+\\.(\\d+)[\\t,\\n]{1}";
        challenge8Pattern = Pattern.compile(challenge9Exp);
        challenge8Matcher = challenge8Pattern.matcher(challenge9);
        while (challenge8Matcher.find()) {
            System.out.println("Occurrence: " + challenge8Matcher.group(1));
        }

        //  CHALLENGE 10
        challenge8Matcher.reset();
        while (challenge8Matcher.find()) {
            System.out.println(challenge8Matcher.start(1) + " to " +
                    (challenge8Matcher.end(1) - 1));
        }

        String challenge11 = "{0, 2}, {0, 5}, {1, 3}, {2, 4}";
        challenge11 = challenge11.replaceAll(" ", "");
        String challenge11Exp = "\\{([0-9]{1}),([0-9]{1})\\}";
        Pattern challenge11Pattern = Pattern.compile(challenge11Exp);
        Matcher challenge11Matcher = challenge11Pattern.matcher(challenge11);

        while (challenge11Matcher.find()) {
            System.out.println("x = " + challenge11Matcher.group(1) + " and y = " +
                    challenge11Matcher.group(2));
        }

        String challenge12 = "11111";
        System.out.println(challenge12.matches("^\\d{5}$"));

        String challenge13 = "11111-1111";
        System.out.println(challenge13.matches("^\\d{5}-\\d{4}$"));
        //  CHALLENGE 14
        System.out.println(challenge13.matches("^\\d{5}(-\\d{4})?$"));
        System.out.println(challenge12.matches("^\\d{5}(-\\d{4})?$"));
    }
}
