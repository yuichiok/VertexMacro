

file="15162"

root -l -q analysis.cc\(\"${file}\",true,true\) > log/log_correction_${file} &
root -l -q analysis.cc\(\"${file}\",true,false\) > log/log_nocorrection_${file}





