import ROOT
from ROOT import gROOT, gDirectory, gPad, gSystem, gStyle
from ROOT import TCanvas, TFile, TProfile, TNtuple, TH1F, TH2F, THStack, TLegend

gROOT.ProcessLine(
	"struct data_t{\
	Float_t mc_quark_E[2];\
	Float_t mc_quark_px[2];\
	Float_t mc_quark_py[2];\
	Float_t mc_quark_pz[2];\
	};"
	)