#ifndef VecOP_hh
#define VecOP_hh

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class VecOP {

public:
	VecOP(float x, float y, float z);
	virtual ~VecOP () {};

	std::vector<float> p;

	float getModule(vector< float > & v);
	std::vector< float > getDirection(vector<float> & vectorPoint);
	std::vector< float > getAngles(std::vector< float > & direction);
	std::vector< float > CalculateAnglesMom();
	std::vector< float > CalculateAngles();


};

#endif

// #ifdef VecOP_cxx

// VecOP::VecOP(float x, float y, float z){

// 	p.push_back(x);
// 	p.push_back(y);
// 	p.push_back(z);

// }

// VecOP::~VecOP(){}

// #endif // #ifdef VecOP_cxx