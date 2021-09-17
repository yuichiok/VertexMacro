#for cut in "0" "1" "2" "4" "5"
#do
#    for pol in "eL_pR" "eR_pL"
#    do
#	hadd -f results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_${cut}GeV.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_${cut}_cquark.root
#	hadd -f results/histos_bquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_${cut}GeV.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_${cut}_bquark.root
#    done
#done

for cut in "0" "1" "2" "4" "5"
do
    for pol in "eL_pR" "eR_pL"
    do
        hadd -f results/histos_cquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_${cut}GeV_costheta_lt08.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_${cut}_cquark_costheta_lt08.root
        hadd -f results/histos_bquark_secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}_${cut}GeV_costheta_lt08.root output/*secondary_tracks_ignoreoverlay_2f_hadronic_sample_${pol}*cut_${cut}_bquark_costheta_lt08.root
    done
done
