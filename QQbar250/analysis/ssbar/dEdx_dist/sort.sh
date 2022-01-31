#!/bin/sh

cd /group/ilc/users/yokugawa/QQbar250/l5/eLpR/15162/dEdx_corr/QQbarProcessor_out/

for i in *.root; do
  filename=$(basename -- "$i")
  filename="${filename%.*}"

  filenumber=$(echo $filename| cut -d'_' -f 9)
  suffix_removed_string=${filename/%${filenumber}}
  filenumber=$(printf "%03d" "${filenumber}")

  newfilename="${suffix_removed_string}${filenumber}.root"

  echo "mv" ${i} ${newfilename}

  mv $i ${newfilename}

done

cd -