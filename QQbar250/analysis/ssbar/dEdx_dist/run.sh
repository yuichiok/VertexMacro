#!/bin/sh

bsub -q s root -l -q run_process.cc\(\"ss\"\)
bsub -q s root -l -q run_process.cc\(\"uu\"\)
bsub -q s root -l -q run_process.cc\(\"dd\"\)
bsub -q s root -l -q run_process.cc\(\"uds\"\)
