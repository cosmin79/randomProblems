#!/bin/bash

g++ -std=c++11 intervalsReunionTest.cpp -o gen
g++ -std=c++11 intervalsReunion.cpp -o C1
g++ -std=c++11 intervalsReunionBrute.cpp -o C2

for ((i=1; i<= 100000; ++i))
do
  ./gen
  ./C1 > C1.out
  ./C2 > C2.out

  if cmp -s "C1.out" "C2.out"
  then
    echo "Pass test no.$i"
  else
    echo "Failed test no.$i"
    break;  
  fi
done