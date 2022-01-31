#!/bin/sh

data_input=/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/

nfirst=1
nlast=-1
nrun=3

flist=list/test.list

`find /group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out -maxdepth 1 -name '*15162*.root' | sort > ${flist}`

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
    
    # log=./sublog/${id}"_"`printf %03d $seq`.log
    # bsub -q s -J "ana"`printf %03d $seq` -o $log "./runMarlin2 ${flist} $nrun0 $nrun1 $inputxml $model $chiral $id"
done

echo "yay!"