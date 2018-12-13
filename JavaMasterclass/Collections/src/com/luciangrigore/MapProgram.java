package com.luciangrigore;

import java.util.HashMap;
import java.util.Map;

public class MapProgram {

    public static void main(String[] args) {

        Map<String, String> languages = new HashMap<>();
        languages.put("Java", "a compiled high-level, " +
                "object-oriented, platform independent language");
        languages.put("Python", "an interpreted, object-oriented, high-level programming" +
                "language with dynamic semantics");
        languages.put("Algol", "an algorithmic language");
        //  returns null because BASIC did not exist before
        System.out.println(languages.put("BASIC", "Beginners All Purposes Symbolic Instruction Code"));
        languages.put("Lisp", "therein lies madness");

//        System.out.println(languages.get("Java"));
//        //  This overwrites the value(definition) at the java key
//        languages.put("Java", "the course is about java");
//        System.out.println(languages.get("Java"));

        //  languages.put returns null if the key was not previously used
//        System.out.println(languages.put("Java", "new value for test"));


        if (languages.containsKey("Java")) {
            System.out.println("Java is already in the map");
        } else {
            languages.put("Java", "this course is about Java");
        }


        System.out.println("==================================");
        for (String key : languages.keySet()) {
            System.out.println(key + " : " + languages.get(key));
        }
        System.out.println("==================================");


        //  Remove method returns true/false
//        languages.remove("Lisp");
        if (languages.remove("BASIC", "only for test purposes")) {
            System.out.println("BASIC removed!");
        } else {
            System.out.println("BASIC not removed, key/value pair not correct");
        }


        //  Replace method can be used with 2 or 3 parameters
        if (languages.replace("BASIC", "This will not work", "a basic ass motherfucker")) {
            System.out.println("BASIC replaced");
        } else {
            System.out.println("BASIC not replaced");
        }
//        languages.replace("C-lang","it is not in the map");


        System.out.println("==================================");
        for (String key : languages.keySet()) {
            System.out.println(key + " : " + languages.get(key));
        }
        System.out.println("==================================");
    }
}
