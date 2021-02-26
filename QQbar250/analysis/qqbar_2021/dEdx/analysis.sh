#!/bin/bash

start_time=`date +%s`

filein=/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/proc_2021/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.MERGE50.root

root -l -q analysis.cc\(\"$filein\",\"test\",true,true\) &
root -l -q analysis.cc\(\"$filein\",\"test\",true,false\)

root -l -q analysis.cc\(\"$filein\",\"test\",false,true\) &
root -l -q analysis.cc\(\"$filein\",\"test\",false,false\) 

end_time=`date +%s`

time=$((end_time - start_time))

echo $time
