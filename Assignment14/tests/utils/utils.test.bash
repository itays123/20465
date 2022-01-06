#!/bin/bash

echo "$(gcc -g ../../assembler/utils.c utils.c -Wall -pedantic -std=c90 -o utils)"
echo "$(./utils >utils.out.txt)"
echo "$(cat ./utils.out.txt)"