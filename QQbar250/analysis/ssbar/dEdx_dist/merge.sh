#!/bin/bash

indir=./rootfiles/tmp_root
outdir=./rootfiles/double_tag

if [[ ! -d "$indir" || ! -d "$outdir" ]]; then
	echo "The directory does not exist."
	exit 1
else
	echo ${indir}
	hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.mergeFULL.root ${indir}/*.root
fi
