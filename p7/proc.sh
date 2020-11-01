#!/bin/bash
grep -v '#' | awk '
{
  x[$1] += $3;
  nx[$1]++;
  y[$1] += $5;
  ny[$1]++ } 
END { 
    for (i in x) { 
        print i, x[i]/nx[i], y[i]/ny[i] }
}'
