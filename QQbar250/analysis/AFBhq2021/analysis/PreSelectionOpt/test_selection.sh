
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

for file in ${folder}/*
do
    echo $file $counter
    name="00"$counter
    if [ $counter -gt 9 ]; then
        name="0"$counter
    fi
    
    if [ $counter -gt 99 ]; then
        name=$counter
    fi

    for cuts in {0..8}
    do

	cat > ${local}/steer/sel_${process}_${pol}_${name}_cuts${cuts}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l ${local}/test_selection.cc\(\"${file}\",\"${process}\",\"${pol}\",${counter},${cuts},35,$bkg\) > ${local}/output/log_sel_${process}_${pol}_${name}_cuts${cuts}
mv *cuts${cuts}_${process}_${pol}_file_${name}_250GeV.root ${local}/output/.
EOF
	
	cat > ${local}/steer/sel_${process}_${pol}_${name}_cuts${cuts}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/sel_${process}_${pol}_${name}_cuts${cuts}.sh
log                     = ${local}/log/sel_${process}_${pol}_${name}_cuts${cuts}.log
output                  = ${local}/log/outfile_sel_${process}_${pol}_${name}_cuts${cuts}.txt
error                   = ${local}/log/errors_sel_${process}_${pol}_${name}_cuts${cuts}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
	
	if [ -f ${local}/output/selection_cuts${cuts}_${process}_${pol}_file_${name}_250GeV.root ];
        then
            echo "Skip ${process}_${pol}_${name}_cuts${cuts}"
        else	
	    condor_submit ${local}/steer/sel_${process}_${pol}_${name}_cuts${cuts}.sub
	fi
    done
	
    counter=$((counter+1))

done



