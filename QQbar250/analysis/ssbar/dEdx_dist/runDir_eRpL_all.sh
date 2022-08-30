#!/bin/sh

nfirst=1
nlast=-1
nrun=3

data_input=/group/ilc/users/yokugawa/QQbar250/l5/eRpL/2f_hadronic_eR_pL/

flist=list/2f_hadronic_eR_pL.list
`find ${data_input} -maxdepth 1 -name 2f_hadronic_eR_pL*.root | sort > ${flist}`

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
    
    echo $nrun0 $nrun1 $nrun $njobs

    log=./sublog/"2f_hadronic_eR_pL_"`printf %03d $seq`.log
    bsub -q s -J "ana_2f_hadronic_eR_pL_"`printf %03d $seq` -o $log "./runROOT ${flist} $nrun0 $nrun1"

done



