#!/bin/bash

cd sol/ && sudo make && cd ..
sudo ln -fs src/router router

sudo fuser -k 6653/tcp
sudo python3 ./topo.py tests
