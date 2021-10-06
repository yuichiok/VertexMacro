import math

def calc_sep(mean0,mean1,sig0,sig1):
	a = abs(mean0 * mean0 - mean1 * mean1)
	b = math.sqrt( (sig0*sig0 + sig1*sig1)/2.0 )
	return a/b

mean_uu0 = 0.113605
mean_uu1 = -0.103795
sig_uu0 = 0.182987
sig_uu1 = 0.180841

sep_uu = calc_sep(mean_uu0,mean_uu1,sig_uu0,sig_uu1)
print(sep_uu)

mean_ss0 = -8.51189E-2
mean_ss1 = 9.07059E-2
sig_ss0 = 1.78358E-1
sig_ss1 = 1.77752E-1

sep_ss = calc_sep(mean_ss0,mean_ss1,sig_ss0,sig_ss1)
print(sep_ss)