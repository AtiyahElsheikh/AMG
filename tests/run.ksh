#!/bin/ksh

LIST="01 02 03 04 05 06 07 08 09 10 11 12 13 14 adic_01 adic_02"

if [[ $1 = new ]]; then
    mkdir -p new
    cd new
    for i in $LIST
      do
      INPUT=test$i
      cp ../$INPUT .
      echo "generating new gateway from $INPUT"
      echo "=================================="
      echo ""
      amg $INPUT
      rm $INPUT
    done
    rm -f *tmp makefile*
elif [[ $1 = standard ]]; then
    mkdir -p standard
    cd standard
    for i in $LIST
      do
      INPUT=test$i
      cp ../$INPUT .
      echo "generating standard gateway from $INPUT"
      echo "======================================="
      echo ""
      amg $INPUT
      rm $INPUT
    done
    rm -f *tmp makefile*
elif [[ $1 = compare ]]; then
    for i in $LIST
      do
      INPUT=test$i
      echo "Comparing standard gateway with new gateway of $INPUT"
      echo "====================================================="
      echo "The input file is for testing:"
      head -n 4 $INPUT
      echo ""
      GATEWAY=foo_$i
      diff standard/$GATEWAY.c new/$GATEWAY.c
      echo "Press any key + ENTER to continue"
      read anything
      clear
    done
fi  