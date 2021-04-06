#ifndef VecOP_hh
#define VecOP_hh

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class VecOP {

public:
	VecOP(float x, float y, float z);
	VecOP();
	virtual ~VecOP () {};

	float getModule(std::vector< float > & v);
	std::vector< float > getDirection(std::vector<float> & vectorPoint);
	std::vector< float > getAngles(std::vector< float > & direction);
	std::vector< float > CalculateAnglesMom();
	std::vector< float > CalculateAngles();
	float GetMomentum();
	float GetCostheta();
	float GetCosphi();
	float GetSinacol(TVector3 v1, TVector3 v2);

private:
	std::vector<float> p;

};

#endif
