
process="2f_hadronic_sample"
for pol in "eL_pR" "eR_pL"
do
    echo $pol
    folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/"${process}"_"${pol}"/"
    local=$PWD
    counter=0

    for quark in 4 5
    do
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
	    
	    for cut in 0 1 2 4 5
	    do
		cat > ${local}/steer/run_${process}_${pol}_${name}_${cut}_${quark}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l -q ${local}/analysis.cc\(\"${file}\",\"${process}_${pol}_${name}\",true,${cut},${quark}\) 
sleep 1
#mv ${local}/output_250_secondary_tracks_ignoreoverlay_${process}_${pol}_${name}*.root ${local}/output/.
EOF
		
		cat > ${local}/steer/run_${process}_${pol}_${name}_${cut}_${quark}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/run_${process}_${pol}_${name}_${cut}_${quark}.sh
log                     = ${local}/log/run_${process}_${pol}_${name}_${cut}_${quark}.log
output                  = ${local}/log/outfile_run_${process}_${pol}_${name}_${cut}_${quark}.txt
error                   = ${local}/log/errors_run_${process}_${pol}_${name}_${cut}_${quark}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
		condor_submit ${local}/steer/run_${process}_${pol}_${name}_${cut}_${quark}.sub
	    done
	    counter=$((counter+1))
	done
    done
done



