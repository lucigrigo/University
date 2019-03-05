package com.company;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    public static void main(String[] args) {
        String string = "I am a string. Yes, I am.";
        System.out.println(string);
        String yourString = string.replaceAll("I", "You");
        System.out.println(yourString);

        String alphanumeric = "abcDeeeF12Ghhiiiiijkl99z";
        // dot "." matches any character
        System.out.println(alphanumeric.replaceAll(".", "Y"));
        //  matches only at the beginning
        System.out.println(alphanumeric.replaceAll("^abcDeee", "YYY"));
        //  matches ALL the string
        System.out.println(alphanumeric.matches("^hello"));
        System.out.println(alphanumeric.matches("^abcDeee"));
        System.out.println(alphanumeric.matches("abcDeeeF12Ghhiiiiijkl99z"));
        //  matches only at the end
        System.out.println(alphanumeric.replaceAll("kl99z$", "THE END"));
        // matches either one of those
        System.out.println(alphanumeric.replaceAll("[eia]", "P"));
        System.out.println(alphanumeric.replaceAll("[eia]", "ALOHA"));
        System.out.println(alphanumeric.replaceAll("[aei][jF]", "X"));
        //  matches except
        System.out.println(alphanumeric.replaceAll("[^ej]", "X"));
        //  matches a range
        System.out.println(alphanumeric.replaceAll("[a-fA-F3-8]", "X"));
        //  ignore case sens. (i - ascii / u - unicode )
        System.out.println(alphanumeric.replaceAll("(?iu)[a-f3-8]", "X"));
        //  matches all numbers (d - digit)
        System.out.println(alphanumeric.replaceAll("\\d", "X"));
        //  matches all non-digits
        System.out.println(alphanumeric.replaceAll("\\D", "@"));
        //  a-zA-Z0-9 and _
        System.out.println(alphanumeric.replaceAll("\\w", "#"));
        //  anything but the ones above
        System.out.println(alphanumeric.replaceAll("\\W", "#"));

        System.out.println("\n\n");
        String hasWhiteSpace = "I have blanks and\ta tab, and also a newline\nsee?";
        System.out.println(hasWhiteSpace);
        //  removes all spaces
        System.out.println(hasWhiteSpace.replaceAll("\\s", ""));
        //  matches tab
        System.out.println(hasWhiteSpace.replaceAll("\t", "@"));
        //  matches everything but white-spaces
        System.out.println(hasWhiteSpace.replaceAll("\\S", ""));
        System.out.println(hasWhiteSpace.replaceAll("\\w", "#"));
        //  surrounds every word with the given char
        System.out.println(hasWhiteSpace.replaceAll("\\b", "#"));

        System.out.println("\n\nQUANTIFIERS");
        //  matches e exactly 3 times
        System.out.println(alphanumeric.replaceAll("^abcDe{3}", "#####"));
        //  matches e 1 or more times
        System.out.println(alphanumeric.replaceAll("^abcDe+", "%%%%%%"));
        //  matches e 0 or more times
        System.out.println(alphanumeric.replaceAll("^abcDe*", "*****"));
        //  matches e 2 to 5 times
        System.out.println(alphanumeric.replaceAll("^abcDe{2,5}", "?"));
        //  h followed by any number of i's and a j at the end
        System.out.println(alphanumeric.replaceAll("h+i*j", "???"));

        System.out.println("\n\nMATCHERS");
        StringBuilder htmlText = new StringBuilder("<h1>My Heading</h1>");
        htmlText.append("<h2>Sub-heading</h2>");
        htmlText.append("<p>This is a paragraph about something.</p>");
        htmlText.append("<p>This is another paragraph about something else.</p>");
        htmlText.append("<h2>Summary</h2>");
        htmlText.append("<p>Here is the summary</p>");

//        String h2Pattern = ".*<h2>.*";
//        Pattern pattern = Pattern.compile(h2Pattern, Pattern.CASE_INSENSITIVE | Pattern.UNICODE_CASE);
        String h2Pattern = "<h2>";
        Pattern pattern = Pattern.compile(h2Pattern);
        Matcher matcher = pattern.matcher(htmlText);
        System.out.println(matcher.matches());

        matcher.reset();
        int count = 0;
        while (matcher.find()) {
            count++;
            System.out.println("occurrence " + count + " : " +
                    matcher.start() + " to " + matcher.end());
        }

        System.out.println("==========================");
        //  parentheses -> group
        //  * is a greedy quantifier
        //  *? makes it a reluctant quantifier
        //  .*? accepts zero or more occurrences
        //  .+? accepts one or more occurrences
        String h2GroupPattern = "(<h2>.*?</h2>)";
        Pattern groupPattern = Pattern.compile(h2GroupPattern);
        Matcher groupMatcher = groupPattern.matcher(htmlText);
        System.out.println(groupMatcher.matches());

        groupMatcher.reset();
        while (groupMatcher.find()) {
            System.out.println("occurrence " + groupMatcher.group(1));
        }

        System.out.println("==========================");
        String h2TextGroups = "(<h2>)(.+?)(</h2>)";
        Pattern h2TextPattern = Pattern.compile(h2TextGroups);
        Matcher h2TextMatcher = h2TextPattern.matcher(htmlText);

        while (h2TextMatcher.find()) {
            System.out.println("occurrence : " + h2TextMatcher.group(2));
        }

        System.out.println("==========================");
        //  "abc" = "a" and "b" and "c"
        //  [abc] = [a|b|c]
        //  [^abc] = everything but 'abc'

        //  negative look ahead expr.
        String tvTest = "tstvtkt";
//        String tNotVRegExp = "t[^v]";
        String tNotVRegExp = "t(?!v)";
        //  positive look ahead expr. t(?=v) -> does not include de v
        Pattern tNotVPattern = Pattern.compile(tNotVRegExp);
        Matcher tNotVMatcher = tNotVPattern.matcher(tvTest);

        count = 0;
        while (tNotVMatcher.find()) {
            count++;
            System.out.println("Occurrence " + count + " : " + tNotVMatcher.start() +
                    " to " + tNotVMatcher.end());
        }
    }
}
