
process=$1
pol=$2
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/"${process}"_"${pol}"/"
local=$PWD
counter=0


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

    for cuts in 6
    do

	cat > ${local}/steer/jettag_${process}_${pol}_${name}_cuts${cuts}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l ${local}/test_jettag.cc\(\"${file}\",\"${process}\",\"${pol}\",${counter},${cuts},35\) > ${local}/output/log_jettag_${process}_${pol}_${name}_cuts${cuts}
mv *cuts${cuts}_${process}_${pol}_file_${name}_250GeV.root ${local}/output/.
EOF
	
	cat > ${local}/steer/jettag_${process}_${pol}_${name}_cuts${cuts}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/jettag_${process}_${pol}_${name}_cuts${cuts}.sh
log                     = ${local}/log/jettag_${process}_${pol}_${name}_cuts${cuts}.log
output                  = ${local}/log/outfile_jettag_${process}_${pol}_${name}_cuts${cuts}.txt
error                   = ${local}/log/errors_jettag_${process}_${pol}_${name}_cuts${cuts}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
	
	if [ -f ${local}/output/jettag_cuts${cuts}_${process}_${pol}_file_${name}_250GeV.root ];
        then
            echo "Skip ${process}_${pol}_${name}_cuts${cuts}"
        else	
	    condor_submit ${local}/steer/jettag_${process}_${pol}_${name}_cuts${cuts}.sub
	fi
    done
	
    counter=$((counter+1))

done



