#!/bin/bash
# ! A SE RULA CU SUDO IN CAZ DE ERORI !
# (pentru comenzile din functia cleanOutDir)

## Description ##
#
# Analiza Algoritmilor - Proiect Etapa 2
# Algoritmii Rabin-Karp si Knuth-Morris-Pratt
# Grigore Lucian-Florin 324CDb
# Facultatea de Automatica si Calculatoare
# Universitatea Politehnica, Bucuresti
#
# Urmatorul script ruleaza testele predefinite si pune rezultatele lor in
# folderul out.
##

## Functions ##
function cleanOutDir() {
  rm -rf out
  mkdir out
}
function compile() {
  javac -g Main.java
}
function makeTest() {
  java Main test "in/test$1.in" "out/test$1.out" >/dev/null
  echo "Test$1 ................................. done."
}
function clean() {
  find . -name "*.class" -type f -delete
}

## Main execution ##
echo ""
echo ""
echo "         --- Testing Rabin-Karp and Knuth-Morris-Pratt algorithms ---"
echo ""
echo "---   ---"
echo "Cleaning previous results..."
cleanOutDir
clean
echo "Cleaning done!"
echo "---   ---"
echo "Starting testing..."
echo "---   ---"
compile
makeTest "1"
makeTest "2"
makeTest "3"
makeTest "4"
makeTest "5"
makeTest "6"
makeTest "7"
makeTest "8"
makeTest "9"
makeTest "10"
makeTest "11"
makeTest "12"
makeTest "13"
makeTest "14"
makeTest "15"
makeTest "16"
makeTest "17"
makeTest "18"
makeTest "19"
makeTest "20"
makeTest "21"
makeTest "22"
makeTest "23"
makeTest "24"
makeTest "25"
makeTest "26"
makeTest "27"
makeTest "28"
makeTest "29"
makeTest "30"
clean
echo "---   ---"
echo "Testing done!"
echo "---   ---"
echo "Results can be found in out folder's text files."
echo "    (use cat out/test[TEST_NUMBER].out to view manually)"
echo "---   ---"
echo ""
