Kt=35

for cuts in {11..12}
do
    root -l analysis.cc\(\"eL\",\"15162\",$cuts,35,0.8,0.8\) > log_bkg_35_analysis_eL_15162_cuts${cuts}  &
done
