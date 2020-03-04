#!/bin/bash

# Lab4: LOSS=0, CORRUPT=0
SPEED=10
DELAY=10
LOSS=0
CORRUPT=0
#BDP - to be modified when implementing sliding window
BDP=$((SPEED * DELAY))

killall link 2> /dev/null
killall recv 2> /dev/null
killall send 2> /dev/null

./link_emulator/link speed=$SPEED delay=$DELAY loss=$LOSS corrupt=$CORRUPT &> /dev/null &
sleep 1
./recv &
sleep 1

./send $BDP
