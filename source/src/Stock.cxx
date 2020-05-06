#include "Stock.hxx"
#include "EnrichmentPlant.hxx"
#include "Scenario.hxx"

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Stock::Stock(int ScenarioTime) {
  	fScenarioTime = ScenarioTime;

  	for(int t=0; t<fScenarioTime; t++) {
    	fMassU5Waste.push_back(0);
    	fMassU8Waste.push_back(0);
  	}

	SetName("Stock.");
}

Stock::Stock(double MassUApp,
			 int ScenarioTime) {
  	fScenarioTime = ScenarioTime;
; 
  	for(int t=0; t<fScenarioTime; t++) {
    	fMassU5App.push_back(0);
    	fMassU8App.push_back(0);
  	}

	SetName("Stock.");
}

Stock::Stock(double MassUNat,
             double MineU5UContent,
             int ScenarioTime) {
  	fMassUNat = MassUNat;
  	fMineU5UContent = MineU5UContent;

  	fScenarioTime = ScenarioTime;

  	for(int t=0; t<fScenarioTime; t++) {
    	fMassU5Nat.push_back(0);
    	fMassU8Nat.push_back(0);
  	}

  	SetName("Stock.");
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Stock::~Stock() {}
