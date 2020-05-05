#include "Reactor.hxx"
#include "Stock.hxx"
#include "EnrichmentPlant.hxx"
#include "Scenario.hxx"

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
  fLifeTime = 50*365.25*24;
  fStartingTime =10*365.25*24;
  fCrossSection = 46.933e-24;
  (*this).SetName("Reactor");
}

Reactor::Reactor(double LifeTime,
                 double CreationTime,
                 int ScenarioTime,
                 double power,
                 double MassHN,
                 double BurnUp,
                 double LoadFactor) {
  (*this).SetName("Reactor");
  
  fLoadFactor = LoadFactor;
  fPower = power * fLoadFactor;
  fMassHN = MassHN;
  fBurnUp = BurnUp;
  fStartingTime = CreationTime*365.25*24;
  fLifeTime = LifeTime*365.25*24;
  fCrossSection = 46.933e-24;
  fCycleTime = (fBurnUp * 1e9 / fPower) * (fMassHN * 24);

  fScenarioTime = ScenarioTime;
  cout <<"taille Scenar " << fScenarioTime << endl; 
  for(int t=0; t<fScenarioTime; t++) {
    fMassU5Evolution.push_back(0);
    fMassU8Evolution.push_back(0);
  }
  fMassU5Evolution[0]=0;
  fMassU8Evolution[0]=0;
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::~Reactor() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void Reactor::CalculateU5Enrichment(double BurnUp) {
  fEnrichissement = 0.0135139 + 0.000563569 * BurnUp 
                  + 1.34642e-06 * BurnUp * BurnUp; 
                  // fBurnUp en GWj/t
}


void Reactor::Evolution(int t) {
  int StartingTime = GetStartingTime();
  int LifeTime = GetLifeTime();
  cout << "taille Evo " << fMassU5Evolution.size() << endl;
  if(t < StartingTime) { // Reactor not started
    return;
  }
  
  if(t > (StartingTime + LifeTime)) { // reactor stopped
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
  

  int DeltaT = t - (t-1); //def time interval between calculation

  int numCycle = (t-StartingTime)/fCycleTime;
  
  int hourInCycle = (t-StartingTime-(numCycle*fCycleTime));

  fFlux = 2.4807e+14 
        + 5.246979e+9*hourInCycle 
        - 2.1964855e+4*hourInCycle*hourInCycle;
/*
  fMassU5Evolution[t] = fMassU5Evolution[t-1]* 
                        exp(-fCrossSection*fFlux*DeltaT*60*60);
  fMassU8Evolution[t] = fMassHN - fMassU5Evolution[t];*/
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
