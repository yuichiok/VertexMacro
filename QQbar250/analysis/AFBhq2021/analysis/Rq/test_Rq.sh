
process=$1
pol=$2
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/"${process}"_"${pol}"/"
local=$PWD
counter=0

bkg=$3


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

    for pdg in 4 5
    do

	cat > ${local}/steer/rq_${process}_${pol}_${name}_pdg${pdg}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l ${local}/test_Rq.cc\(\"${file}\",\"${process}\",\"${pol}\",${counter},${pdg},35,$bkg\) > ${local}/output/log_rq_${process}_${pol}_${name}_pdg${pdg}
mv Rq_pdg${pdg}_${process}_${pol}_file_${name}_250GeV.root ${local}/output/.
EOF
	
	cat > ${local}/steer/rq_${process}_${pol}_${name}_pdg${pdg}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/rq_${process}_${pol}_${name}_pdg${pdg}.sh
log                     = ${local}/log/rq_${process}_${pol}_${name}_pdg${pdg}.log
output                  = ${local}/log/outfile_rq_${process}_${pol}_${name}_pdg${pdg}.txt
error                   = ${local}/log/errors_rq_${process}_${pol}_${name}_pdg${pdg}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
	
	if [ -f ${local}/output/Rq_pdg${pdg}_${process}_${pol}_file_${name}_250GeV.root ];
        then
            echo "Skip ${process}_${pol}_${name}_pdg${pdg}"
        else	
	    condor_submit ${local}/steer/rq_${process}_${pol}_${name}_pdg${pdg}.sub
	fi
    done
	
    counter=$((counter+1))

done



