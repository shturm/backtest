#!/bin/bash

rm tests/data/history.tohlc.csv.bth

cd tests/
for f in *.out; do
  echo "==== " $f "===="
  ./$f
  echo "====" /$f "===="
  
done

cd ../