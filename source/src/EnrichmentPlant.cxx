#include "EnrichmentPlant.hxx"
#include "Stock.hxx"
#include "Reactor.hxx"
#include "Scenario.hxx"

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::EnrichmentPlant(double U5ContentInUWaste,
                                 int ScenarioTime) {
                                 
  fEnrichmentTime = 17532;
  fU5ContentInUWaste = U5ContentInUWaste;
  
  SetName("EnrichmentPlant.");
  
  for(int t = 0; t < ScenarioTime; t++) {
    fMassU5.push_back(0);
    fMassU8.push_back(0);
    
  }
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::~EnrichmentPlant() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// ----------------------------------------------------------
void EnrichmentPlant::RemoveMassU5(int time, double mass){

  if(fMassU5[time] - mass < 0){
    cout<<"ERROR in EnrichmentPlant::RemoveMassU5(t,m)"<<endl;
    cout<<"You try to remove the mass "<<mass<<endl;
    cout<<"in the stock "<<GetName()<<endl;
    exit(1);
  }

  fMassU5[time] = fMassU5[time] - mass;
}
// ----------------------------------------------------------
void EnrichmentPlant::RemoveMassU8(int time, double mass){

  if(fMassU8[time] - mass < 0){
    cout<<"ERROR in EnrichmentPlant::RemoveMassU8(t,m)"<<endl;
    cout<<"You try to remove the mass "<<mass<<endl;
    cout<<"in the stock "<<GetName()<<endl;
    exit(1);
  }

  fMassU8[time] = fMassU8[time] - mass;
}
// ----------------------------------------------------------
void EnrichmentPlant::AddMassU5(int time, double mass){
  fMassU5[time] = fMassU5[time] + mass;
}
// ----------------------------------------------------------
void EnrichmentPlant::AddMassU8(int time, double mass){
  fMassU8[time] = fMassU8[time] + mass;
}

// ----------------------------------------------------------
void EnrichmentPlant::FuelEnrichment(int time,
                                     double ReactorMass,
                                     double U5ContentInUProduct) {
                                     
  TakeFeedMassForFuel(time - fEnrichmentTime, ReactorMass, U5ContentInUProduct);
  FuelEnrichmentProcess(time - fEnrichmentTime, ReactorMass, U5ContentInUProduct);
  
  
}
// ----------------------------------------------------------
void EnrichmentPlant::TakeFeedMassForFuel(int time,
                                          double ReactorMass,
                                          double U5ContentInUProduct) {
                                          
  double MassU5InFeedStock = fFeedStock->GetMassU5(time);
  double MassU8InFeedStock = fFeedStock->GetMassU8(time);
  
  double U5ContentInUFeed = MassU5InFeedStock /
                            (MassU5InFeedStock + MassU8InFeedStock);
  double Rendement = (U5ContentInUFeed    - fU5ContentInUWaste) /
                     (U5ContentInUProduct - fU5ContentInUWaste);
                     
  double URequiredMassFromFeed = ReactorMass / Rendement;
  
  // Add Feed mass in the EP
  fMassU5[time] += URequiredMassFromFeed * U5ContentInUFeed;
  fMassU8[time] += URequiredMassFromFeed * (1 - U5ContentInUFeed);
  
  // Remove Feed mass in the feed stock
  GetFeedStock()->RemoveMassU5(time, URequiredMassFromFeed * U5ContentInUFeed);
  GetFeedStock()->RemoveMassU8(time, URequiredMassFromFeed * (1 - U5ContentInUFeed));
  
}
// ----------------------------------------------------------
void EnrichmentPlant::FuelEnrichmentProcess(int time,
                                            double ReactorMass,
                                            double U5ContentInUProduct) {
                                            
  int tStart = time + 1;
  int tStop  = time + fEnrichmentTime;
  
  double MassU5InFeedStock = fFeedStock->GetMassU5(time);
  double MassU8InFeedStock = fFeedStock->GetMassU8(time);
  
  double U5ContentInUFeed = MassU5InFeedStock /
                            (MassU5InFeedStock + MassU8InFeedStock);
  double Rendement = (U5ContentInUFeed    - fU5ContentInUWaste) /
                     (U5ContentInUProduct - fU5ContentInUWaste);
                     
  double URequiredMassFromFeed = ReactorMass / Rendement;
  
  for(int t = tStart; t <= tStop; t++) {
  
    double MassOfFeedInDT = URequiredMassFromFeed / fEnrichmentTime;
    double MassOfProductInDT = MassOfFeedInDT * Rendement;
    double MassOfWasteInDT = MassOfFeedInDT - MassOfProductInDT;
    
    // Remove Waste mass in the EP
    fMassU5[t] -= MassOfWasteInDT * fU5ContentInUWaste;
    fMassU8[t] -= MassOfWasteInDT * (1 - fU5ContentInUWaste);
    
    // Push Waste mass in the Waste Stock
    GetWasteStock()->AddMassU5(t, MassOfWasteInDT * fU5ContentInUWaste);
    GetWasteStock()->AddMassU8(t, MassOfWasteInDT * (1 - fU5ContentInUWaste)); 
  }
}
