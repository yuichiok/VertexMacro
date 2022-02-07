#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define dEdx_dist_cxx
#include "dEdx_dist.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <fstream>

// see math/mathcore/src/PdfFuncMathCore.cxx in ROOT 6.x
double crystalball_function(double x, double alpha, double n, double sigma, double mean) {
  // evaluate the crystal ball function
  if (sigma < 0.)     return 0.;
  double z = (x - mean)/sigma; 
  if (alpha < 0) z = -z; 
  double abs_alpha = std::abs(alpha);
  // double C = n/abs_alpha * 1./(n-1.) * std::exp(-alpha*alpha/2.);
  // double D = std::sqrt(M_PI/2.)*(1.+ROOT::Math::erf(abs_alpha/std::sqrt(2.)));
  // double N = 1./(sigma*(C+D));
  if (z  > - abs_alpha)
    return std::exp(- 0.5 * z * z);
  else {
    //double A = std::pow(n/abs_alpha,n) * std::exp(-0.5*abs_alpha*abs_alpha);
    double nDivAlpha = n/abs_alpha;
    double AA =  std::exp(-0.5*abs_alpha*abs_alpha);
    double B = nDivAlpha -abs_alpha;
    double arg = nDivAlpha/(B-z);
    return AA * std::pow(arg,n);
  }
}

double crystalball_function(const double *x, const double *p) {
  // if ((!x) || (!p)) return 0.; // just a precaution
  // [Constant] * ROOT::Math::crystalball_function(x, [Alpha], [N], [Sigma], [Mean])
  return (p[0] * crystalball_function(x[0], p[3], p[4], p[2], p[1]));
}

void dEdx_dist::printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void dEdx_dist::Analyze_dEdxdist(int n_entries=-1, float MINP_CUT=10.0, TString process="test", TString fileout="out")
{

	float MAXP_CUT=60.0;

	// MC Histograms

	TString name_mc_stable = "h_mc_stable_";

	// TH1F
	TH1F* mc_nk_evt  = new TH1F(name_mc_stable+"nKaons_evt",";nKaons/Evt; Events",20,0,20);
	TH1F* mc_qq_cos  = new TH1F("h_mc_quark_cos",";cos#theta; Entries",100,-1.0,1.0);

	h1_mc_stable.push_back( mc_nk_evt );
	h1_mc_stable.push_back( mc_qq_cos );

	// TH2F



	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F

	// vertex position
  TH1F * pfo_pv_kaon     = new TH1F(name_pfo+"pv_kaon", "pv_kaon", 40, 0, 4.0);
  TH1F * pfo_pv_pion     = new TH1F(name_pfo+"pv_pion", "pv_pion", 40, 0, 4.0);
  TH1F * pfo_pv_proton   = new TH1F(name_pfo+"pv_proton", "pv_proton", 40, 0, 4.0);

  // dEdx distance from kaon bethe-bloch
  TH1F * pfo_kdEdx_dist_kaon     = new TH1F(name_pfo+"kdEdx_dist_kaon", "kdEdx_dist_kaon", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_proton   = new TH1F(name_pfo+"kdEdx_dist_proton", "kdEdx_dist_proton", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_pion     = new TH1F(name_pfo+"kdEdx_dist_pion", "kdEdx_dist_pion", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_electron = new TH1F(name_pfo+"kdEdx_dist_electron", "kdEdx_dist_electron", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_muon     = new TH1F(name_pfo+"kdEdx_dist_muon", "kdEdx_dist_muon", 40, -10, 10);
  TH1F * pfo_kdEdx_dist_others   = new TH1F(name_pfo+"kdEdx_dist_others", "kdEdx_dist_others", 40, -10, 10);

  // dEdx distance from pion bethe-bloch
  TH1F * pfo_pidEdx_dist_kaon     = new TH1F(name_pfo+"pidEdx_dist_kaon", "pidEdx_dist_kaon", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_proton   = new TH1F(name_pfo+"pidEdx_dist_proton", "pidEdx_dist_proton", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_pion     = new TH1F(name_pfo+"pidEdx_dist_pion", "pidEdx_dist_pion", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_electron = new TH1F(name_pfo+"pidEdx_dist_electron", "pidEdx_dist_electron", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_muon     = new TH1F(name_pfo+"pidEdx_dist_muon", "pidEdx_dist_muon", 40, -10, 10);
  TH1F * pfo_pidEdx_dist_others   = new TH1F(name_pfo+"pidEdx_dist_others", "pidEdx_dist_others", 40, -10, 10);

  // dEdx distance from proton bethe-bloch
  TH1F * pfo_pdEdx_dist_kaon     = new TH1F(name_pfo+"pdEdx_dist_kaon", "pdEdx_dist_kaon", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_proton   = new TH1F(name_pfo+"pdEdx_dist_proton", "pdEdx_dist_proton", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_pion     = new TH1F(name_pfo+"pdEdx_dist_pion", "pdEdx_dist_pion", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_electron = new TH1F(name_pfo+"pdEdx_dist_electron", "pdEdx_dist_electron", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_muon     = new TH1F(name_pfo+"pdEdx_dist_muon", "pdEdx_dist_muon", 40, -10, 10);
  TH1F * pfo_pdEdx_dist_others   = new TH1F(name_pfo+"pdEdx_dist_others", "pdEdx_dist_others", 40, -10, 10);

  // Kaon polar angle
	TH1F* pfo_LeadK_qcos			     = new TH1F(name_pfo+"LeadKaons_cos",";cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_kaon	     = new TH1F(name_pfo+"LeadKaons_cos_kaon","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_proton	   = new TH1F(name_pfo+"LeadKaons_cos_proton","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_pion	     = new TH1F(name_pfo+"LeadKaons_cos_pion","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_electron	 = new TH1F(name_pfo+"LeadKaons_cos_electron","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_muon	     = new TH1F(name_pfo+"LeadKaons_cos_muon","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_others	   = new TH1F(name_pfo+"LeadKaons_cos_others","Polar Angle Cheat;cos#theta; Events",100,-1.0,1.0);

	TH1F* pfo_LeadK_psum					 = new TH1F(name_pfo+"LeadKaons_psum",";cos#theta; Events",100,-1.0,1.0);

	// Migrated Events
	// wrong
	TH1F* pfo_qq_qcos_wrong 		   = new TH1F(name_pfo+"QQ_cos_wrong",";cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_wrong 		 = new TH1F(name_pfo+"LeadKaons_cos_wrong",";cos#theta; Events",100,-1.0,1.0);
	TH1F* pfo_LeadK_qcos_sep_wrong = new TH1F(name_pfo+"LeadKaons_cos_sep_wrong",";|cos#theta_{0} - cos#theta_{1}|; Events",40,0,4.0);
	TH1F* pfo_LeadK_pdiff_wrong		 = new TH1F(name_pfo+"LeadKaons_pdiff_wrong",";|p_{diff}| (GeV); Events", 40,0,40);
	TH1F* pfo_LeadK_ip_wrong		   = new TH1F(name_pfo+"LeadKaons_ip_wrong",";Impact Parameter (cm); Events", 50,0,0.5);

	TH1F* pfo_nKaons_wrong0				 = new TH1F(name_pfo+"nKaons_wrong0","Kaon mult wrong per Jet;nKaon/Jet0; Events",10,0,10);
	TH1F* pfo_nKaons_wrong1				 = new TH1F(name_pfo+"nKaons_wrong1","Kaon mult wrong per Jet;nKaon/Jet1; Events",10,0,10);

	TH1F* pfo_nSignK_wrong0				 = new TH1F(name_pfo+"nSignK_wrong0","Kaon mult wrong per Jet;nKaon/Jet0; Events",10,0,10);
	TH1F* pfo_nSignK_wrong1				 = new TH1F(name_pfo+"nSignK_wrong1","Kaon mult wrong per Jet;nKaon/Jet1; Events",10,0,10);

	TH1F* pfo_nSignKopp_wrong0		 = new TH1F(name_pfo+"nSignKopp_wrong0","Kaon mult wrong per Jet;nKaon/Jet0; Events",10,0,10);
	TH1F* pfo_nSignKopp_wrong1		 = new TH1F(name_pfo+"nSignKopp_wrong1","Kaon mult wrong per Jet;nKaon/Jet1; Events",10,0,10);

	TH1F* pfo_SignKopp_p_wrong		 = new TH1F(name_pfo+"SignKopp_p_wrong",";Momentum (GeV); Events", 100, 0, 100);

	// correct
	TH1F* pfo_LeadK_qcos_sep_correct = new TH1F(name_pfo+"LeadKaons_cos_sep_correct",";|cos#theta_{0} - cos#theta_{1}|; Events",40,0,4.0);
	TH1F* pfo_LeadK_pdiff_correct		 = new TH1F(name_pfo+"LeadKaons_pdiff_correct",";p diff (GeV); Events", 40,0,40);
	TH1F* pfo_LeadK_ip_correct	     = new TH1F(name_pfo+"LeadKaons_ip_correct",";Impact Parameter (cm); Events", 50,0,0.5);

	TH1F* pfo_nKaons_correct0				 = new TH1F(name_pfo+"nKaons_correct0","Kaon mult correct per Jet;nKaon/Jet0; Events",10,0,10);
	TH1F* pfo_nKaons_correct1				 = new TH1F(name_pfo+"nKaons_correct1","Kaon mult correct per Jet;nKaon/Jet1; Events",10,0,10);

	TH1F* pfo_nSignK_correct0				 = new TH1F(name_pfo+"nSignK_correct0","Kaon mult correct per Jet;nKaon/Jet0; Events",10,0,10);
	TH1F* pfo_nSignK_correct1				 = new TH1F(name_pfo+"nSignK_correct1","Kaon mult correct per Jet;nKaon/Jet1; Events",10,0,10);

	TH1F* pfo_nSignKopp_correct0		 = new TH1F(name_pfo+"nSignKopp_correct0","Kaon mult correct per Jet;nKaon/Jet0; Events",10,0,10);
	TH1F* pfo_nSignKopp_correct1		 = new TH1F(name_pfo+"nSignKopp_correct1","Kaon mult correct per Jet;nKaon/Jet1; Events",10,0,10);

	TH1F* pfo_SignKopp_p_correct		 = new TH1F(name_pfo+"SignKopp_p_correct",";Momentum (GeV); Events", 100, 0, 100);



  // push_back hists
  h1_pfo.push_back( pfo_pv_kaon );
  h1_pfo.push_back( pfo_pv_pion );
  h1_pfo.push_back( pfo_pv_proton );

	h1_pfo.push_back( pfo_kdEdx_dist_kaon );
	h1_pfo.push_back( pfo_kdEdx_dist_proton );
	h1_pfo.push_back( pfo_kdEdx_dist_pion );
	h1_pfo.push_back( pfo_kdEdx_dist_electron );
	h1_pfo.push_back( pfo_kdEdx_dist_muon );
	h1_pfo.push_back( pfo_kdEdx_dist_others );

	h1_pfo.push_back( pfo_pidEdx_dist_kaon );
	h1_pfo.push_back( pfo_pidEdx_dist_proton );
	h1_pfo.push_back( pfo_pidEdx_dist_pion );
	h1_pfo.push_back( pfo_pidEdx_dist_electron );
	h1_pfo.push_back( pfo_pidEdx_dist_muon );
	h1_pfo.push_back( pfo_pidEdx_dist_others );

	h1_pfo.push_back( pfo_pdEdx_dist_kaon );
	h1_pfo.push_back( pfo_pdEdx_dist_proton );
	h1_pfo.push_back( pfo_pdEdx_dist_pion );
	h1_pfo.push_back( pfo_pdEdx_dist_electron );
	h1_pfo.push_back( pfo_pdEdx_dist_muon );
	h1_pfo.push_back( pfo_pdEdx_dist_others );

	h1_pfo.push_back( pfo_LeadK_qcos );
	h1_pfo.push_back( pfo_LeadK_qcos_kaon );
	h1_pfo.push_back( pfo_LeadK_qcos_proton );
	h1_pfo.push_back( pfo_LeadK_qcos_pion );
	h1_pfo.push_back( pfo_LeadK_qcos_electron );
	h1_pfo.push_back( pfo_LeadK_qcos_muon );
	h1_pfo.push_back( pfo_LeadK_qcos_others );

	h1_pfo.push_back( pfo_qq_qcos_wrong );
	h1_pfo.push_back( pfo_LeadK_qcos_wrong );

	h1_pfo.push_back( pfo_LeadK_qcos_sep_wrong );
	h1_pfo.push_back( pfo_LeadK_pdiff_wrong );
	h1_pfo.push_back( pfo_LeadK_ip_wrong );
	h1_pfo.push_back( pfo_SignKopp_p_wrong );

	h1_pfo.push_back( pfo_nKaons_wrong0 );
	h1_pfo.push_back( pfo_nKaons_wrong1 );

	h1_pfo.push_back( pfo_nSignK_wrong0 );
	h1_pfo.push_back( pfo_nSignK_wrong1 );

	h1_pfo.push_back( pfo_nSignKopp_wrong0 );
	h1_pfo.push_back( pfo_nSignKopp_wrong1 );	

	h1_pfo.push_back( pfo_LeadK_qcos_sep_correct );
	h1_pfo.push_back( pfo_LeadK_pdiff_correct );
	h1_pfo.push_back( pfo_LeadK_ip_correct );
	h1_pfo.push_back( pfo_SignKopp_p_correct );

	h1_pfo.push_back( pfo_nKaons_correct0 );
	h1_pfo.push_back( pfo_nKaons_correct1 );

	h1_pfo.push_back( pfo_nSignK_correct0 );
	h1_pfo.push_back( pfo_nSignK_correct1 );

	h1_pfo.push_back( pfo_nSignKopp_correct0 );
	h1_pfo.push_back( pfo_nSignKopp_correct1 );	



	// TH2F

	// dEdx dist
  TH2F * pfo_p_kdEdx_dist_kaon 			= new TH2F(name_pfo+"p_kdEdx_dist_kaon", "p_kdEdx_dist_kaon", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_proton 		= new TH2F(name_pfo+"p_kdEdx_dist_proton", "p_kdEdx_dist_proton", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_pion 			= new TH2F(name_pfo+"p_kdEdx_dist_pion", "p_kdEdx_dist_pion", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_electron  = new TH2F(name_pfo+"p_kdEdx_dist_electron", "p_kdEdx_dist_electron", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_muon 			= new TH2F(name_pfo+"p_kdEdx_dist_muon", "p_kdEdx_dist_muon", 100, 0.5, 100.5, 40, -10, 10);
  TH2F * pfo_p_kdEdx_dist_others 		= new TH2F(name_pfo+"p_kdEdx_dist_others", "p_kdEdx_dist_others", 100, 0.5, 100.5, 40, -10, 10);

  // dEdx vs p
  float momentum_min=0.95;
  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.5,3,4,5,6,7,8,9,10,12,14,16,18,20,24,28,32,36,40,44,48,52,56,60,64,68,72,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[200];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
  Int_t nbinnumy=199;

  TH2F* pfo_p_dEdx_kaon     = new TH2F(name_pfo+"p_dEdx_kaon","p_dEdx_kaon",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pfo_p_dEdx_proton   = new TH2F(name_pfo+"p_dEdx_proton","p_dEdx_proton",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pfo_p_dEdx_pion     = new TH2F(name_pfo+"p_dEdx_pion","p_dEdx_pion",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pfo_p_dEdx_electron = new TH2F(name_pfo+"p_dEdx_electron","p_dEdx_electron",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pfo_p_dEdx_muon     = new TH2F(name_pfo+"p_dEdx_muon","p_dEdx_muon",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pfo_p_dEdx_others     = new TH2F(name_pfo+"p_dEdx_others","p_dEdx_others",nbinnum_p,bins_p,nbinnumy,binsy);


  // Migrated Events
  TH2F * pfo_LeadK_pdg_wrong 	 = new TH2F(name_pfo+"LeadK_pdg_wrong","LeadK_pdg_wrong;LPFO0;LPFO1",3,0,3,3,0,3);
  pfo_LeadK_pdg_wrong->SetCanExtend(TH1::kAllAxes);

  TH2F * pfo_LeadK_p_wrong 		 = new TH2F(name_pfo+"LeadK_p_wrong","LeadK_p_wrong;p LPFO0 (GeV);p LPFO1 (GeV)",100,0.5,100.5,100,0.5,100.5);
  TH2F * pfo_LeadK_p_correct 	 = new TH2F(name_pfo+"LeadK_p_correct","LeadK_p_correct;p LPFO0 (GeV);p LPFO1 (GeV)",100,0.5,100.5,100,0.5,100.5);

  // dEdx vs p (wrong)
  TH2F* pfo_LeadK_p_dEdx_wrong     = new TH2F(name_pfo+"LeadK_p_dEdx_wrong","LeadK_p_dEdx_wrong",nbinnum_p,bins_p,nbinnumy,binsy);


  // push_back hists
  h2_pfo.push_back( pfo_p_kdEdx_dist_kaon );
  h2_pfo.push_back( pfo_p_kdEdx_dist_proton );
  h2_pfo.push_back( pfo_p_kdEdx_dist_pion );
  h2_pfo.push_back( pfo_p_kdEdx_dist_electron );
  h2_pfo.push_back( pfo_p_kdEdx_dist_muon );
  h2_pfo.push_back( pfo_p_kdEdx_dist_others );

  h2_pfo.push_back( pfo_p_dEdx_kaon );
  h2_pfo.push_back( pfo_p_dEdx_proton );
  h2_pfo.push_back( pfo_p_dEdx_pion );
  h2_pfo.push_back( pfo_p_dEdx_electron );
  h2_pfo.push_back( pfo_p_dEdx_muon );
  h2_pfo.push_back( pfo_p_dEdx_others );

  h2_pfo.push_back( pfo_LeadK_pdg_wrong );
  h2_pfo.push_back( pfo_LeadK_p_wrong );
  h2_pfo.push_back( pfo_LeadK_p_correct );

  h2_pfo.push_back( pfo_LeadK_p_dEdx_wrong );


	std::stringstream stream_min;
	std::stringstream stream_max;
	stream_min << std::fixed << std::setprecision(0) << MINP_CUT;
	stream_max << std::fixed << std::setprecision(0) << MAXP_CUT;
	TString minp_it = stream_min.str();
	TString maxp_it = stream_max.str();
	cout << "MINP = " << minp_it << endl;
	cout << "MAXP = " << maxp_it << endl;

	process = process;



	// Use for Merging

	// Double Tag
	// TString filename_out = TString::Format("DQ_250GeV_%s.minp%smaxp%s.hit210.offset.dEdxMin",process.Data(),minp_it.Data(),maxp_it.Data());

	// Offset Change
	// TString filename_out = TString::Format("DQ_250GeV_%s.minp%smaxp%s.hit210.offset0.25.dEdxMin",process.Data(),minp_it.Data(),maxp_it.Data());

	// no cut on lead PFO
	// TString filename_out = TString::Format("DQ_250GeV_%s.nocut",process.Data(),minp_it.Data(),maxp_it.Data());

	// TString filename_out = TString::Format("DQ_250GeV_%s.minp%smaxp%s.hit210.offset.dEdxMin.cheat",process.Data(),minp_it.Data(),maxp_it.Data());



	// TString filename_out_root = "rootfiles/double_tag/" + filename_out + ".root";

	TString filename_out_root = fileout;
	TString filename_out = "test";

	// test mode
	bool debug = 0;
	if(debug) filename_out_root = "rootfiles/double_tag/test.root";



	TFile *MyFile = new TFile(filename_out_root,"RECREATE");

	MyFile->cd();

	TString tmp_str  = "data/" + filename_out + ".txt";
	TString tmp_str2 = "data/" + filename_out + ".true.txt";
	ofstream LeadKDataFile (tmp_str.Data());
	ofstream TrueDataFile  (tmp_str2.Data());

	if (fChain == 0) return;



	//////////////////////////////////
	///////   EVENT ANALYSIS   ///////
	//////////////////////////////////

	// const float MINP_CUT = 10.;

	// pdg ratio
	int kaon_dEdx_cheat_same0 = 0;
	int kaon_dEdx_cheat_same1 = 0;
	int kaon_dEdx_cheat_all  = 0;


	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {


		if (debug)
		{
			// if(jentry>100000) break;
			if(jentry>90000) break;
		}

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		// Progress bar
		// if ( jentry > 10000 && jentry % 10000 == 0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

		// Comment on batch mode
		// printProgress( static_cast<double>(jentry) / (double)(1.0 * nentries) );

		nevents_all++;

		if(process=="uds" && (fabs(mc_quark_pdg[0])==4 || fabs(mc_quark_pdg[0])==5) ) continue; // ignore MC b/c quarks
		if(process=="uu"  && fabs(mc_quark_pdg[0])!=2) continue; // ignore MC other than uu
		if(process=="ss"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss
		if(process=="dd"  && fabs(mc_quark_pdg[0])!=1) continue; // ignore MC other than dd
		if(process=="default"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss

		// if(mc_ISR_E[0] + mc_ISR_E[1]>35) continue; 


		nevents++;


		////////////////////////////////
		//////   MC QQ ANALYSIS   //////
		////////////////////////////////

		std::vector<VecOP> qqVecs;

		for(int iqq=0; iqq < 2; iqq++){

			VecOP qqVec(mc_quark_px[iqq],mc_quark_py[iqq],mc_quark_pz[iqq]);
			qqVecs.push_back(qqVec);

		}

		// Cut qq with qq separation
		float qqsep = VecOP::getAngleBtw(qqVecs.at(0).GetMomentum3(),qqVecs.at(1).GetMomentum3());
		float qqqcos[2]={-2};


		// ISR protection
		if(abs(cos(qqsep)) < 0.95) continue;

		if( qqVecs.at(0).GetMomentum() < 120 || qqVecs.at(0).GetMomentum() > 127 ) continue;
		if( qqVecs.at(1).GetMomentum() < 120 || qqVecs.at(1).GetMomentum() > 127 ) continue;

		nevents_after_GENselec++;

		for(int iqq=0; iqq < 2; iqq++){

			float cos 	 			= qqVecs.at(iqq).GetCostheta();
			float charge 			= mc_quark_charge[iqq];
			qqqcos[iqq] 			= (charge < 0)? cos: -cos;

			mc_qq_cos->Fill(qqqcos[iqq]);

		}


		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		// Compare qqbar
		int qq_match = -1;
		int qq_match_count[2] = {0};

		// Leading PFO variables
		int   lead_ipfo[2]	= {-1};
		float maxP[2]				= {0};

		// Count N Kaons
		int n_reco_kaon_all     = 0;
		int n_reco_signK_jet[2][2] = {0};
		vector <float> signKopp_p_jet[2][2];

		struct JetParam {
			vector<int> id;
			vector<float> mom;
			vector<float> dEdx_dist;
		}

		JetParam SPFOs[2];


		for(int ipfo=0; ipfo<pfo_n; ipfo++) {

			if(pfo_match[ipfo]<0 || pfo_match[ipfo]==2) continue;
			if(pfo_ntracks[ipfo]!=1) continue;

			VecOP pfoVec(pfo_px[ipfo],pfo_py[ipfo],pfo_pz[ipfo]);
			float mom    = pfoVec.GetMomentum();


			// Jet Analysis

			if(abs(pfo_pdgcheat[ipfo])==321) n_reco_kaon_all++;
			
			for (int imatch = 0; imatch < 2; ++imatch)
			{
				if(pfo_match[ipfo]==imatch){

					if(pfo_pdgcheat[ipfo]==321){

						if(mom>10.0) n_reco_signK_jet[imatch][0]++;

						signKopp_p_jet[imatch][0].push_back(mom);

					}else if(pfo_pdgcheat[ipfo]==-321){

						if(mom>10.0) n_reco_signK_jet[imatch][1]++;

						signKopp_p_jet[imatch][1].push_back(mom);

					}


					if(mom > maxP[imatch]){
						maxP[imatch] = mom;
						lead_ipfo[imatch] = ipfo;
					}


				} // end jet imatch
			} // end imatch


		} // end of pfo

		if(lead_ipfo[0]==-1 || lead_ipfo[1]==-1) continue;
		nevents_after_PFOselec++;


		///////////////////////////////
		//////   Jet ANALYSIS   ///////
		///////////////////////////////
		
		std::vector<VecOP> jetVecs;

		for (int ijet = 0; ijet < 2; ++ijet){
		
			VecOP jetVec(jet_px[ijet],jet_py[ijet],jet_pz[ijet]);
			jetVecs.push_back(jetVec);
		
		}


		///////////////////////////////////////
		//////   Leading PFOs ANALYSIS   //////
		///////////////////////////////////////

		std::vector<VecOP> LeadPFOVecs;

		struct PFOParam {
			float dEdx;
			float kdEdx_dist;
			float pdEdx_dist;
			float pidEdx_dist;
			float chg;
			float pv;
			float tpc_hits;
			int   pdg_cheat;
			float mom;
			float cos;
			float qcos;
			float q_sep;
			float qbar_sep;
		};

		PFOParam LPFO[2] = {
			{0, 0, 0, 0, 0, -1, -1, 0, 0, -2, -2, 0, 0},
			{0, 0, 0, 0, 0, -1, -1, 0, 0, -2, -2, 0, 0}
		};

		for (int i = 0; i < 2; ++i){

			int lpfo = lead_ipfo[i];
		
			VecOP LeadPFOVec(pfo_px[lpfo],pfo_py[lpfo],pfo_pz[lpfo]);
		
			LPFO[i].dEdx				= pfo_dedx[lpfo];
			LPFO[i].kdEdx_dist  = pfo_piddedx_k_dedxdist[lpfo];
			LPFO[i].pdEdx_dist  = pfo_piddedx_p_dedxdist[lpfo];
			LPFO[i].pidEdx_dist = pfo_piddedx_pi_dedxdist[lpfo];

			LPFO[i].chg					= pfo_charge[lpfo];
			LPFO[i].pv  				= sqrt( pfo_d0[lpfo]*pfo_d0[lpfo] + pfo_z0[lpfo]*pfo_z0[lpfo] );
			LPFO[i].tpc_hits		= pfo_tpc_hits[lpfo];
			LPFO[i].pdg_cheat 	= pfo_pdgcheat[lpfo];

			LPFO[i].mom 				= LeadPFOVec.GetMomentum();
			LPFO[i].cos					= LeadPFOVec.GetCostheta();
			LPFO[i].qcos 				= (LPFO[i].chg < 0)? LPFO[i].cos: -LPFO[i].cos;

			// This compares pfo angle with MC angle -> giving which this pfo are from. 
			// 0: PFO is from q
			// 1: PFO is from qbar

			LPFO[i].q_sep    = VecOP::getAngleBtw(LeadPFOVec.GetMomentum3(),qqVecs.at(0).GetMomentum3());
			LPFO[i].qbar_sep = VecOP::getAngleBtw(LeadPFOVec.GetMomentum3(),qqVecs.at(1).GetMomentum3());

			LeadPFOVecs.push_back(LeadPFOVec);


		}

		// LEAD PFO SEPARATION
		float lead_abs_cos_sep = VecOP::getAngleBtw(LeadPFOVecs.at(0).GetMomentum3(),LeadPFOVecs.at(1).GetMomentum3());
		float lead_abs_pdiff   = abs(LPFO[0].mom-LPFO[1].mom);
		
		// CHARGE CHECK
    bool chg_check = false;
		bool kchg_configs[4] = {0};
		kchg_configs[0] = ( (LPFO[0].chg<0) && (LPFO[1].chg>0) ) ? true : false;
		kchg_configs[1] = ( (LPFO[0].chg>0) && (LPFO[1].chg<0) ) ? true : false;
		kchg_configs[2] = ( (LPFO[0].chg>0) && (LPFO[1].chg>0) ) ? true : false;
		kchg_configs[3] = ( (LPFO[0].chg<0) && (LPFO[1].chg<0) ) ? true : false;

    if(kchg_configs[0] || kchg_configs[1]) chg_check = true;

		// MOMENTUM CHECK
		// bool mom_check = ( maxP[0]>MINP_CUT && maxP[1]>MINP_CUT ) ? true : false;
		bool mom_check = ( maxP[0]>MINP_CUT && maxP[1]>MINP_CUT
										 && maxP[0]<MAXP_CUT && maxP[1]<MAXP_CUT ) ? true : false;

		// TPC HIT CHECK
		bool nhits_check = false;
    if (LPFO[0].tpc_hits > 210 && LPFO[1].tpc_hits > 210) nhits_check = true;

    // OFFSET CHECK
    bool offset_check = false;
    if( LPFO[0].pv<1.0 && LPFO[1].pv<1.0 ) offset_check = true;
    // if( LPFO[0].pv<0.25 && LPFO[1].pv<0.25 ) offset_check = true;

    // DEDX DISTANCE MINIMUM
    bool dEdx_dist_min_check   = false;
    bool pdEdx_dist_min_check  = false;
    bool pidEdx_dist_min_check = false;
    if( (abs(LPFO[0].kdEdx_dist) < abs(LPFO[0].pdEdx_dist))  && (abs(LPFO[1].kdEdx_dist) < abs(LPFO[1].pdEdx_dist))  ) pdEdx_dist_min_check  = true;
    if( (abs(LPFO[0].kdEdx_dist) < abs(LPFO[0].pidEdx_dist)) && (abs(LPFO[1].kdEdx_dist) < abs(LPFO[1].pidEdx_dist)) ) pidEdx_dist_min_check = true;
    if( pdEdx_dist_min_check && pidEdx_dist_min_check ) dEdx_dist_min_check = true;

    // DEDX DISTANCE WINDOW
    bool dEdx_dist_win_check = false;
		float min_dist=-1.5;
		// float max_dist=0.5;
		float max_dist=2.0;
    if( (LPFO[0].kdEdx_dist>min_dist&&LPFO[0].kdEdx_dist<max_dist)
    	&&(LPFO[1].kdEdx_dist>min_dist&&LPFO[1].kdEdx_dist<max_dist) ) dEdx_dist_win_check = true;


    bool check_all = false;
		// if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check && dEdx_dist_win_check ) check_all = true;
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check ) check_all = true;
		// if( 1 ) check_all = true;

		// Stats
		if( chg_check ) n_chg_check++;
		if( chg_check && mom_check ) n_chg_mom_check++;
		if( chg_check && mom_check && nhits_check ) n_chg_mom_nhits_check++;
		if( chg_check && mom_check && nhits_check && offset_check ) n_chg_mom_nhits_offset_check++;
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check ) n_chg_mom_nhits_offset_DistMin_check++;
		if( chg_check && mom_check && nhits_check && offset_check && dEdx_dist_min_check && dEdx_dist_win_check ) n_chg_mom_nhits_offset_DistMin_DistWin_check++;



		if (check_all)
		{

			if(debug){
				// cout << "Event# " << nevents_all <<"\t total PFO K = " << n_reco_kaon_all << "\t jet0 nK = " << n_reco_kaon_jet[0] << "\t jet1 nK = " << n_reco_kaon_jet[1] << endl;
				cout << "Event# " << nevents_all <<"\t total PFO K = " << n_reco_kaon_all << "\t jet0 nK = " << n_reco_signK_jet[0][0]+n_reco_signK_jet[0][1] << "\t jet1 nK = " << n_reco_signK_jet[1][0]+n_reco_signK_jet[1][1] << endl;
			}

			// count number of when the reco is WRONG (source of migration)
			bool flag0=false;
			bool flag1=false;
			if( (LPFO[0].q_sep<LPFO[0].qbar_sep) && (LPFO[0].chg>0) ) flag0=true;
			if( (LPFO[0].q_sep>LPFO[0].qbar_sep) && (LPFO[0].chg<0) ) flag0=true;
			if( (LPFO[1].q_sep<LPFO[1].qbar_sep) && (LPFO[1].chg>0) ) flag1=true;
			if( (LPFO[1].q_sep>LPFO[1].qbar_sep) && (LPFO[1].chg<0) ) flag1=true;


			// MIGRATED EVENTS

			if(flag0&&flag1){
					cout << "<< double wrong event " << nevents_all << " >>" << endl;
					// cout << "nstable = " << mc_stable_n  << endl;

					if(debug){
						for (int i = 0; i < mc_stable_n; ++i)
						{
							if(!mc_stable_isoverlay[i]) cout << mc_stable_pdg[i] << ", " << sqrt(mc_stable_px[i]*mc_stable_px[i]+mc_stable_py[i]*mc_stable_py[i]+mc_stable_pz[i]*mc_stable_pz[i]) <<endl;
						}
					}
			}

			if(flag0||flag1){

				n_cos_nonconsis++;
				// continue;
				float enu0 = enumerate_pdg(LPFO[0].pdg_cheat);
				float enu1 = enumerate_pdg(LPFO[1].pdg_cheat);

				pfo_qq_qcos_wrong->Fill(qqqcos[0]);
				pfo_qq_qcos_wrong->Fill(qqqcos[1]);
				pfo_LeadK_qcos_wrong->Fill(LPFO[0].qcos);
				pfo_LeadK_qcos_wrong->Fill(LPFO[1].qcos);

				pfo_LeadK_pdg_wrong->Fill(enu0,enu1);
				pfo_LeadK_p_wrong->Fill(LPFO[0].mom,LPFO[1].mom);

				pfo_LeadK_qcos_sep_wrong->Fill(lead_abs_cos_sep);
				pfo_LeadK_pdiff_wrong->Fill(lead_abs_pdiff);

				pfo_LeadK_ip_wrong->Fill(LPFO[0].pv);
				pfo_LeadK_ip_wrong->Fill(LPFO[1].pv);

				pfo_LeadK_p_dEdx_wrong->Fill(LPFO[0].mom,LPFO[0].dEdx);
				pfo_LeadK_p_dEdx_wrong->Fill(LPFO[1].mom,LPFO[1].dEdx);

				if(flag0) pfo_nKaons_wrong0->Fill(n_reco_signK_jet[0][0]+n_reco_signK_jet[0][1]);
				if(flag1) pfo_nKaons_wrong1->Fill(n_reco_signK_jet[1][0]+n_reco_signK_jet[1][1]);


				// Number of K same chg as LPFO
				if(LPFO[0].chg>0){

					pfo_nSignK_wrong0->Fill(n_reco_signK_jet[0][0]);

				}else if(LPFO[0].chg<0){

					pfo_nSignK_wrong0->Fill(n_reco_signK_jet[0][1]);

				}

				if(LPFO[1].chg>0){

					pfo_nSignK_wrong1->Fill(n_reco_signK_jet[1][0]);

				}else if(LPFO[1].chg<0){

					pfo_nSignK_wrong1->Fill(n_reco_signK_jet[1][1]);

				}


				// Number of K opposite chg as LPFO
				if(abs(LPFO[0].pdg_cheat)==321){

					if(LPFO[0].chg>0){

						pfo_nSignKopp_wrong0->Fill(n_reco_signK_jet[0][1]);

						for (int i = 0; i < signKopp_p_jet[0][1].size(); ++i)
						{
							if( maxP[0]!=signKopp_p_jet[0][1].at(i) ) pfo_SignKopp_p_wrong->Fill(signKopp_p_jet[0][1].at(i));
						}

						if(signKopp_p_jet[0][1].size()==0) pfo_SignKopp_p_wrong->Fill(0);

					}else if(LPFO[0].chg<0){

						pfo_nSignKopp_wrong0->Fill(n_reco_signK_jet[0][0]);

						for (int i = 0; i < signKopp_p_jet[0][0].size(); ++i)
						{
							if( maxP[0]!=signKopp_p_jet[0][0].at(i) ) pfo_SignKopp_p_wrong->Fill(signKopp_p_jet[0][0].at(i));
						}

						if(signKopp_p_jet[0][0].size()==0) pfo_SignKopp_p_wrong->Fill(0);						

					}

				}


				if(abs(LPFO[1].pdg_cheat)==321){

					if(LPFO[1].chg>0){

						pfo_nSignKopp_wrong1->Fill(n_reco_signK_jet[1][1]);

						for (int i = 0; i < signKopp_p_jet[1][1].size(); ++i)
						{
							if( maxP[1]!=signKopp_p_jet[1][1].at(i) ) pfo_SignKopp_p_wrong->Fill(signKopp_p_jet[1][1].at(i));
						}

						if(signKopp_p_jet[1][1].size()==0) pfo_SignKopp_p_wrong->Fill(0);

					}else if(LPFO[1].chg<0){

						pfo_nSignKopp_wrong1->Fill(n_reco_signK_jet[1][0]);

						for (int i = 0; i < signKopp_p_jet[1][0].size(); ++i)
						{
							if( maxP[1]!=signKopp_p_jet[1][0].at(i) ) pfo_SignKopp_p_wrong->Fill(signKopp_p_jet[1][0].at(i));
						}

						if(signKopp_p_jet[1][0].size()==0) pfo_SignKopp_p_wrong->Fill(0);

					}

				}


				if(debug) cout << "MIGRATION:";

			}else{

				pfo_LeadK_p_correct->Fill(LPFO[0].mom,LPFO[1].mom);
				pfo_LeadK_qcos_sep_correct->Fill(lead_abs_cos_sep);
				pfo_LeadK_pdiff_correct->Fill(lead_abs_pdiff);

				pfo_LeadK_ip_correct->Fill(LPFO[0].pv);
				pfo_LeadK_ip_correct->Fill(LPFO[1].pv);

				pfo_nKaons_correct0->Fill(n_reco_signK_jet[0][0]+n_reco_signK_jet[0][1]);
				pfo_nKaons_correct1->Fill(n_reco_signK_jet[1][0]+n_reco_signK_jet[1][1]);

				// Number of K same chg as LPFO
				if(LPFO[0].chg>0){

					pfo_nSignK_correct0->Fill(n_reco_signK_jet[0][0]);

				}else if(LPFO[0].chg<0){

					pfo_nSignK_correct0->Fill(n_reco_signK_jet[0][1]);

				}

				if(LPFO[1].chg>0){

					pfo_nSignK_correct1->Fill(n_reco_signK_jet[1][0]);

				}else if(LPFO[1].chg<0){

					pfo_nSignK_correct1->Fill(n_reco_signK_jet[1][1]);

				}


				// Number of K opposite chg as LPFO
				if(abs(LPFO[0].pdg_cheat)==321){

					if(LPFO[0].chg>0){

						pfo_nSignKopp_correct0->Fill(n_reco_signK_jet[0][1]);

						for (int i = 0; i < signKopp_p_jet[0][1].size(); ++i)
						{
							if( maxP[0]!=signKopp_p_jet[0][1].at(i) ) pfo_SignKopp_p_correct->Fill(signKopp_p_jet[0][1].at(i));
						}

						if(signKopp_p_jet[0][1].size()==0) pfo_SignKopp_p_correct->Fill(0);

					}else if(LPFO[0].chg<0){

						pfo_nSignKopp_correct0->Fill(n_reco_signK_jet[0][0]);
						
						for (int i = 0; i < signKopp_p_jet[0][0].size(); ++i)
						{
							if( maxP[0]!=signKopp_p_jet[0][1].at(i) ) pfo_SignKopp_p_correct->Fill(signKopp_p_jet[0][0].at(i));
						}

						if(signKopp_p_jet[0][0].size()==0) pfo_SignKopp_p_correct->Fill(0);

					}

				}


				if(abs(LPFO[0].pdg_cheat)==321){				

					if(LPFO[1].chg>0){

						pfo_nSignKopp_correct1->Fill(n_reco_signK_jet[1][1]);

						for (int i = 0; i < signKopp_p_jet[1][1].size(); ++i)
						{
							if( maxP[1]!=signKopp_p_jet[1][1].at(i) ) pfo_SignKopp_p_correct->Fill(signKopp_p_jet[1][1].at(i));
						}

						if(signKopp_p_jet[1][1].size()==0) pfo_SignKopp_p_correct->Fill(0);

					}else if(LPFO[1].chg<0){

						pfo_nSignKopp_correct1->Fill(n_reco_signK_jet[1][0]);

						for (int i = 0; i < signKopp_p_jet[1][0].size(); ++i)
						{
							if( maxP[1]!=signKopp_p_jet[1][0].at(i) ) pfo_SignKopp_p_correct->Fill(signKopp_p_jet[1][0].at(i));
						}

						if(signKopp_p_jet[1][0].size()==0) pfo_SignKopp_p_correct->Fill(0);

					}

				}


				if(debug) cout << "CONSIS:";
			}

			if(debug){
				// cout << " qcos=" << qqqcos[0] << "\tqbarcos=" << qqqcos[1] << "\tcos0=" << LPFO[0].qcos << "\tcos1=" << LPFO[1].qcos << "\t lead_pdg0=" << LPFO[0].pdg_cheat << "\t lead_pdg1=" <<  LPFO[1].pdg_cheat << "\t lead_sep=" << lead_sep << endl;
				cout << " mom0=" << LPFO[0].mom << "\t mom1=" << LPFO[1].mom << "\t |mom_diff|=" << abs(LPFO[0].mom-LPFO[1].mom)/abs(LPFO[0].mom+LPFO[1].mom) << endl;
				cout << " ip0=" << LPFO[0].pv << "\t ip1=" << LPFO[1].pv << endl;
			}



			// ANALYZE RECO KAON ID EVENTS

			for (int i = 0; i < 2; ++i)
			{
	      if (debug)
	      {
	      	cout << "Lead PFO " << i << ": q sep=" << LPFO[i].q_sep << "\t qqbar sep=" << LPFO[i].qbar_sep << "\t lead chg=" << LPFO[i].chg << "\t lead pdg=" << LPFO[i].pdg_cheat << endl;
	      }
	      LeadKDataFile << LPFO[i].qcos << ',' << LPFO[i].mom << ',' << LPFO[i].chg << ',' << LPFO[i].dEdx << ',' << LPFO[i].kdEdx_dist << '\n';

				pfo_LeadK_qcos->Fill(LPFO[i].qcos);

				switch(abs(LPFO[i].pdg_cheat)){

					case 321:		// kaon

						TrueDataFile << LPFO[i].qcos << ',' << LPFO[i].mom << ',' << LPFO[i].chg << ',' << LPFO[i].dEdx << ',' << LPFO[i].kdEdx_dist << '\n';

			      // pfo_LeadK_qcos->Fill(LPFO[i].qcos);

						pfo_kdEdx_dist_kaon->Fill(LPFO[i].kdEdx_dist);
						pfo_pdEdx_dist_kaon->Fill(LPFO[i].pdEdx_dist);
						pfo_pidEdx_dist_kaon->Fill(LPFO[i].pidEdx_dist);

						pfo_LeadK_qcos_kaon->Fill(LPFO[i].qcos);
						pfo_p_kdEdx_dist_kaon->Fill(LPFO[i].mom,LPFO[i].kdEdx_dist);
						pfo_p_dEdx_kaon->Fill(LPFO[i].mom,LPFO[i].dEdx);
						pfo_pv_kaon->Fill(LPFO[i].pv);
						break;

					case 211:		// pion
						pfo_kdEdx_dist_pion->Fill(LPFO[i].kdEdx_dist);
						pfo_pdEdx_dist_pion->Fill(LPFO[i].pdEdx_dist);
						pfo_pidEdx_dist_pion->Fill(LPFO[i].pidEdx_dist);

						pfo_LeadK_qcos_pion->Fill(LPFO[i].qcos);
						pfo_p_kdEdx_dist_pion->Fill(LPFO[i].mom,LPFO[i].kdEdx_dist);
						pfo_p_dEdx_pion->Fill(LPFO[i].mom,LPFO[i].dEdx);
						pfo_pv_pion->Fill(LPFO[i].pv);
						break;

					case 2212:	// proton
						pfo_kdEdx_dist_proton->Fill(LPFO[i].kdEdx_dist);
						pfo_pdEdx_dist_proton->Fill(LPFO[i].pdEdx_dist);
						pfo_pidEdx_dist_proton->Fill(LPFO[i].pidEdx_dist);

						pfo_LeadK_qcos_proton->Fill(LPFO[i].qcos);
						pfo_p_kdEdx_dist_proton->Fill(LPFO[i].mom,LPFO[i].kdEdx_dist);
						pfo_p_dEdx_proton->Fill(LPFO[i].mom,LPFO[i].dEdx);
						pfo_pv_proton->Fill(LPFO[i].pv);
						break;

					case 11:		// electron
						pfo_kdEdx_dist_electron->Fill(LPFO[i].kdEdx_dist);
						pfo_pdEdx_dist_electron->Fill(LPFO[i].pdEdx_dist);
						pfo_pidEdx_dist_electron->Fill(LPFO[i].pidEdx_dist);

						pfo_LeadK_qcos_electron->Fill(LPFO[i].qcos);
						pfo_p_kdEdx_dist_electron->Fill(LPFO[i].mom,LPFO[i].kdEdx_dist);
						pfo_p_dEdx_electron->Fill(LPFO[i].mom,LPFO[i].dEdx);
						break;

					case 13:		// muon
						pfo_kdEdx_dist_muon->Fill(LPFO[i].kdEdx_dist);
						pfo_pdEdx_dist_muon->Fill(LPFO[i].pdEdx_dist);
						pfo_pidEdx_dist_muon->Fill(LPFO[i].pidEdx_dist);

						pfo_LeadK_qcos_muon->Fill(LPFO[i].qcos);
						pfo_p_kdEdx_dist_muon->Fill(LPFO[i].mom,LPFO[i].kdEdx_dist);
						pfo_p_dEdx_muon->Fill(LPFO[i].mom,LPFO[i].dEdx);
						break;

					default:

						if(debug) cout << "other PID = " << LPFO[i].pdg_cheat << endl;

						pfo_kdEdx_dist_others->Fill(LPFO[i].kdEdx_dist);
						pfo_pdEdx_dist_others->Fill(LPFO[i].pdEdx_dist);
						pfo_pidEdx_dist_others->Fill(LPFO[i].pidEdx_dist);

						pfo_LeadK_qcos_others->Fill(LPFO[i].qcos);
						pfo_p_kdEdx_dist_others->Fill(LPFO[i].mom,LPFO[i].kdEdx_dist);
						pfo_p_dEdx_others->Fill(LPFO[i].mom,LPFO[i].dEdx);
						break;

				} // switch

			} // Loop Lead PFO

		}// check all


	} // end of event loop

	// printProgress( 1.0 );
	// std::cout << std::endl;


	printResults();

	for(int h=0; h < h1_mc_stable.size(); h++) h1_mc_stable.at(h)->Write();
	for(int h=0; h < h2_mc_stable.size(); h++) h2_mc_stable.at(h)->Write();

	for(int h=0; h < h1_pfo.size(); h++) h1_pfo.at(h)->Write();
	for(int h=0; h < h2_pfo.size(); h++) h2_pfo.at(h)->Write();

	LeadKDataFile.close();
	TrueDataFile.close();


}

void dEdx_dist::printResults(){

	cout << "========= Event Results =========" << "\n";
	cout << "Process: " << process << "\n";
	cout << "# Events:                     " << nevents << "\n";
	cout << "# Events after GEN selection: " << nevents_after_GENselec << "\n";
	cout << "# Events after PFO selection: " << nevents_after_PFOselec << "\n";
	
	cout << "# Events after LeadK selection (Both LeadPFO should satisfy):" << "\n";
	cout << " - Charge check:              " << n_chg_check << "\n";
	cout << " - Momentum check:            " << n_chg_mom_check << "\n";
	cout << " - TPC hit check:             " << n_chg_mom_nhits_check << "\n";
	cout << " - Offset check:              " << n_chg_mom_nhits_offset_check << "\n";
	cout << " - dEdx dist min check:       " << n_chg_mom_nhits_offset_DistMin_check << "\n";
	cout << " - dEdx dist win check:       " << n_chg_mom_nhits_offset_DistMin_DistWin_check << "\n";

	cout << endl;
	cout << "migration: " << n_cos_nonconsis << "\n";

	// // std::cout << "# Events Kaon: " << nevents_kaon_match << "\n";
	// std::cout << "LeadK_match: " << nLeadK_match << " LeadK_pass: " << nLeadK_pass << "\n";
	// std::cout << "Kaon purity: " << (float)nLeadK_match / (float)nLeadK_pass << "\n";
	// std::cout << "n_kk: " << n_kk << " n_kpkm: " << n_kpkm << " n_kpkp:" << n_kpkp << " n_kmkm:" << n_kmkm << "\n";

 }



 void dEdx_dist::LeadingMom(TH1F* h1p = 0, TH1F* h1m = 0, TH2F* h2 = 0, int subject = 0, int iPFO0 = 0, int iPFO1 = 0, float P0 = -2, float P1 = -2) {

 	// are leading PFOs Kaons?
 	// if( fabs(pfo_pdgcheat[iPFO0]) == subject && fabs(pfo_pdgcheat[iPFO1]) == subject ){
 	if( fabs(pfo_piddedx[iPFO0]) == subject && fabs(pfo_piddedx[iPFO1]) == subject ){

 		float multchg = pfo_charge[iPFO0] * pfo_charge[iPFO1];
 		bool signPM = (multchg < 0) ? true : false;

 		if(signPM){

 			if(pfo_charge[iPFO0] > 0){

 				h1p->Fill(P0);
 				h1m->Fill(P1);

 				h2->Fill(P1,P0);

 			}else if(pfo_charge[iPFO0] < 0){

 				h1p->Fill(P1);
 				h1m->Fill(P0);

 				h2->Fill(P0,P1);

 			}

 		} // end sign check

 	} // end Leading Kaon check

 }


 bool dEdx_dist::PreSelection(int type=0,float Kvcut=25) {

   if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;

   if(type == 0 ) return true;

   //---------------------
   //Radiative return cuts, photon not in the detector

   double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

   TVector3 v1(jet_px[0],jet_py[0],jet_pz[0]);
   TVector3 v2(jet_px[1],jet_py[1],jet_pz[1]);
   VecOP vop;
   float acol=vop.GetSinacol(v1,v2);

   double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
   double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

   float costheta_j0;
   VecOP p_j0(jet_px[0],jet_py[0],jet_pz[0]);
   costheta_j0 = fabs(p_j0.GetCostheta());

   float costheta_j1;
   VecOP p_j1(jet_px[1],jet_py[1],jet_pz[1]);
   costheta_j1 = fabs(p_j1.GetCostheta());

   float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));
   float K1=jet0_p*acol/sqrt(1-costheta_j1*costheta_j1);
   float K2=jet1_p*acol/sqrt(1-costheta_j0*costheta_j0);

   if(type == 1 )  if( Kv < Kvcut ) return true;
   if(type == 2 )  if( Kv < Kvcut && bbmass>130 )  return true;



   return false;
 } 

 float dEdx_dist::enumerate_pdg(const int pdg=0){

 	switch(abs(pdg)){
		
		case 211:		// pion
			return 0;
			break;
		case 321:		// kaon
			return 1;
			break;
		case 2212:	// proton
			return 2;
			break;
		default:
			return 3;
			break;
 	}

 }
