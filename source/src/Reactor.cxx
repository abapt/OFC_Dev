#include "Reactor.hxx"

#include <iostream>

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::Reactor() {
  (*this).SetName("Reactor");
  
  fMassHN = 100;
  fPower = 3e9;
  fLoadFactor = 0.75;
  fBurnUp = 35; 
  fCycleTime = (fBurnUp * 1e9 / (fPower)*fMassHN * 24);
  fStartingTime = 5*365.25*24;
  fLifeTime = 50*365.25*24; 

}

Reactor::Reactor(double StartingTime, double LifeTime, double power, double MassHN,double BurnUp, 
				double LoadFactor) {
  (*this).SetName("Reactor");

  fLoadFactor = LoadFactor;
  fPower = power * fLoadFactor;
  fMassHN = MassHN;
  fBurnUp = BurnUp;
  fLifeTime = LifeTime;

  fCycleTime = (fBurnUp * 1e9 / fPower)*(fMassHN * 24);
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::~Reactor() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void Reactor::CalculateU5Enrichment(double fBurnUp) {
	fMassHN = 0.0135139 + 0.000563569*fBurnUp + 1.34642e-06*fBurnUp*fBurnUp; // fBurnUp en GWj/t
}

void Reactor::Evolution(double fCycleTime) {
/*
FIT PWR - 3.26% en U5
p0                        =   2.4807e+14   +/-   1.17036e+12
p1                        =   4.6258e+13   +/-   1.36441e+12
p2                        = -1.68784e+12   +/-   3.28195e+11

FIT PWR - 4.20% en U5
p0                        =  2.28774e+14   +/-   1.43852e+12
p1                        =  3.81756e+13   +/-   1.92004e+12
p2                        = -8.50596e+11   +/-   5.27476e+11
*/

/*
  int i(0);
  do
  {
    fFlux[i]= 4.10569e15 - 8.75127e10*i + 5.31149e6*i*i - 142.44206*i*i*i + 0.00204*i*i*i*i - 1.55273e-8*i*i*i*i*i + 4.9082e-14*i*i*i*i*i*i;
    if (i%fCycleTime==0)
    {
      fMassU5Evolution[i] = fMassHN ;
      fMassU8Evolution[i] = fMassHN/fEnrichissement;
    }
    else
    {
      fMassU5Evolution[i] = fMassU5Evolution[i-1]*exp(-fFlux[i]*fCrossSection*(365*24*60*60));
    }
    i++;
  } while (i<fLifeTime);
*/
}
