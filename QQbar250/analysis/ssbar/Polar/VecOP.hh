#ifndef VecOP_hh
#define VecOP_hh

#include <cmath>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class VecOP {

public:
	VecOP(float x, float y, float z);
	VecOP();
	virtual ~VecOP () {};

	static float getModule( const std::vector< float > & v);
	static std::vector< float > getDirection(const std::vector<float> & vectorPoint);
	std::vector< float > getAngles(std::vector< float > & direction);
	std::vector< float > CalculateAnglesMom();
	std::vector< float > CalculateAngles();
	float CalculatePT(std::vector< float > & v);
	float GetMomentum();
	std::vector< float > GetMomentum3();
    static float    getAngleBtw(const std::vector< float > & vector1, const std::vector< float > & vector2);
	float GetPT();
	float GetCostheta();
	float GetCosphi();
	float GetSinacol(TVector3 v1, TVector3 v2);

private:
	std::vector<float> p;

};

#endif
