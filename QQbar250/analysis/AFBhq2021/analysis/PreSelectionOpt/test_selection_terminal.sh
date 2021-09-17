
process=$1
pol=$2
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/"${process}"_"${pol}"/"
local=$PWD
counter=0

bkg=1

if [ "$process" = "2f_hadronic_sample" ];
then 
    bkg=0
fi

cuts=5
counter=1
name="001"
root -l ${local}/test_selection.cc\(\"${file}\",\"${process}\",\"${pol}\",${counter},${cuts},35,$bkg\) > ${local}/output/log_sel_${process}_${pol}_${name}_cuts${cuts}



