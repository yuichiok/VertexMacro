# List of Files
1. `DQ_250GeV_qq.minp10maxp60.distcut.polar.test.root`
2. `DQ_250GeV_qq.minp10.distcut.polar.test.root`
3. `DQ_250GeV_qq.minp10.distcut.polar.hit210.root`
4. `DQ_250GeV_qq.minp10maxp60.distcut.polar.hit210.root`
---
**Double Tag**

5. `double_tag/DQ_250GeV_qq.minp10maxp60.hit210.offset.dEdxMin.root`
6. `double_tag/DQ_250GeV_qq.minp10maxp60.hit210.offset.dEdxMin.cheat.root`
7. `double_tag/DQ_250GeV_qq.minp20maxp60.hit210.offset.dEdxMin.root`
8. `double_tag/DQ_250GeV_qq.nocut.root`
9. `double_tag/DQ_250GeV_qq.minp20maxp60.hit210.offset0.25.dEdxMin.root`
---
**Full Stats**

10. `double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.mergeFULL.root`
11. `double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppMult.mergeFULL.root`
12. `double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.OppMult.neutral.mergeFULL.root`
13. `double_tag/DQ_250GeV_ss.minp20maxp60.hit210.offset.dEdxMin.neutral.mergeFULL.root`

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
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)
- -1.5 < kdEdx_dist < 2.0

### Notes
- Set this as base cut. Change from here.


# File 2

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO
- Both PFO should have momentum window **10 < Lead PFO mom**
- Lead PFO charge +- or -+
- Compensate hit numbers for different acceptance region:
  - (       cos < 0.75) 210 < Lead PFO hits
  - (0.75 < cos < 0.90) (210 + (210 - 50) * (cos - 0.75) / (0.75 - 0.9)) < Lead PFO hits
  - (0.90 < cos       )  50 < Lead PFO hits
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)
- -1.5 < kdEdx_dist < 2.0

### Notes
- mom windown 10\<p\<60 -> 10\<p 


# File 3

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO
- Both PFO should have momentum window **10 < Lead PFO mom**
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)
- -1.5 < kdEdx_dist < 2.0

### Notes
- mom windown 10\<p\<60 -> 10\<p
- TPC hits -> changed from base


# File 4

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
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)
- -1.5 < kdEdx_dist < 2.0

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...

---

# Double Tag

# File 5

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO (double tag)
- Both PFO should have momentum window 10 < Lead PFO mom < 60
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...

# File 6

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO (double tag)
- Both PFO should have momentum window 10 < Lead PFO mom < 60
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...
- **Ignore migrations**

# File 7

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO (double tag)
- Both PFO should have momentum window **20 < Lead PFO mom < 60**
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...

# File 8

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO (double tag)
- No cut

### Notes
- No cut on Lead PFO

# File 9

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO (double tag)
- Both PFO should have momentum window **20 < Lead PFO mom < 60**
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- **Offset cut < 0.25**
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...

# File 10

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO (double tag)
- Both PFO should have momentum window **20 < Lead PFO mom < 60**
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...
- Full Stats

# File 11

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- \# PFO tracks == 1 (more than 2 tracks cannot be associated to make 1 PFO)

### Lead PFO (double tag)
- Both PFO should have momentum window **20 < Lead PFO mom < 60**
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)
- **SPFO Kaon number**

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...
- Full Stats

# File 12

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- **removed # PFO track cut** (will include neutrals)

### Lead PFO (double tag)
- Both PFO should have momentum window **20 < Lead PFO mom < 60**
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)
- **SPFO Kaon number**

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...
- Full Stats

# File 13

## Cut MC

### ISR suppression
- QQ cos sep > 0.95
- 120 < QQ mom < 127

## Cut PFO

### General PFO
- PFO match (It should fall into either jet0 or jet1)
- **removed # PFO track cut** (will include neutrals)

### Lead PFO (double tag)
- Both PFO should have momentum window **20 < Lead PFO mom < 60**
- Lead PFO charge +- or -+
- \# TPC hits **210 < Lead PFO hits**
- Offset cut < 1.0
- kdEdx_dist < (pdEdx_dist & pidEdx_dist)

### Notes
- TPC hits -> changed from base
- Added pfo_LeadK_qcos_kaon, proton, ...
- Full Stats