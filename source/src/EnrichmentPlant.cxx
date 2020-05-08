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
void EnrichmentPlant::MassConservation(int time) {


		fMassU5[time+1] = fMassU5[time];
		fMassU8[time+1] = fMassU8[time];
	
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
 	//cout << Rendement << endl;
 	double URequiredMassFromFeed = ReactorMass / Rendement;
 	//cout << URequiredMassFromFeed << endl;
  	double MassOfFeedInT = URequiredMassFromFeed;
    //cout << MassOfFeedInT << endl;
    double MassOfProductInT = MassOfFeedInT * Rendement;

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
                                            
 	

 	double MassU5InFeedStock = fFeedStock->GetMassU5(time);
  	double MassU8InFeedStock = fFeedStock->GetMassU8(time);
  
  	double U5ContentInUFeed = MassU5InFeedStock /
                             (MassU5InFeedStock + MassU8InFeedStock);
  	double Rendement = (U5ContentInUFeed    - fU5ContentInUWaste) /
                       (U5ContentInUProduct - fU5ContentInUWaste);
                     
  	double URequiredMassFromFeed = ReactorMass / Rendement;
  	//cout << U5ContentInUProduct << endl;
  
  	double MassOfFeedInT = URequiredMassFromFeed;
    //cout << MassOfFeedInT << endl;
    double MassOfProductInT = MassOfFeedInT * Rendement;
    //cout << MassOfProductInT << endl;
    double MassOfWasteInT = MassOfFeedInT - MassOfProductInT;
    //cout << MassOfWasteInT << endl;

	// Push Product mass in the Product Stock
    GetProductStock()->AddMassU5(time, MassOfProductInT * U5ContentInUProduct);
    GetProductStock()->AddMassU8(time, MassOfProductInT * (1 - U5ContentInUProduct));

    // Push Waste mass in the Waste Stock
    GetWasteStock()->AddMassU5(time, MassOfWasteInT * fU5ContentInUWaste);
    GetWasteStock()->AddMassU8(time, MassOfWasteInT * (1 - fU5ContentInUWaste));

    // Remove Product mass in the EP
    //fMassU5[time] -= MassOfProductInT * U5ContentInUProduct;
    //fMassU8[time] -= MassOfProductInT * (1 - U5ContentInUProduct);

    // Remove Waste mass in the EP
    fMassU5[time] -= MassOfWasteInT * fU5ContentInUWaste;
    fMassU8[time] -= MassOfWasteInT * (1 - fU5ContentInUWaste);
  
}
