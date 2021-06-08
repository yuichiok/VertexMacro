#define VecOP_cxx
#include "VecOP.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

VecOP::VecOP(float x, float y, float z){

  p.push_back(x);
  p.push_back(y);
  p.push_back(z);

}

VecOP::VecOP() {};

float VecOP::getModule( const vector< float > & v)   {
  float module = 0.0;
  for (unsigned int i = 0; i < v.size(); i++) module += v[i]*v[i];
     module = sqrt(module);
  return module;
}

std::vector< float > VecOP::getDirection( const vector<float> & vectorPoint) {
  vector< float > vector1;
  float module = getModule(vectorPoint);
  for (int i = 0; i < 3; i++) vector1.push_back( vectorPoint[i]/module);
  return vector1;
}

std::vector< float > VecOP::getAngles(std::vector< float > & direction) {
  vector< float > result;

  TLorentzVector v1(direction[0],direction[1],0,0);
  TLorentzVector v2(1,0,0,0);

  float phi = v1.Angle(v2.Vect()); 
  if(direction[1]<0 && direction[0]>0) phi=2*TMath::Pi() - phi;
  if(direction[1]<0 && direction[0]<0) phi=2*TMath::Pi() - phi;

  if(direction[1]<0 && direction[0]==0) phi=3.*TMath::Pi()/2.;
  if(direction[1]>0 && direction[0]==0) phi=TMath::Pi()/2.;
  if(direction[1]==0 && direction[0]>0) phi=0;
  if(direction[1]==0 && direction[0]<0) phi=TMath::Pi();

  float teta = acos(direction[2]);
  result.push_back(phi);
  result.push_back(teta);
  return result;
}

std::vector< float > VecOP::CalculateAnglesMom() {
  std::vector< float > direction = getDirection(p);
  std::vector< float > angles=getAngles(direction);
  angles.push_back(getModule(p));
  return angles;
}

float VecOP::CalculatePT(vector< float > & v){
  float pt = 0.0;
  for (unsigned int i = 0; i < 2; i++) pt += v[i]*v[i];
     pt = sqrt(pt);
  return pt;
}

std::vector< float > VecOP::CalculateAngles() {
  std::vector< float > direction = getDirection(p);
  std::vector< float > angles=getAngles(direction);
  return angles;
}

float VecOP::getAngleBtw(const std::vector< float > & vector1, const std::vector< float > & vector2)
{
  vector< float > direction1 = getDirection(vector1);
  vector< float > direction2 = getDirection(vector2);
  float product = 0.0;
  for (int i = 0; i < 3; i++) 
  {
    product += direction1[i]*direction2[i];
  }
  float result = acos(product);
  if (isnan(result)) 
  {
    if (product > 0.999) 
    {
      return 0.0;
    }

  }
  return result;
}

float VecOP::GetMomentum(){
  return getModule(p);
}

std::vector< float > VecOP::GetMomentum3(){
  return p;
}

float VecOP::GetThrustPT(const std::vector< float > & v){

  float pt = 0.0;
  float angbtw = getAngleBtw(p,v);
  float flip = ( angbtw < TMath::Pi()/2 ) ? 1.0 : -1.0;
  float thval = getModule(v);

  for (unsigned int i = 0; i < 3; i++) pt += p[i]*flip*v[i];
     pt = sqrt(pt) / thval;
  return pt;
}

float VecOP::GetPT(){
  return CalculatePT(p);
}

float VecOP::GetCostheta(){
  float costheta1 =  -2.0;
  std::vector< float > d1= getDirection(p);
  costheta1 =  std::cos( getAngles(d1).at(1) );
  return costheta1;
}

float VecOP::GetCosphi(){
  float cosphi= -2.0;
  std::vector<float> d1 = getDirection(p);
  cosphi = std::cos(getAngles(d1).at(0));
  return cosphi;
}

float VecOP::GetSinacol(TVector3 v1, TVector3 v2){
  float sinacol =  -2.0;
  TVector3 v= v1.Cross(v2);
  sinacol = (v.Mag()/(v1.Mag()*v2.Mag()));// * v2.Mag()/(v1+v2).Mag(); 
  return sinacol;
}

// float VecOP::getAngle2Vec(float px1, float py1, float pz1, float E1, float px2, float py2, float pz2, float E2) {

//   TLorentzVector v1(px1,py1,pz1,E1);
//   TLorentzVector v2(px2,py2,pz2,E2);

//   Double_t a = v1.Angle(v2.Vect());  // get angle between v1 and v2
//   return a;
// }