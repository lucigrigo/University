package com.luciangrigore;

public class StringUtilities {

    private StringBuilder sBuilder = new StringBuilder();
    private int charsAdded = 0;

    public void addChar(StringBuilder stringBuilder, char c) {
        stringBuilder.append(c);
        charsAdded++;
    }

    public String upperAndPrefix(String string) {
        String upper = string.toUpperCase();
        return "Prefix_" + upper;
    }

    public String addSufix(String string) {
        return string + "_Suffix";
    }
}
