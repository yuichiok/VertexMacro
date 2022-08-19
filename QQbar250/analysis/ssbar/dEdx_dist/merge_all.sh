#!/bin/bash

indir=./rootfiles/tmp_root
stagedir=${indir}/stage_merge

outdir=./rootfiles/double_tag

# Process ID
processIDs=(15162 15271 15273 15315 15319 15351 15353 15355 15357 15463 15465 15467 15469 15471 15473 15475 15477 15479 15499 15501 15503 15505 15507 15509 15511 15513 15515 15517 15539 15541 15549 15551 15553 15555 15557 15559 15561 15563 15585 15587 15589 15591 15593 15595 15597 15599 15601 15603 15629 15633)

if [[ ! -d "$indir" || ! -d "$stagedir" || ! -d "$outdir" ]]; then
	echo "The directory does not exist."
	exit 1
else
	echo ${indir}

	for processID in ${processIDs[*]};
	do
		echo "Processing" ${processID} "..."
		hadd -f ${stagedir}/DQ_250GeV_ss.${processID}.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.K_cos.AllEvents.root ${indir}/*${processID}*.root &
	done

	wait

	hadd -f ${outdir}/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppKMult.KPicross.K_cos.AllEvents.root ${stagedir}/*.root

fi

