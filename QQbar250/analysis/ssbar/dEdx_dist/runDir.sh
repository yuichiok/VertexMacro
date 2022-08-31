#!/bin/sh

# data_input=/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/
data_input=/sps/ilc/yokugawa/QQbar250/l5/eLpR/00015162/QQbarProcessor_out/

nfirst=1
nlast=-1
nrun=200

flist=list/15162.list

`find ${data_input} -maxdepth 1 -name '*15162*.root' | sort > ${flist}`

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
    
    echo ${id} $nrun0 $nrun1 $nrun $njobs

    log=./sublog/`printf %03d $seq`.log
    # bsub -q s -J "ana"`printf %03d $seq` -o $log "./runROOT ${flist} $nrun0 $nrun1"
    srun -J "ana"`printf %03d $seq` ./runROOT ${flist} $nrun0 $nrun1 -o $log
done