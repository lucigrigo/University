#!/bin/bash


counter=0

./electricity ./tests/test0.in your_result.out
if diff your_result.out ./tests/correct0.out > /dev/null
then
  echo "Testul 0 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 0 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct0.out
fi
echo ""


./electricity ./tests/test1.in your_result.out
if diff your_result.out ./tests/correct1.out > /dev/null
then
  echo "Testul 1 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 1 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct1.out
fi
echo ""


./electricity ./tests/test2.in your_result.out
if diff your_result.out ./tests/correct2.out > /dev/null
then
  echo "Testul 2 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 2 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct2.out
fi
echo ""


./electricity ./tests/test3.in your_result.out
if diff your_result.out ./tests/correct3.out > /dev/null
then
  echo "Testul 3 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 3 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct3.out
fi
echo ""


./electricity ./tests/test4.in your_result.out
if diff your_result.out ./tests/correct4.out > /dev/null
then
  echo "Testul 4 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 4 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct4.out
fi
echo ""

 
./electricity ./tests/test5.in your_result.out
if diff your_result.out ./tests/correct5.out > /dev/null
then
  echo "Testul 5 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 5 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct5.out
fi
echo ""


./electricity ./tests/test6.in your_result.out
if diff your_result.out ./tests/correct6.out > /dev/null
then
  echo "Testul 6 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 6 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct6.out
fi
echo ""



./electricity ./tests/test7.in your_result.out
if diff your_result.out ./tests/correct7.out > /dev/null
then
  echo "Testul 7 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 7 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct7.out
fi
echo ""



./electricity ./tests/test8.in your_result.out
if diff your_result.out ./tests/correct8.out > /dev/null
then
  echo "Testul 8 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 8 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct8.out
fi
echo ""


 
./electricity ./tests/test9.in your_result.out
if diff your_result.out ./tests/correct9.out > /dev/null
then
  echo "Testul 9 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 9 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct9.out
fi
echo ""


 
./electricity ./tests/bonus0.in your_result.out
if diff your_result.out ./tests/correct_bonus0.out > /dev/null
then
  echo "Testul bonus 0 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul bonus 0 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct_bonus0.out
fi
echo ""



./electricity ./tests/bonus1.in your_result.out
if diff your_result.out ./tests/correct_bonus1.out > /dev/null
then
  echo "Testul bonus 1 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul bonus 1 a picat!"
  echo "Raspunsul tau:"
  cat your_result.out
  echo "Raspunsul asteptat:"
  cat ./tests/correct_bonus1.out
fi
echo ""


echo "Felicitari! Ai obtinut $counter puncte!" 
rm your_result.out
