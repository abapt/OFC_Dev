#include "Reactor.hxx"
#include "Stock.hxx"
#include "EnrichmentPlant.hxx"

#include <iostream>
#include<math.h>
using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::Reactor() {
  fLoadFactor = 0.75;
  fPower = 3e9 * fLoadFactor;
  fMassHN = 100;
  fBurnUp = 35;
  fLifeTime = 50;
  (*this).SetName("Reactor");
}

Reactor::Reactor(double LifeTime,
                 double power,
                 double MassHN,
                 double BurnUp,
                 double LoadFactor) {
  (*this).SetName("Reactor");
  
  fLoadFactor = LoadFactor;
  fPower = power * fLoadFactor;
  fMassHN = MassHN;
  fBurnUp = BurnUp;
  fLifeTime = LifeTime;
  
  fCycleTime = (fBurnUp * 1e9 / fPower) * (fMassHN * 24);
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::~Reactor() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void Reactor::CalculateU5Enrichment(double fBurnUp) {
  fMassHN = 0.0135139 + 0.000563569 * fBurnUp + 1.34642e-06 * fBurnUp * fBurnUp; // fBurnUp en GWj/t
}


void Reactor::Evolution(int t) {
  int StartingTime = GetStartingTime();
  int LifeTime = GetLifeTime();
  
  if(t < StartingTime) {
    return;
  }
  
  if(t > StartingTime + LifeTime) {
    return;
  }
  
  /*
  flux
  FIT PWR - 3.26% en U5
  p0                        =   2.4807e+14   +/-   1.17036e+12
  p1                        =   4.6258e+13   +/-   1.36441e+12
  p2                        = -1.68784e+12   +/-   3.28195e+11
  
  FIT PWR - 4.20% en U5
  p0                        =  2.28774e+14   +/-   1.43852e+12
  p1                        =  3.81756e+13   +/-   1.92004e+12
  p2                        = -8.50596e+11   +/-   5.27476e+11
  */
  
//
  DeltaT = t - (t - 1);
  
  int RelativeTime = t - NumberCycle * fCycleTime;
  fFlux = 2.28774e+14 +
          3.81756e+13 * RelativeTime -
          8.50596e+11 * RelativeTime * RelativeTime;
  fMassU5Evolution[t] = fMassU5Evolution[t - 1] * exp(-s * f * DeltaT)
  fMassU8Evolution[t] = fMassU8Evolution[t - 1] * exp(-s * f * DeltaT)
  
  
  for(int i = 1; i <= fCycleTime; ++i) { fFlux.push_back(0); }
  
  for(int j = 1; j <= fCycleTime; ++j) {
    fMassU5Evolution[0] = EnrichmentPlant->GiveReactorUenr();
    fFlux[j] = 2.28774e+14 + 3.81756e+13 * j - 8.50596e+11 * j * j;
    fMassU5Evolution[j] = fMassHN * exp(-fFlux[j] * fCrossSection * (j * 365 * 24 * 60 * 60));;
    fMassU8Evolution[j] = fMassHN - fMassU5Evolution[j];
  }
  
  /*if ((t-StartingTime)%LifeTime == 0 && t != StartingTime)
  {
    // Créer un vecteur lié à U5Waste de Stock
    U5Stock[t] += fMassU5Waste[t];
    U8Stock[t] += fMassU8Waste[t];
  }*/
}
