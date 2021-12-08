#!/bin/sh

# for cut in 0 1 2 5
for cut in 0 1 2 5 10 20 30 60
do
	root -l -q analysis.cc\(${cut}\)
done
