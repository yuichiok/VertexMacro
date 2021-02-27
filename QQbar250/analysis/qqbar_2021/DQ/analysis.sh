#!/bin/bash

filein=/group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/proc_2021/QQbarProcessor_out/root_merge/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500010.P2f_z_h.eL.pR.15162.MERGE50.root

root -l -q DQChecks.cc\(\"$filein\",\"15162\"\)

# root -l -q DQChecks.cc\(\"/home/airqui/cernbox/QQbar/processor_output_2021/merged_15161_eLpR.root\",\"15161\"\) &
# root -l -q DQChecks.cc\(\"/home/airqui/cernbox/QQbar/processor_output_2021/merged_15162_eLpR.root\",\"15162\"\)
#root -l -q DQChecks.cc\(\"/home/airqui/cernbox/QQbar/processor_output_2021/merged_15271_eLpR.root\",\"15271\"\) &
#root -l -q DQChecks.cc\(\"/home/airqui/cernbox/QQbar/processor_output_2021/merged_15273_eLpR.root\",\"15273\"\)


#mv *root DQplots/.
