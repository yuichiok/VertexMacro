# List of Files
1. DQ_250GeV_qq.minp10maxp60.distcut.polar.test.root
2. DQ_250GeV_qq.minp10.distcut.polar.test.root

# File 1

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO
- Both PFO should have momentum window 10 < Lead PFO mom < 60
- Lead PFO charge +- or -+
- Compensate hit numbers for different acceptance region:
  - (       cos < 0.75) 210 < Lead PFO hits
  - (0.75 < cos < 0.90) (210 + (210 - 50) * (cos - 0.75) / (0.75 - 0.9)) < Lead PFO hits
  - (0.90 < cos       )  50 < Lead PFO hits
- Offset cut > 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)
- -1.5 < kdEdx_dist < 2.0