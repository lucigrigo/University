package com.luciangrigore;

/**
 * Analiza Algoritmilor - Proiect Etapa 2
 * Algoritmii Rabin-Karp si Knuth-Morris-Pratt
 * Grigore Lucian-Florin 324CDb
 * Facultatea de Automatica si Calculatoare
 * Universitatea Politehnica, Bucuresti
 */
public class Main {

    public static void main(final String[] args) {
        if (args[0] != null) {
            MatchingAdministrator administrator = new MatchingAdministrator();
            switch (args[0]) {
                case "test":
                    administrator.runSingleTests(args[1], args[2]);
                    break;
                case "manual":
                    administrator.runManualTest(args[1], args[2]);
                    break;
                default:
                    System.out.println("Input invalid!");
                    System.exit(1);
            }
        } else {
            System.out.println("Input invalid!");
            System.exit(1);
        }
    }
}
