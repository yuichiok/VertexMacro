#!/bin/sh

# Process ID
processIDs=(15162 15271 15273 15315 15319 15351 15353 15355 15357 15463 15465 15467 15469 15471 15473 15475 15477 15479 15499 15501 15503 15505 15507 15509 15511 15513 15515 15517 15539 15541 15549 15551 15553 15555 15557 15559 15561 15563 15585 15587 15589 15591 15593 15595 15597 15599 15601 15603 15629 15633)
OLDPATH=$PWD

for processID in ${processIDs[*]};
do

  cd /group/ilc/users/yokugawa/QQbar250/l5/eLpR/${processID}/dEdx_corr/QQbarProcessor_out/

  for i in *.root; do
    filename=$(basename -- "$i")
    filename="${filename%.*}"

    filenumber=$(echo $filename| cut -d'_' -f 9)
    suffix_removed_string=${filename/%${filenumber}}
    filenumber=$(printf "%03d" "$(( 10#${filenumber} ))")

    newfilename="${suffix_removed_string}${filenumber}.root"

    echo "mv -f" ${i} ${newfilename}

    mv -f $i ${newfilename}

  done

done

cd $OLDPATH
