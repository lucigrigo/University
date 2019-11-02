package com.luciangrigore;

import java.util.Random;

public class PasswordMaker {

    private static PasswordMaker instance = null;

    private final int MAGIC_NUMBER = 15;
    private String MAGIC_STRING;
    private String name;
    private String password;
    // trebuie sa fie 'static' counts deoarece nu poate fi accesata/incrementata dintr-o
    // functie statica (getInstance()) daca ea nu e o variabila statica
    private static int counts;

    static {
        instance = new PasswordMaker("defaultName");
    }

    private PasswordMaker(String name) {
        counts = 0;
        MAGIC_STRING = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                + "0123456789"
                + "abcdefghijklmnopqrstuvxyz";
        StringBuilder sb = new StringBuilder();
        Random r = new Random();
        for (int i = 0; i < MAGIC_NUMBER + 10; i++) {
            int index = Math.abs((r.nextInt() *
                    MAGIC_STRING.length()) % MAGIC_STRING.length());
            sb.append(MAGIC_STRING.charAt(index));
        }
        this.name = name;
        sb.append(name.length() + Math.nextAfter(0f, 100f));
        this.password = sb.toString();
    }

    public static PasswordMaker getInstance() {
        counts++;
        if (instance == null) {
            instance = new PasswordMaker("defaultName");
        }
        return instance;
    }

    public String getPassword() {
        return password;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public int getCounts() {
        return counts;
    }

    // **RASPUNS LA TEMA DE GANDIRE:**
    /* Folosirea unei singure clase Singleton in cadrul unui program paralelizat poate duce
     la intercalarea thread-urilor in executarea/modificarea diferitelor proprietati si/sau
     functii din clasa Singleton -> trebuie sincronizata clasa Singleton (synchronized())
     pentru a fi threadsafe. */
}
