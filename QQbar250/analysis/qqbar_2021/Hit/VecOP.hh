#ifndef VecOP_hh
#define VecOP_hh

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class VecOP {

public:
	VecOP(float x, float y, float z);
	virtual ~VecOP () {};

	float getModule(std::vector< float > & v);
	std::vector< float > getDirection(std::vector<float> & vectorPoint);
	std::vector< float > getAngles(std::vector< float > & direction);
	std::vector< float > CalculateAnglesMom();
	std::vector< float > CalculateAngles();
	float GetMomentum();
	float GetCostheta();
	float GetCosphi();

private:
	std::vector<float> p;

};

#endif
