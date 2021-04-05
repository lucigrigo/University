#!/bin/bash

echo "        size,          ops,         time,      time/op"

for ((i=2; i <= 256; i = i + 2)) do
    ./task5 $i 512000 $(($i * 10))
done
