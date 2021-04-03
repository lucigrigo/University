#!/bin/bash

echo "        size,          ops,         time,      op/time"

for ((i=131072; i <= 8290304; i = i + 131072)) do
    ./task4 64 $i $((2000000000 / $i))
done
