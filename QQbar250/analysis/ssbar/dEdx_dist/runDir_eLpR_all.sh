#!/bin/sh

# Process ID
processIDs=(15162 15271 15273 15315 15319 15351 15353 15355 15357 15463 15465 15467 15469 15471 15473 15475 15477 15479 15499 15501 15503 15505 15507 15509 15511 15513 15515 15517 15539 15541 15549 15551 15553 15555 15557 15559 15561 15563 15585 15587 15589 15591 15593 15595 15597 15599 15601 15603 15629 15633)

nfirst=1
nlast=-1
nrun=100

for processID in ${processIDs[*]};
do
    data_input=/group/ilc/users/yokugawa/QQbar250/l5/eLpR/${processID}/dEdx_corr/QQbarProcessor_out/

    flist=list/${processID}.list
    `find ${data_input} -maxdepth 1 -name *${processID}*.root | sort > ${flist}`

    nf=`more ${flist} | wc -l`
    echo "number of files for process : " ${nf}

    if [ ${nlast} -le 0 ] || [ ${nlast} -ge ${nf} ] ; then
        nlast=${nf}
    fi

    njobs=$[($nlast-$nfirst)/$nrun+1]
    seqlist=`seq 1 $njobs`
    for seq in $seqlist; do
        nrun0=$[$nfirst+$nrun*($seq-1)]
        nrun1tmp=$[$nrun0+$nrun-1]
        
        if [ $nrun1tmp -le $nlast ] ; then
        nrun1=$nrun1tmp
        else
        nrun1=$nlast
        fi
        
        echo ${processID} $nrun0 $nrun1 $nrun $njobs

        if [ $processID -eq 15271 ]
        then
            log=./sublog/${processID}"_"`printf %03d $seq`.log
            bsub -q s -J "ana_"${processID}"_"`printf %03d $seq` -o $log "./runROOT ${flist} $nrun0 $nrun1"
        else
            bsub -q s -J "ana_"${processID}"_"`printf %03d $seq` "./runROOT ${flist} $nrun0 $nrun1"
        fi

    done

done


