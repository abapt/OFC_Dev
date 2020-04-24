#include "Reactor.hxx"

#include <iostream>

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::Reactor() {
  MassHN = 100;
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
  do
  {
    fFlux[i]= 4.10569e15 - 8.75127e10*i + 5.31149e6*i² - 142.44206*i³ + 0.00204*i⁴ - 1.55273e-8*i⁵ + 4.9082e-14*i⁶;
    if (i%fCycleTime==0)
    {
      fMassU5Evolution[i] = fMassHN ;
      fMassU8Evolution[i] = fMassHN/fEnrichissement;
    }
    else
    {
      fMassU5Evolution[i] = fMassU5Evolution[i-1]*exp(-fFlux[i]*fCrossSection*(365*24*60*60));
      /*fMassU8Evolution[i] = fMassHN*; */
    }
    i++;
  } while (i<fLifeTime);
}
