#define dEdxOP_cxx
#include "../include/dEdxOP.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

dEdxOP::dEdxOP(float dEdx_val, std::vector< float > & p3){

  dEdx = dEdx_val;
  p = p3;

}

dEdxOP::dEdxOP() {};


