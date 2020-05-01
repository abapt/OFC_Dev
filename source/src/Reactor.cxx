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
  fCrossSection = 46.933e-24;
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
  fCrossSection = 46.933e-24;
  fCycleTime = (fBurnUp * 1e9 / fPower) * (fMassHN * 24);
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::~Reactor() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void Reactor::CalculateU5Enrichment(double BurnUp) {
  fEnrichissement = 0.0135139 + 0.000563569 * BurnUp + 1.34642e-06 * BurnUp * BurnUp; // fBurnUp en GWj/t
}


void Reactor::Evolution(int t) {
  int StartingTime = GetStartingTime();
  int LifeTime = GetLifeTime();
  
  if(t < StartingTime) { // Reactor not started
    return;
  }
  
  if(t > StartingTime + LifeTime) { // reactor stopped
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
  int DeltaT = t - (t-1); //def time interval between calculation
  
  int RelativeTime = (t-StartingTime)%fCycleTime; //define flux 
  if (RelativeTime == 1) {fFlux = 2.66099004e+14;}
  if (RelativeTime == 2) {fFlux = 3.01722816e+14;}
  if (RelativeTime == 0) {fFlux = 3.35645436e+14;}

  fMassU5Evolution[t] = fMassU5Evolution[t-1]* 
                        exp(-fCrossSection*fFlux*DeltaT*365.25*24*60*60);
  fMassU8Evolution[t] = fMassHN - fMassU5Evolution[t];
  }

void Reactor::Start(int t){
  CalculateU5Enrichment(fBurnUp);  

  // Fill Reactor
  fMassU5Evolution[t] = fMassHN * fEnrichissement;
  fMassU8Evolution[t] = fMassHN * (1 - fEnrichissement);


}

void Reactor::Drain(int t){
  //Access to stocks
  vector<double> fMassU5WasteStock = fStock->GetMassU5Waste();
  vector<double> fMassU8WasteStock = fStock->GetMassU8Waste();

  // Modify stock masses
  fMassU5WasteStock[t] += fMassU5Evolution[t];
  fMassU8WasteStock[t] += fMassU8Evolution[t];
  fMassU5Evolution[t] = 0;
  fMassU8Evolution[t] = 0;
}

void Reactor::Load(int t){
  // Calculate needed U5
  CalculateU5Enrichment(fBurnUp);  

  // Access to EP stocks
  vector<double> fMassU5EnrEP = fEnrichmentPlant->GetMassU5Enr();
  vector<double> fMassU8EnrEP = fEnrichmentPlant->GetMassU8Enr();

  // Modify Reactor stocks
  fMassU5Evolution[t] = fMassU5EnrEP[t];
  fMassU8Evolution[t] = fMassU8EnrEP[t];

  // Reset EP stocks
  fMassU5EnrEP[t] = 0;
  fMassU8EnrEP[t] = 0;
}
