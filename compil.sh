#!/bin/bash
./myc < $1
if [ $? = 0 ]
then
  gcc -std=c99 -o test_exec test/test.c
  mv test_exec test/test
  ./test/test
else
    echo "Pas d'execution"
fi
