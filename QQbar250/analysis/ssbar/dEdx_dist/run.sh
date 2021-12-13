#!/bin/sh

bsub -q s -o ./log/run_ss.log root -l -q run_process.cc\(\"ss\"\)
bsub -q s -o ./log/run_uu.log root -l -q run_process.cc\(\"uu\"\)
bsub -q s -o ./log/run_dd.log root -l -q run_process.cc\(\"dd\"\)
bsub -q s -o ./log/run_uds.log root -l -q run_process.cc\(\"uds\"\)
