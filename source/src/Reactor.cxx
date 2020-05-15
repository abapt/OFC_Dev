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
  fLifeTime = 50 * 365.25 * 24;
  fStartingTime = 10 * 365.25 * 24;
  fCrossSectionU5 = 46.933e-24;
  fCrossSectionU8 = 1.015e-24;
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
  fStartingTime = CreationTime * 365.25 * 24;
  fLifeTime = LifeTime * 365.25 * 24;
  fCycleTime = (fBurnUp * 1e9 / fPower) * (fMassHN * 24);
  fCrossSectionU5 = 46.933e-24;
  fCrossSectionU8 = 1.015e-24;
  //cout << "tps cycle " << fCycleTime << endl;

  fScenarioTime = ScenarioTime;
  
  for(int t = 0; t < fScenarioTime; t++) {
    fMassU5Evolution.push_back(0);
    fMassU8Evolution.push_back(0);
    fMassOtherEvolution.push_back(0);
  }
  
  CalculateU5Enrichment(fBurnUp);
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::~Reactor() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void Reactor::CalculateU5Enrichment(double BurnUp) {
  fEnrichment = 0.0135139 + 0.000563569 * BurnUp
                + 1.34642e-06 * BurnUp * BurnUp;
  //cout << "Enrichissement " << fEnrichment << endl;
  // fBurnUp en GWj/t
}

void Reactor::Evolution(int t) {
  int StartingTime = GetStartingTime();
  int LifeTime = GetLifeTime();
  
  if(t < StartingTime) { // Reactor not started
    return;
    //cout << "Evolution" << endl;
  }
  
  if(t > (StartingTime + LifeTime)) { // reactor stopped
    return;
  }
  
  /*
  flux
  FIT BU-30GWj/t
  p0 =
  p1 = 

  FIT BU-35GWj/t
  p0 = 2.05344462162583e+14 
  p1 = 2.6160537285442e+13

  FIT BU-40GWj/t
  p0 =
  p1 = 

  FIT BU-45GWj/t
  p0 =
  p1 = 
  */
  
  
  int DeltaT = t - (t - 1); //def time interval between calculation
  
  int numCycle = (t - StartingTime) / fCycleTime;
  
  int hourInCycle = (t - StartingTime - (numCycle * fCycleTime));
  
  if(fBurnUp == 30) {
    fFlux = 2.13989553951004e+14 
            + 3.04361568e+9 * hourInCycle;

    fCrossSectionU5 = 59.608e-24
                      - (1.5395e-27)*hourInCycle
                      + (1.1021e-31)*hourInCycle*hourInCycle
                      - (4.1122e-36)*hourInCycle*hourInCycle*hourInCycle
                      + (8.5158e-41)*hourInCycle*hourInCycle*hourInCycle*hourInCycle
                      - (9.2739e-46)*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle
                      + (4.1295e-51)*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle;
    fCrossSectionU8 = 1.01666e-24
                      - (1.5027e-30)*hourInCycle
                      + (1.1568e-34)*hourInCycle*hourInCycle
                      - (2.6446e-39)*hourInCycle*hourInCycle*hourInCycle
                      + (2.0332e-44)*hourInCycle*hourInCycle*hourInCycle*hourInCycle;
  }
  else if(fBurnUp == 35) {
    fFlux = 2.05344462162583e+14 
            + 2.98431865e+9 * hourInCycle;

    fCrossSectionU5 = 55.83689e-24
                      - (1.3452e-27)*hourInCycle
                      + (9.7562e-32)*hourInCycle*hourInCycle
                      - (3.6439e-36)*hourInCycle*hourInCycle*hourInCycle
                      + (7.6236e-41)*hourInCycle*hourInCycle*hourInCycle*hourInCycle
                      - (8.4102e-46)*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle
                      + (3.7877e-51)*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle;
    fCrossSectionU8 = 1.00832e-24
                      - (1.2502e-30)*hourInCycle
                      + (1.0511e-34)*hourInCycle*hourInCycle
                      - (2.3842e-39)*hourInCycle*hourInCycle*hourInCycle
                      + (1.8207e-44)*hourInCycle*hourInCycle*hourInCycle*hourInCycle;
  }
 else if(fBurnUp == 40) {
    fFlux = 1.98181552271573e+14 
            + 2.879908401e+9 * hourInCycle;

    fCrossSectionU5 = 52.36492e-24
                      - (1.1731e-27)*hourInCycle
                      + (8.6071e-32)*hourInCycle*hourInCycle
                      - (3.2228e-36)*hourInCycle*hourInCycle*hourInCycle
                      + (6.8232e-41)*hourInCycle*hourInCycle*hourInCycle*hourInCycle
                      - (7.6240e-46)*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle
                      + (3.4679e-51)*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle;
    fCrossSectionU8 = 1.00068e-24
                      - (1.0283e-30)*hourInCycle
                      + (9.3718e-35)*hourInCycle*hourInCycle
                      - (2.0845e-39)*hourInCycle*hourInCycle*hourInCycle
                      + (1.5722e-44)*hourInCycle*hourInCycle*hourInCycle*hourInCycle;
  }
  else if(fBurnUp == 45) {
    fFlux = 1.92218415221614e+14 
            + 2.746067085e+9 * hourInCycle;

    fCrossSectionU5 = 49.2022e-24
                      - (1.0223e-27)*hourInCycle
                      + (7.5720e-32)*hourInCycle*hourInCycle
                      - (2.8472e-36)*hourInCycle*hourInCycle*hourInCycle
                      + (6.1075e-41)*hourInCycle*hourInCycle*hourInCycle*hourInCycle
                      - (6.9061e-46)*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle
                      + (3.1670e-51)*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle*hourInCycle;
    fCrossSectionU8 = 0.99374e-24
                      - (8.2412e-31)*hourInCycle
                      + (8.1151e-35)*hourInCycle*hourInCycle
                      - (1.7442e-39)*hourInCycle*hourInCycle*hourInCycle
                      + (1.2888e-44)*hourInCycle*hourInCycle*hourInCycle*hourInCycle;
  }
  else {
    cout << "Burn Up incompatible" << endl;
    cout << "Valeurs compatibles pour BU : 30 - 35 - 40 - 45" << endl;
    exit(1);
  }


  fMassU5Evolution[t] = fMassU5Evolution[t-1] *
                        exp(-fCrossSectionU5 * fFlux * DeltaT * 3600);
  fMassU8Evolution[t] = fMassU8Evolution[t-1] *
                        exp(-fCrossSectionU8 * fFlux * DeltaT * 3600);
  fMassOtherEvolution[t] = fMassHN*1000 - fMassU5Evolution[t] - fMassU8Evolution[t];
}

void Reactor::Drain(int t) {

  GetStock()->AddMassU5(t, fMassU5Evolution[t]);
  GetStock()->AddMassU8(t, fMassU8Evolution[t]);
  GetStock()->AddMassOther(t, fMassOtherEvolution[t]);
  
  fMassU5Evolution[t] = 0;
  fMassU8Evolution[t] = 0;
  fMassOtherEvolution[t] = 0;
}

void Reactor::Load(int t) {

  // Add mass in Reactor
  fMassU5Evolution[t] += fMassHN*1000 * GetEnrichment();
  fMassU8Evolution[t] += fMassHN*1000 * (1 - GetEnrichment());


  //cout << "Masse U5 " << fMassU5Evolution[t] << endl; 
  //cout << "Masse U8 " << fMassU8Evolution[t] << endl;
  
  // Remove Mass in EP
  GetEnrichmentPlant()->GetProductStock()->RemoveMassU5(t, fMassHN*1000 * GetEnrichment());
  GetEnrichmentPlant()->GetProductStock()->RemoveMassU8(t, fMassHN*1000 * (1 - GetEnrichment()));
}





