#include "../../../style/Style.C"
#include "../../../style/Labels.C"




void Labels(int ipol, int iquark, int lum){
  QQBARLabel(0.86,0.952," work in progress");
  TString quark= "c#bar{c}";
  if(iquark==5) quark="b#bar{b}";
  if(iquark==0) quark="q#bar{q}";


  TString pol[]={"e_{L}^{-}e_{R}^{+}","e_{R}^{-}e_{L}^{+}","e_{L,80%}^{-}e_{R,30%}^{+}","e_{R,80%}^{-}e_{L,30%}^{+}","e^{-}e^{+}"};
  QQBARLabel2(0.1,0.05, pol[ipol]+" #rightarrow "+quark+" mc-2020. "+TString::Format("Lum = %i fb^{-1}",lum),kGray+2);


}

