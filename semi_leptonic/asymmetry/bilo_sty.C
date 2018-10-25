#ifndef bilo_sty_C
#define bilo_sty_C

void bilo_sty() {

		//ild TStyle
		TStyle* biloStyle = new  TStyle("biloStyle", "Bilokin Style");

		//biloStyle->SetFrameLineWidth(3);
		biloStyle->SetHistLineWidth(3);
		biloStyle->SetLineWidth(3); 

		biloStyle->SetPadLeftMargin(0.14);
		biloStyle->SetTitleOffset(1.3,"yz");

		//done
		biloStyle->cd();
		gROOT->ForceStyle();
		gStyle->ls();

}

#endif
