#ifndef dEdxOP_hh
#define dEdxOP_hh

#include <cmath>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class dEdxOP {

public:
	dEdxOP(float dEdx_val, std::vector< float > & p3);
	dEdxOP();
	virtual ~dEdxOP () {};


private:
	float dEdx;
	std::vector<float> p;

};

#endif
