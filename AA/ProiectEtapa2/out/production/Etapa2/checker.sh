#!/bin/bash

## Functions ##
function clean
{
  rm -rf ./tests/out
  mkdir ./tests/out
}
function compile
{
  javac -g com/luciangrigore/Main.java
}
function makeTest
{
  java com.luciangrigore.Main test "src/tests/in/test$1.txt" "src/tests/out/out$1.txt" > /dev/null
  echo "Test$1 done."
}
function clean
{
  find . -name "*.class" -type f -delete
}

## Main execution ##
echo "Cleaning previous results..."
clean
echo "Cleaning done!"
echo "Starting testing..."
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
clean
echo "Tests done!"
echo "Results can be found in src/tests/out folder's text files."
