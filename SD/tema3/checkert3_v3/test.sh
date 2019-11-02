#!/bin/bash


counter=0

./electricity ./tests/test0.in your_result.out
if python ./links_check.py ./tests/test0.in your_result.out ./tests/correct0.out
then
  echo "Testul 0 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 0 a picat!"
fi
echo ""


./electricity ./tests/test1.in your_result.out
if python ./links_check.py ./tests/test1.in your_result.out ./tests/correct1.out
then
  echo "Testul 1 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 1 a picat!"
fi
echo ""


./electricity ./tests/test2.in your_result.out
if python ./links_check.py ./tests/test2.in your_result.out ./tests/correct2.out
then
  echo "Testul 2 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 2 a picat!"
fi
echo ""


./electricity ./tests/test3.in your_result.out
if python ./links_check.py ./tests/test3.in your_result.out ./tests/correct3.out
then
  echo "Testul 3 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 3 a picat!"
fi
echo ""


./electricity ./tests/test4.in your_result.out
if python ./links_check.py ./tests/test4.in your_result.out ./tests/correct4.out
then
  echo "Testul 4 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 4 a picat!"
fi
echo ""

 
./electricity ./tests/test5.in your_result.out
if python ./links_check.py ./tests/test5.in your_result.out ./tests/correct5.out
then
  echo "Testul 5 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 5 a picat!"
fi
echo ""


./electricity ./tests/test6.in your_result.out
if python ./links_check.py ./tests/test6.in your_result.out ./tests/correct6.out
then
  echo "Testul 6 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 6 a picat!"
fi
echo ""



./electricity ./tests/test7.in your_result.out
if python ./links_check.py ./tests/test7.in your_result.out ./tests/correct7.out
then
  echo "Testul 7 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 7 a picat!"
fi
echo ""



./electricity ./tests/test8.in your_result.out
if python ./links_check.py ./tests/test8.in your_result.out ./tests/correct8.out
then
  echo "Testul 8 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 8 a picat!"
fi
echo ""


 
./electricity ./tests/test9.in your_result.out
if python ./links_check.py ./tests/test9.in your_result.out ./tests/correct9.out
then
  echo "Testul 9 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul 9 a picat!"
fi
echo ""


 
./electricity ./tests/bonus0.in your_result.out
if python ./links_check.py ./tests/bonus0.in your_result.out ./tests/correct_bonus0.out
then
  echo "Testul bonus 0 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul bonus 0 a picat!"
fi
echo ""



./electricity ./tests/bonus1.in your_result.out
if python ./links_check.py ./tests/bonus1.in your_result.out ./tests/correct_bonus1.out
then
  echo "Testul bonus 1 a fost trecut cu succes!"
  counter=$((counter + 1))
else
  echo "Testul bonus 1 a picat!"
fi
echo ""


echo "Felicitari! Ai obtinut $counter puncte!" 
rm your_result.out
