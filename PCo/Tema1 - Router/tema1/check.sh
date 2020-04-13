#!/bin/bash

sudo make

sudo fuser -k 6653/tcp
sudo python3 ./topo.py tests
