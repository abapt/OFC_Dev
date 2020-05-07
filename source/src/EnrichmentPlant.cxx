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

void EnrichmentPlant::SetStock(Stock* feedstock,
                               Stock* productstock,
                               Stock* wastestock) {
                               
// Mettre un if qui oblige les stocks à etre définis avant....

  fFeedStock = feedstock;
  fProductStock = productstock;
  fWasteStock = wastestock;
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
  //cout << MassU5InFeedStock << " et " << MassU8InFeedStock << endl;
  double U5ContentInUFeed = MassU5InFeedStock /
                            (MassU5InFeedStock + MassU8InFeedStock);
  //cout << U5ContentInUFeed << endl;
  double Rendement = (U5ContentInUFeed    - fU5ContentInUWaste) /
                     (U5ContentInUProduct - fU5ContentInUWaste);
  cout << Rendement << endl;
  double URequiredMassFromFeed = ReactorMass / Rendement;
  //cout << URequiredMassFromFeed << endl;
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
  //cout << U5ContentInUProduct << endl;
  for(int t = tStart; t <= tStop; t++) {
  
    double MassOfFeedInDT = URequiredMassFromFeed / (fEnrichmentTime-1);
    //cout << MassOfFeedInDT << endl;
    double MassOfProductInDT = MassOfFeedInDT * Rendement;
    //cout << MassOfProductInDT << endl;
    double MassOfWasteInDT = MassOfFeedInDT - MassOfProductInDT;
    //cout << MassOfWasteInDT << endl;

	// Push Product mass in the Product Stock
    GetProductStock()->AddMassU5(t, MassOfProductInDT * U5ContentInUProduct);
    GetProductStock()->AddMassU8(t, MassOfProductInDT * (1 - U5ContentInUProduct));

    // Push Waste mass in the Waste Stock
    GetWasteStock()->AddMassU5(t, MassOfWasteInDT * fU5ContentInUWaste);
    GetWasteStock()->AddMassU8(t, MassOfWasteInDT * (1 - fU5ContentInUWaste));

    // Remove Product mass in the EP
    fMassU5[t] -= MassOfProductInDT * U5ContentInUProduct;
    fMassU8[t] -= MassOfProductInDT * (1 - U5ContentInUProduct);

    // Remove Waste mass in the EP
    fMassU5[t] -= MassOfWasteInDT * fU5ContentInUWaste;
    fMassU8[t] -= MassOfWasteInDT * (1 - fU5ContentInUWaste);
  }
}
