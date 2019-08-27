#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

using namespace std;
void efficiency_methods()
{
	int token=0;

	FileSelector fs;
	std::vector<FileSelector> rootfiles;
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record.txt" );

	while( fs.input(in) ){
		rootfiles.push_back(fs);
	}

	int nrootfiles = 0;
	nrootfiles = rootfiles.size();
  
	cout << "nfiles = " << nrootfiles << endl;

	std::cout << "Choose a file from below:" << std::endl;
	for( int i=0; i < nrootfiles; i++){
		std::cout << i << ": " << rootfiles[i].info() << endl;
	}

	std::cout << "Enter code: ";
	std::cin >> token;
	std::cout << std::endl;

	std::string filename = rootfiles[token].filename();
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
	TTree * Summary = (TTree*) file->Get( "Summary" );

	int forward  = GenTree->Draw("qMCcostheta","qMCcostheta > 0 && qMCcostheta > -2 ");
	int backward = GenTree->Draw("qMCcostheta","qMCcostheta < 0 && qMCcostheta > -2");

	// Begin efficiency calculation

	int entrySum = Summary->GetEntries();
	int nGenUsed, nAfterLeptonCuts, nAfterBtagCuts;
	int nevt=0, nlcut=0, nbcut=0;

	Summary->SetBranchAddress( "nGenUsed", &nGenUsed ) ;
	Summary->SetBranchAddress( "nAfterLeptonCuts", &nAfterLeptonCuts ) ;
	Summary->SetBranchAddress( "nAfterBtagCuts", &nAfterBtagCuts ) ;

	for(int i=0; i<entrySum; i++){

		Summary->GetEntry(i);

		nevt  += nGenUsed;
		nlcut += nAfterLeptonCuts;
		nbcut += nAfterBtagCuts;

	}

	cout << "============================ Baseline Cuts ============================" << endl;
	cout << "nEvents                      = " << nevt << " (100%)" << endl;
	cout << "after lepton cuts            = " << nlcut << " (" << (float)(nlcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after btag cuts (0.8 & 0.3)  = " << nbcut << " (" << (float)(nbcut)/(float)(nevt) *100 << "%)" << endl;



	int entryStat = normaltree->GetEntries();

	float Thrust=0,
				hadMass=0,
				Top1mass=0,
				W1mass=0,
				Top1bmomentum=0,
				Top2bmomentum=0,
				Top1gamma=0,
				Top2gamma=0;
	
	int methodUsed=0;
	int methodTaken[100],
			chgValue[100];

				
  int afterthrucut=0,
			afterhadMcut=0,
			afterrcTWcut=0,
			afterpcut=0,
			aftergcut=0;
	
	int	aftermethod7=0,
			aftermethod75=0,
			aftermethod756=0,
			aftermethod7561=0,
			aftermethod75612=0,
			aftermethod756123=0,
			aftermethod7561234=0;

	normaltree->SetBranchAddress("Thrust", &Thrust);
	normaltree->SetBranchAddress("hadMass", &hadMass);
	normaltree->SetBranchAddress("Top1mass", &Top1mass);
	normaltree->SetBranchAddress("W1mass", &W1mass);
	normaltree->SetBranchAddress("Top1bmomentum", &Top1bmomentum);
	normaltree->SetBranchAddress("Top2bmomentum", &Top2bmomentum);
	normaltree->SetBranchAddress("Top1gamma", &Top1gamma);
	normaltree->SetBranchAddress("Top2gamma", &Top2gamma);
	normaltree->SetBranchAddress("methodUsed", &methodUsed);
	normaltree->SetBranchAddress("methodTaken", methodTaken);
	normaltree->SetBranchAddress("chgValue", chgValue);

	int temp=0;

  for(int iStatEntry=0; iStatEntry<entryStat; iStatEntry++){

		normaltree->GetEntry(iStatEntry);

		if(Thrust<0.9){

			afterthrucut++;

			if(hadMass > 180 && hadMass < 420){

				afterhadMcut++;

				if(Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50){

					afterrcTWcut++;

					bool methodCheck1=false,
			 				 methodCheck2=false,
			 				 methodCheck3=false,
			 				 methodCheck4=false,
			 				 methodCheck5=false,
			 				 methodCheck6=false,
			 				 methodCheck7=false;

					int sum = 0;

					for(int imethod = 0; imethod < methodUsed; imethod++){

						int Nmethod = methodTaken[imethod];
						int charge  = chgValue[imethod];

						sum += charge;

						if(Nmethod==1) methodCheck1=true;
						if(Nmethod==2) methodCheck2=true;
						if(Nmethod==3) methodCheck3=true;
						if(Nmethod==4) methodCheck4=true;
						if(Nmethod==5) methodCheck5=true;
						if(Nmethod==6) methodCheck6=true;
						if(Nmethod==7) methodCheck7=true;

					}

					if(sum == 0){
						temp++;
						continue;
					}else{
						if(methodCheck7) aftermethod7++;
						if(methodCheck7 || methodCheck5) aftermethod75++;
						if(methodCheck7 || methodCheck5 || methodCheck6) aftermethod756++;
						if(methodCheck7 || methodCheck5 || methodCheck6 || methodCheck1) aftermethod7561++;
						if(methodCheck7 || methodCheck5 || methodCheck6 || methodCheck1 || methodCheck2) aftermethod75612++;
						if(methodCheck7 || methodCheck5 || methodCheck6 || methodCheck1 || methodCheck2 || methodCheck3) aftermethod756123++;
						if(methodCheck7 || methodCheck5 || methodCheck6 || methodCheck1 || methodCheck2 || methodCheck3 || methodCheck4) aftermethod7561234++;
					}

					if(Top1bmomentum > 15 && Top2bmomentum > 15){

						afterpcut++;

					}//pcut
				}//rcTW cut
			}//hadM cut
		}//thrust cut
	}

	cout << "after thrust cut             = " << afterthrucut << " (" << (float)(afterthrucut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after hadronic mass cut      = " << afterhadMcut << " (" << (float)(afterhadMcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after reco T & W mass cut    = " << afterrcTWcut << " (" << (float)(afterrcTWcut)/(float)(nevt) *100 << "%)" << endl;

	cout << "============================ Non-baseline Cuts ============================" << endl;
	//cout << "after gcut                   = " << aftergcut << " (" << (float)(aftergcut)/(float)(nevt) *100 << "%)" << endl;
	//cout << "after pcut                   = " << afterpcut << " (" << (float)(afterpcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method7                = " << aftermethod7 << " (" << (float)(aftermethod7)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method75               = " << aftermethod75 << " (" << (float)(aftermethod75)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method756              = " << aftermethod756 << " (" << (float)(aftermethod756)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method7561             = " << aftermethod7561 << " (" << (float)(aftermethod7561)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method75612            = " << aftermethod75612 << " (" << (float)(aftermethod75612)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method756123           = " << aftermethod756123 << " (" << (float)(aftermethod756123)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method7561234          = " << aftermethod7561234 << " (" << (float)(aftermethod7561234)/(float)(nevt) *100 << "%)" << endl;
	cout << endl;
	cout << "skipped (sum = 0)            = " << temp << " (" << (float)(temp)/(float)(nevt) *100 << "%)" << endl;
	cout << endl;

/*

	TCut thru = "Thrust < 0.9";
	TCut hadM = "hadMass > 180 && hadMass < 420";
	TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";

	TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
	TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

	TCut method = "methodTaken > 0";

	TCut cuts = thru && hadM && rcTW && pcut && gcut && method;

	int afterbcut    = normaltree->GetEntries();
	int afterthrucut = normaltree->GetEntries( thru );
	int afterhadMcut = normaltree->GetEntries( thru && hadM );
	int afterrcTWcut = normaltree->GetEntries( thru && hadM && rcTW );

	cout << "after thrust cut             = " << afterthrucut << " (" << (float)(afterthrucut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after hadronic mass cut      = " << afterhadMcut << " (" << (float)(afterhadMcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after reco T & W mass cut    = " << afterrcTWcut << " (" << (float)(afterrcTWcut)/(float)(nevt) *100 << "%)" << endl;

	int afterpcut = normaltree->GetEntries( thru && hadM && rcTW && pcut );
	int aftergcut = normaltree->GetEntries( thru && hadM && rcTW && gcut );

	cout << "============================ Non-baseline Cuts ============================" << endl;
	cout << "after gcut                   = " << aftergcut << " (" << (float)(aftergcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after pcut                   = " << afterpcut << " (" << (float)(afterpcut)/(float)(nevt) *100 << "%)" << endl;
	cout << endl;

	TCut fcoscut = "qCostheta > 0";
	TCut bcoscut = "qCostheta < 0 && qCostheta > -1.0";

	TCut fcuts = fcoscut && cuts;
	TCut bcuts = bcoscut && cuts;

	int recoforward = normaltree->GetEntries(fcuts);
	int recobackward = normaltree->GetEntries(bcuts);

	float afbgen = (float)(forward - backward) / (float) (forward + backward);
	float afbreco = (float)(recoforward - recobackward) / (float) (recoforward + recobackward);

	cout << "recoforward  = " << recoforward  << endl;
	cout << "recobackward = " << recobackward << endl;


	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
	std::cout << "Afb reco: " << afbreco << " N: " << recoforward + recobackward << "(" << afbreco / afbgen *100 << "%)"  << "\n";
	cout << "--------------------------------------------------------------\n";
	float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
	cout << "Final efficiency: " << efficiency << "%\n" ;
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	//file->Close();
	
	*/
	
}

