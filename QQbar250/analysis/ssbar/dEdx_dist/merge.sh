#!/bin/bash

indir=./rootfiles/tmp_root
outdir=./rootfiles/double_tag

if [[ ! -d "$indir" || ! -d "$outdir" ]]; then
	echo "The directory does not exist."
	exit 1
else
	echo ${indir}
	# hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.mergeFULL.root ${indir}/*.root
	# hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.mergeFULL.root ${indir}/*.root
	# hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.neutral.mergeFULL.root ${indir}/*.root
	# hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.neutral.mergeFULL.root ${indir}/*.root

	# hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.ISRcut.mergeFULL.root ${indir}/*.root
	# hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.ISRcut.mergeFULL.root ${indir}/*.root
	# hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.Kmass.mergeFULL.root ${indir}/*.root
	hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.calo.mergeFULL.root ${indir}/*.root
fi

