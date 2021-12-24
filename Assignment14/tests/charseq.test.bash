#!/bin/bash

echo "$(gcc -g ../assembler/charsequence.c charsequence.c -Wall -pedantic -std=c90 -o charsequence)"
echo "$(./charsequence)"