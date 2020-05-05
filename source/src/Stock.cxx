#include "Stock.hxx"
#include "EnrichmentPlant.hxx"
#include "Scenario.hxx"

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Stock::Stock() {
	/*int ScenarioTime = sScenario->GetScenarioTime();

	for(int t=0; t<ScenarioTime; t++) {
		fMassU5Waste.push_back(0);
		fMassU8Waste.push_back(0);
	}
	fMassU5Waste[0]=0;
	fMassU8Waste[0]=0;*/

	SetName("Stock.");
}

Stock::Stock(double MassUApp) {
	/*int ScenarioTime = sScenario->GetScenarioTime();

	for(int t=0; t<ScenarioTime; t++) {
		fMassU5App.push_back(0);
		fMassU8App.push_back(0);
	}
	fMassU5App[0]=0;
	fMassU8App[0]=0;*/

	SetName("Stock.");
}

Stock::Stock(double MassUNat,
             double MineU5UContent) {
  fMassUNat = MassUNat;
  fMineU5UContent = MineU5UContent;

  /*int ScenarioTime = sScenario->GetScenarioTime();

  for(int t=0; t<ScenarioTime; t++) {
		fMassU5Nat.push_back(0);
		fMassU8Nat.push_back(0);
	}
	fMassU5Nat[0]=fMassUNat*fMineU5UContent;
	fMassU8Nat[0]=fMassUNat-fMassU5Nat[0];*/

  SetName("Stock.");
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Stock::~Stock() {}
