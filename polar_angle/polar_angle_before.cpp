
float LorentzF( float energy, float mass){
	return energy/mass ;
}


void AddAFBvalue( float input, int& plus , int& minus ){
	if( input > 0 ){
		plus++ ;
	}else{
		minus++ ;
	}
}

float getAFB( int plus, int minus ){
	return 1.0*(plus-minus)/(plus+minus) ;
}

void FillandAdd( int b1 = 0, int b2 = 0, float tcos1 = 0, float tcos2 = 0, float bcos1 = 0, float bcos2 = 0, int& tpl, int& tmi = 0, int& bpl, int& bmi, double weight = 0, TH1F* top = 0, TH1F* bottom = 0){

		if( b1 < 0 ){  //Top1 = top, Top2 = antitop, Top1b = bottom, Top2b = antibottom
			top->Fill( tcos1, weight ) ;
			top->Fill( -tcos2, weight ) ;
			bottom->Fill( bcos1, weight ) ;
			bottom->Fill( -bcos2, weight ) ;
			AddAFBvalue( tcos1, tpl, tmi ) ;
			AddAFBvalue( -tcos2, tpl, tmi ) ;
			AddAFBvalue( bcos1, bpl, bmi ) ;
			AddAFBvalue( -bcos2, bpl, bmi ) ;
		}else if( b1 > 0 ){  //Top1 = antitop, Top2 = top, Top1b = antibottom, Top2b = bottom
			top->Fill( -tcos1, weight ) ;
			top->Fill( tcos2, weight ) ;
			bottom->Fill( -bcos1, weight ) ;
			bottom->Fill( bcos2, weight ) ;
			AddAFBvalue( -tcos1, tpl, tmi ) ;
			AddAFBvalue( tcos2, tpl, tmi ) ;
			AddAFBvalue( -bcos1, bpl, bmi ) ;
			AddAFBvalue( bcos2, bpl, bmi ) ;
		}else if( b2 > 0 ){  //Top1 = top, Top2 = antitop, Top1b = bottom, Top2b = antibottom
			top->Fill( tcos1, weight ) ;
			top->Fill( -tcos2, weight ) ;
			bottom->Fill( bcos1, weight ) ;
			bottom->Fill( -bcos2, weight ) ;
			AddAFBvalue( tcos1, tpl, tmi ) ;
			AddAFBvalue( -tcos2, tpl, tmi ) ;
			AddAFBvalue( bcos1, bpl, bmi ) ;
			AddAFBvalue( -bcos2, bpl, bmi ) ;
		}else{  //Top1 = antitop, Top2 = top, Top1b = antibottom, Top2b = bottom
			top->Fill( -tcos1, weight ) ;
			top->Fill( tcos2, weight ) ;
			bottom->Fill( -bcos1, weight ) ;
			bottom->Fill( bcos2, weight ) ;
			AddAFBvalue( -tcos1, tpl, tmi ) ;
			AddAFBvalue( tcos2, tpl, tmi ) ;
			AddAFBvalue( -bcos1, bpl, bmi ) ;
			AddAFBvalue( bcos2, bpl, bmi ) ;
		}

}


#ifdef __CINT__
int polar_angle_before( string input ){
#else
int main( int argc, char **argv ){
	TApplication app( "app", &argc, argv ) ;
#endif

	string treename = "Stats" ;
	
	TFile file1( input.c_str() ) ;
	if( file1.IsZombie() ){
		cout << "cannot open the file '" << input.c_str() << "'." << endl ;
		return 1 ;
	}

	gStyle->SetOptStat(0) ;

	int Top1bcharge, Top2bcharge ;
	float Top1costheta, Top1bcostheta, Top2costheta, Top2bcostheta ;
	int Top1TotalKaonCharge, Top2TotalKaonCharge ;
	float Top1bmomentum, Top2bmomentum;
	float Top1btag, Top2btag;
	float Top1energy, Top1mass;
	float Top2mass, Top2energy;
	float MCTopcostheta, MCTopBarcostheta ;
	float qMCBcostheta[2] ;
	int topplus = 0, topminus = 0, bottomplus = 0, bottomminus = 0 ;
	float topAFB, bottomAFB, topAFBgen, bottomAFBgen ;

	TCut btag = " ( Top1btag > 0.80 ) && ( Top2btag > 0.30 ) " ;
	TCut chi2_1 = " chiTopMass1 + chiTopE1 + chiPbstar1 < 30 " ;
	TCut chi2_2 = " chiTopMass2 + chiTopE2 + chiPbstar2 < 30 " ;
	TCut chi2 = chi2_1 + chi2_2 ;
	TCut kinematic = " ( Top1mass > 140 ) && ( Top1mass < 210 ) && ( Top2mass > 140 ) && ( Top2mass < 210 ) " ;
	//TCut samecharge = " ( Top1bcharge * Top2bcharge > 0 ) && ( Top1TotalKaonCharge * Top2TotalKaonCharge > 0 ) " ;
	TCut samecharge = "  Top1bcharge * Top2bcharge > 0 " ;
	TCut both0charge = " ( Top1bcharge == 0 ) || ( Top2bcharge == 0 ) " ;

	cout << endl ;
	cout << "-- before vertex recovery --" << endl ;

	TTree* tree1 = (TTree*)file1.Get( treename.c_str() ) ;
	int eventnum = tree1->GetEntries() ;
	cout << "eventnum            = " << eventnum << " (100%)" << endl ;
	int afterbtag = tree1->GetEntries( btag ) ;
	cout << "after b-tag cut     = " << afterbtag << " (" << (float)100*afterbtag/eventnum << "%)" << endl ;
	int afterkinematic = tree1->GetEntries( btag && kinematic ) ;
	cout << "atfer kinematic cut = " << afterkinematic << " (" << (float)100*afterkinematic/eventnum << "%)" << endl;
	int afterchi2 = tree1->GetEntries( btag && kinematic && chi2 ) ;
	cout << "after chi2 cut      = " << afterchi2 << " (" << (float)100*afterchi2/eventnum << "%)" << endl;

	int samesignnum = tree1->GetEntries( btag && kinematic && chi2 && samecharge ) ;
	int both0num = tree1->GetEntries( btag && kinematic && chi2 && both0charge ) ;
	int usednum = afterchi2 ;

	cout << endl ;
	cout << "used number = " << usednum << endl ;

	TEventList *elist1 = new TEventList( "elist1", "Reconstructed Event List" ) ;
	//tree1->Draw( ">>elist1", btag && kinematic && chi2 && !samecharge  && !both0charge ) ;
	tree1->Draw( ">>elist1", btag && kinematic && chi2 ) ;
	//usednum = elist->GetN() ;
	//cout << "used number = " << usednum << endl ;

	tree1->SetBranchAddress( "Top1bcharge", &Top1bcharge ) ;
	tree1->SetBranchAddress( "Top1costheta", &Top1costheta ) ;
	tree1->SetBranchAddress( "Top1bcostheta", &Top1bcostheta ) ;
	tree1->SetBranchAddress( "Top2bcharge", &Top2bcharge ) ;
	tree1->SetBranchAddress( "Top2costheta", &Top2costheta ) ;
	tree1->SetBranchAddress( "Top2bcostheta", &Top2bcostheta ) ;
	
	tree1->SetBranchAddress( "Top1TotalKaonCharge", &Top1TotalKaonCharge ) ;
	tree1->SetBranchAddress( "Top2TotalKaonCharge", &Top2TotalKaonCharge ) ;
	tree1->SetBranchAddress( "Top1btag", &Top1btag ) ;
	tree1->SetBranchAddress( "Top2btag", &Top2btag ) ;

	tree1->SetBranchAddress( "Top1mass", &Top1mass ) ;
	tree1->SetBranchAddress( "Top1energy", &Top1energy ) ;
	tree1->SetBranchAddress( "Top2mass", &Top2mass ) ;
	tree1->SetBranchAddress( "Top2energy", &Top2energy ) ;

	tree1->SetBranchAddress( "Top1bmomentum", &Top1bmomentum ) ;
	tree1->SetBranchAddress( "Top2bmomentum", &Top2bmomentum ) ;

	TCanvas* c1 = new TCanvas( "c1", "c1", 1280, 480 ) ;
	TCanvas* c2 = new TCanvas( "c2", "c2", 680, 480 ) ;
	TH1F* htop = new TH1F( "htop", "top polar angle (reconstructed)", 40, -1, 1 ) ;
	htop->SetMinimum(0) ;
	htop->SetLineColor(2) ;
	TH1F* hbottom = new TH1F( "hbottom", "bottom polar angle (reconstructed)", 40, -1, 1 ) ;
	hbottom->SetMinimum(0) ;
	hbottom->SetLineColor(2) ;
	TH1F* htopgen = new TH1F( "htopgen", "top polar angle (generated)", 40, -1, 1 ) ;
	htopgen->SetMinimum(0) ;
	htopgen->SetMaximum(0.11) ;
	htopgen->SetLineColor(4) ;
	TH1F* hbottomgen = new TH1F( "hbottomgen", "bottom polar angle (generated)", 40, -1, 1 ) ;
	hbottomgen->SetMinimum(0) ;
	hbottomgen->SetMaximum(0.11) ;
	hbottomgen->SetLineColor(4) ;
	TH1F* hLzFbf = new TH1F( "hLzFbf", "Lorentz factor #gamma", 100, 2, 4 ) ;
	hLzFbf->SetLineColor(2) ;
	TH1F* hLzFaf = new TH1F( "hLzFaf", "Lorentz factor #gamma", 100, 2, 4 ) ;
	hLzFaf->SetLineColor(3) ;

	htop->Sumw2();
	htopgen->Sumw2();
	hbottom->Sumw2();
	hbottomgen->Sumw2();

	// we need to change this weighting some how
	//double fillweight = (double)1/usednum ;
	double fillweight = 1 ;
	
	bool isbsign = false, iskaonsign = false;
	bool isb1k2sign = false;
	bool isbMomentum = false;
	
	int b1b2=0,k1k2=0,b1k2=0,k1b2=0;
	
	for( int i=0 ; i<usednum ; i++ ){

		tree1->GetEntry( elist1->GetEntry(i) ) ;

		isbsign = false ;
		iskaonsign = false;
		isb1k2sign = false ;
		isbMomentum = false ;

		float G1=0,G2=0;

		if( Top1bcharge*Top2bcharge < 0 && Top2btag > 0.80 ) isbsign = true;
		if( Top1TotalKaonCharge*Top2TotalKaonCharge < 0 ) iskaonsign = true;
		if( Top1bcharge*Top2TotalKaonCharge < 0 ) isb1k2sign = true;
		if( Top1bmomentum > 30 && Top2bmomentum > 30 ) isbMomentum = true;

		if( isbsign || iskaonsign || isb1k2sign ){
			G1 = LorentzF(Top1energy,Top1mass);
			G2 = LorentzF(Top2energy,Top2mass);
			hLzFbf->Fill(G1+G2);
		}

		if(G1+G2>2.6 && isbMomentum){
			if( isbsign ){
					FillandAdd(Top1bcharge,Top2bcharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
					b1b2++;
			}else if( iskaonsign ){
					FillandAdd(Top1TotalKaonCharge,Top2TotalKaonCharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
					k1k2++;
			}else if( isb1k2sign ){
					FillandAdd(Top1bcharge,Top2TotalKaonCharge,Top1costheta,Top2costheta,Top1bcostheta,Top2bcostheta,topplus,topminus,bottomplus,bottomminus,fillweight,htop,hbottom);
					b1k2++;
			}
		}

	}

	cout << "number after cuts = " << b1b2+k1k2+b1k2+k1b2 << endl;
	cout << "vtx1  + vtx2  : " << b1b2 << endl;
	cout << "kaon1 + kaon2 : " << k1k2 << endl;
	cout << "vtx1  + kaon2 : " << b1k2 << endl;

	topAFB = getAFB( topplus, topminus ) ;
	bottomAFB = getAFB( bottomplus, bottomminus ) ;
	cout << "AFB(top) = " << topAFB << ", AFB(bottom) = " << bottomAFB << endl ;

	tree1->SetBranchStatus( "Top*", 0 ) ;
	tree1->SetBranchAddress( "MCTopcostheta", &MCTopcostheta ) ;
	tree1->SetBranchAddress( "MCTopBarcostheta", &MCTopBarcostheta ) ;
	tree1->SetBranchAddress( "qMCBcostheta", &qMCBcostheta ) ;

	TEventList* elistgen = new TEventList( "elistgen", "Generated Event List" ) ;
	tree1->Draw( ">>elistgen", " ( MCTopcostheta != -2 ) && ( MCTopBarcostheta != -2 ) && ( qMCBcostheta[0] != -2 ) && ( qMCBcostheta[1] != -2 ) " ) ;
	int usedgennum = elistgen->GetN() ;
	cout << endl ;

	//work on weight
	fillweight = (double)1/usedgennum ;
	//fillweight = 1 ;

	topplus = 0 ;
	topminus = 0;
	bottomplus = 0 ;
	bottomminus = 0 ;

	for( int i=0 ; i<usedgennum ; i++ ){

		tree1->GetEntry( elistgen->GetEntry(i) ) ;

		htopgen->Fill( MCTopcostheta, fillweight ) ;
		htopgen->Fill( -MCTopBarcostheta, fillweight ) ;
		hbottomgen->Fill( qMCBcostheta[0], fillweight ) ;
		hbottomgen->Fill( -qMCBcostheta[1], fillweight ) ;
		AddAFBvalue( MCTopcostheta, topplus, topminus ) ;
		AddAFBvalue( -MCTopBarcostheta, topplus, topminus ) ;
		AddAFBvalue( qMCBcostheta[0], bottomplus, bottomminus ) ;
		AddAFBvalue( -qMCBcostheta[1], bottomplus, bottomminus ) ;

	}

	topAFBgen = getAFB( topplus, topminus ) ;
	bottomAFBgen = getAFB( bottomplus, bottomminus ) ;

	cout << endl ;
	cout << endl ;
	cout << "-- generated data --" << endl ;
	cout << "used genarated number = " << usedgennum << endl ;
	cout << endl ;
	cout << "AFB(top) = " << topAFBgen << ", AFB(bottom) = " << bottomAFBgen << endl ;

	c1->Divide(2,1) ;
	c1->cd(1) ;
	htopgen->SetTitle( "top polar angle (before:Red after:Green Gen:Blue)" ) ;

	cout << endl;

	TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
	pad1->SetBottomMargin(3);
	//pad1->SetGridx();
	pad1->Draw();
	pad1->cd();
	
	double norm = htop->GetEntries()/2 ;

	htop->Scale(1/norm);
    norm = htopafter->GetEntries()/2 ;
	htopafter->Scale(1/norm);


	htopgen->Draw() ;
	htop->Draw( "SAME" ) ;
	htopafter->Draw( "SAME" ) ;

	
	c1->cd(1);
	TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.2);
	pad2->SetGridx();
	pad2->SetGridy();
	pad2->Draw();
	pad2->cd();

	TH1F *rpTopBF = (TH1F*)htop->Clone("rpTopBF");
	TH1F *rpTopAF = (TH1F*)htopafter->Clone("rpTopAF");
	rpTopBF->SetMinimum(0.7);
	rpTopBF->SetMaximum(1.3);
	rpTopBF->SetStats(0);
	rpTopBF->Divide(htopgen);
	rpTopBF->SetMarkerColor(2);
	rpTopBF->SetMarkerStyle(20);
	rpTopBF->SetMarkerSize(0.8);
	rpTopBF->Draw("ep");
	rpTopBF->SetTitle("");

	rpTopBF->GetYaxis()->SetTitleSize(20);

	rpTopAF->SetMinimum(0.7);
	rpTopAF->SetMaximum(1.3);
	rpTopAF->SetStats(0);
	rpTopAF->Divide(htopgen);
	rpTopAF->SetMarkerColor(3);
	rpTopAF->SetMarkerStyle(20);
	rpTopAF->SetMarkerSize(0.8);
	rpTopAF->Draw("ep same");
	rpTopAF->SetTitle("");

	rpTopAF->GetYaxis()->SetTitleSize(20);

	
	c1->cd(2) ;
	hbottomgen->SetTitle( "bottom polar angle (before:Red after:Green Gen:Blue)" ) ;

	TPad *pad3 = new TPad("pad3", "pad3", 0, 0.3, 1, 1.0);
	pad3->SetBottomMargin(3);
	pad3->Draw();
	pad3->cd();
	
	norm = hbottom->GetEntries()/2 ;
	
	hbottom->Scale(1/norm);
	norm = hbottomafter->GetEntries()/2 ;
	hbottomafter->Scale(1/norm);
	
	hbottomgen->Draw() ;
	hbottom->Draw( "SAME" ) ;
	hbottomafter->Draw( "SAME" ) ;

	c1->cd(2);
	TPad *pad4 = new TPad("pad4", "pad4", 0, 0.05, 1, 0.3);
	pad4->SetTopMargin(0);
	pad4->SetBottomMargin(0.2);
	pad4->SetGridx();
	pad4->SetGridy();
	pad4->Draw();
	pad4->cd();

	TH1F *rpBottomBF = (TH1F*)htop->Clone("rpBottomBF");
	TH1F *rpBottomAF = (TH1F*)htopafter->Clone("rpBottomAF");
	rpBottomBF->SetMinimum(0.7);
	rpBottomBF->SetMaximum(1.3);
	rpBottomBF->SetStats(0);
	rpBottomBF->Divide(htopgen);
	rpBottomBF->SetMarkerColor(2);
	rpBottomBF->SetMarkerStyle(20);
	rpBottomBF->SetMarkerSize(0.8);
	rpBottomBF->Draw("ep");
	rpBottomBF->SetTitle("");

	rpBottomBF->GetYaxis()->SetTitleSize(100);

	rpBottomAF->SetMinimum(0.7);
	rpBottomAF->SetMaximum(1.3);
	rpBottomAF->SetStats(0);
	rpBottomAF->Divide(htopgen);
	rpBottomAF->SetMarkerColor(3);
	rpBottomAF->SetMarkerStyle(20);
	rpBottomAF->SetMarkerSize(0.8);
	rpBottomAF->Draw("ep same");
	rpBottomAF->SetTitle("");

	rpBottomAF->GetYaxis()->SetTitleSize(100);

	c2->cd();
	hLzFbf->Draw();
	hLzFaf->Draw("same");

	
	c1->WaitPrimitive() ;

	c1->Print( "picture/newpicture.png" ) ;
	c1->Close() ;

	file1.Close() ;
	file2.Close() ;
	

	return 0;

}




