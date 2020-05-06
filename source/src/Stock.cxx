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
    	fMassU5Spent.push_back(0);
    	fMassU8Spent.push_back(0);
  	}

	SetName("Stock.");
}

Stock::Stock(double MassUWaste,
			 int ScenarioTime) {
  	fScenarioTime = ScenarioTime;
; 
  	for(int t=0; t<fScenarioTime; t++) {
    	fMassU5Waste.push_back(0);
    	fMassU8Waste.push_back(0);
  	}

	SetName("Stock.");
}

Stock::Stock(double MassUFeed,
             double MineU5UContent,
             int ScenarioTime) {
  	fMassUFeed = MassUFeed;
  	fMineU5UContent = MineU5UContent;

  	fScenarioTime = ScenarioTime;

  	for(int t=0; t<fScenarioTime; t++) {
    	fMassU5Feed.push_back(0);
    	fMassU8Feed.push_back(0);
  	}

  	SetName("Stock.");
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Stock::~Stock() {}
