for pol in "eL_pR" "eR_pL" 
do
    for pdg in 4 5
    do
	hadd results/Rq_pdg${pdg}_4f_ZZ_hadronic_${pol}_250GeV.root output/Rq_pdg${pdg}_4f_ZZ_hadronic_${pol}_*250GeV.root &
	hadd results/Rq_pdg${pdg}_2f_hadronic_sample_${pol}_250GeV.root output/Rq_pdg${pdg}_2f_hadronic_sample_${pol}_*250GeV.root &
	hadd results/Rq_pdg${pdg}_2f_hadronic_${pol}_250GeV.root output/Rq_pdg${pdg}_2f_hadronic_${pol}_*250GeV.root
	hadd results/Rq_pdg${pdg}_qqH_${pol}_250GeV.root output/Rq_pdg${pdg}_qqH_${pol}_*250GeV.root &
	hadd results/Rq_pdg${pdg}_4f_WW_hadronic_${pol}_250GeV.root output/Rq_pdg${pdg}_4f_WW_hadronic_${pol}_*250GeV.root
    done
done



