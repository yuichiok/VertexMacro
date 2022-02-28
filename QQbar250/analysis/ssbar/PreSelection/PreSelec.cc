#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define PreSelec_cxx
#include "PreSelec.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <fstream>

void PreSelec::PreSelection(int n_entries=-1, float MINP_CUT=10.0, TString process="test", TString fileout="out")
{

	float MAXP_CUT=60.0;

	// Number Counting
	TH1I* cnt_nevents   = new TH1I("h_cnt_nevents",";nevents;Entries",10,0,10);
	TH1I* cnt_ISRevents = new TH1I("h_cnt_ISRevents",";isr events;Entries",10,0,10);

	_h0_counter.push_back(cnt_nevents);
	_h0_counter.push_back(cnt_ISRevents);

	// MC Histograms

	TString name_mc_stable = "h_mc_stable_";
	TString name_mc 			 = "h_mc_";

	// TH1F
	TH1F* h_mc_nk_evt  = new TH1F(name_mc_stable+"nKaons_evt",";nKaons/Evt; Events",20,0,20);
	TH1F* h_mc_qq_cos  = new TH1F(name_mc+"quark_cos",";cos#theta; Entries",100,-1.0,1.0);

	// ISR parameters
	TH1F* h_mc_visibleE = new TH1F(name_mc+"visibleE", ";Visible Energy (GeV);", 100, 0, 300);
	TH1F* h_mc_QQsep  	= new TH1F(name_mc+"QQsep", ";QQ sep |cos#theta|;", 100, 0, 1);


	_h1_mc_stable.push_back( h_mc_nk_evt );
	_h1_mc_stable.push_back( h_mc_qq_cos );

	_h1_mc_stable.push_back( h_mc_visibleE );
	_h1_mc_stable.push_back( h_mc_QQsep );

	// TH2F



	// Reco Histograms

	TString name_pfo = "h_pfo_";

	// TH1F

	// ISR parameters
	TH1F* h_pfo_visibleE = new TH1F(name_pfo+"visibleE", ";Visible Energy (GeV);", 100, 0, 300);
	TH1F* h_pfo_Jetsep   = new TH1F(name_pfo+"Jetsep", ";Jet sep |cos#theta|;", 100, 0, 1);

	// push_back hists
	_h1_pfo.push_back( h_pfo_visibleE );
	_h1_pfo.push_back( h_pfo_Jetsep );


	// TH2F

	std::stringstream stream_min;
	std::stringstream stream_max;
	stream_min << std::fixed << std::setprecision(0) << MINP_CUT;
	stream_max << std::fixed << std::setprecision(0) << MAXP_CUT;
	TString minp_it = stream_min.str();
	TString maxp_it = stream_max.str();
	cout << "MINP = " << minp_it << endl;
	cout << "MAXP = " << maxp_it << endl;

	process = process;

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


	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		if(process=="uds" && (fabs(mc_quark_pdg[0])==4 || fabs(mc_quark_pdg[0])==5) ) continue; // ignore MC b/c quarks
		if(process=="uu"  && fabs(mc_quark_pdg[0])!=2) continue; // ignore MC other than uu
		if(process=="ss"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss
		if(process=="dd"  && fabs(mc_quark_pdg[0])!=1) continue; // ignore MC other than dd
		if(process=="default"  && fabs(mc_quark_pdg[0])!=3) continue; // ignore MC other than ss


		////////////////////////////////
		//////   MC QQ ANALYSIS   //////
		////////////////////////////////

		std::vector<VecOP> qqVecs;
		float mc_InvM[2] = {-1,-1};

		for(int iqq=0; iqq < 2; iqq++){

			VecOP qqVec(mc_quark_px[iqq],mc_quark_py[iqq],mc_quark_pz[iqq]);
			qqVecs.push_back(qqVec);

		}

		VecOP qqAddVec = VecOP::AddVec(qqVecs.at(0),qqVecs.at(1));

		float mc_qq_E = mc_quark_E[0]+mc_quark_E[1];
		float mc_qq_InvM = GetInvMass(mc_qq_E,qqAddVec.GetMomentum3());
		

		////////////////////////////////
		///////   PFO ANALYSIS   ///////
		////////////////////////////////

		for(int ipfo=0; ipfo<pfo_n; ipfo++) {



		} // end of pfo



		///////////////////////////////
		//////   Jet ANALYSIS   ///////
		///////////////////////////////
		
		std::vector<VecOP> jetVecs;
		float jet_InvM[2] = {-1,-1};

		for (int ijet = 0; ijet < 2; ++ijet){
		

		} // end of jet




	} // end of event loop

	printResults();

	for(int h=0; h < _h0_counter.size(); h++) _h0_counter.at(h)->Write();

	for(int h=0; h < _h1_mc_stable.size(); h++) _h1_mc_stable.at(h)->Write();
	for(int h=0; h < _h2_mc_stable.size(); h++) _h2_mc_stable.at(h)->Write();

	for(int h=0; h < _h1_pfo.size(); h++) _h1_pfo.at(h)->Write();
	for(int h=0; h < _h2_pfo.size(); h++) _h2_pfo.at(h)->Write();

	LeadKDataFile.close();
	TrueDataFile.close();


}

float PreSelec::GetInvMass(float E=0, vector<float> p3 = {}){

	float p32 = 0;
	for (int i = 0; i < 3; ++i)
	{
		p32 += p3.at(i)*p3.at(i);
	}

	float InvM = sqrt( E*E - p32 );
	return InvM;

}

void PreSelec::printResults(){

	cout << "print event result" << endl;


}