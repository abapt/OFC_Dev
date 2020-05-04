#include"Scenario.hxx"
#include"Stock.hxx"
#include"Reactor.hxx"
#include"EnrichmentPlant.hxx"

#include<vector>
#include <iostream>
#include <fstream>
#include<string>

using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Scenario::Scenario(int startingTime) {
  fStartingTime = startingTime;
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Scenario::~Scenario() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////


// -----------------------------------------------------------
void Scenario::AddReactor(Reactor* reactor) {
  fReactor.push_back(reactor);
}
// -----------------------------------------------------------
void Scenario::AddStock(Stock* stock) {
  fStock.push_back(stock);
}
// -----------------------------------------------------------
void Scenario::AddEnrichmentPlant(EnrichmentPlant* enrichmentplant) {
  fEnrichmentPlant.push_back(enrichmentplant);
}
//-----------------------------------------------------------
void Scenario::Evolution(int t) {
  BuildStatusVector();
  
// ----------  Status Loop ----------  //
  for(t = 0; t < fScenarioTime; t++) {
    for(int r = 0; r < fReactor.size(); r++) {
      if(fStatus[t] == 0) {
        fReactor[r]->Evolution(t); // Evolution under neutron flux
      }
      
      if(fStatus[t] == 1) {
        // @ t-2
        // Take needed UNat from UNat Stock and put it in EP
        // @ t-1
        // Enrichment of half of UNat
        // keep Uenr in EP in variable
        // keep Uapp in EP in variable
        // @ t
        // Enrichment of the other half of UNat
        // Push Uapp in Stock Uapp
        // Remove Uenr from EP
        fReactor[r]->GetEnrichmentPlant()->FuelNatLoad(t);
        fReactor[r]->GetEnrichmentPlant()->FuelConversion(t);
        fReactor[r]->GetEnrichmentPlant()->PushUApp(t);
        fReactor[r]->Load(t);
      }
      
      if(fStatus[t] == 2) {
        fReactor[r]->Evolution(t); // Evolution under neutron flux
        fReactor[r]->Drain(t); // Push spent uox in stock
        fReactor[r]->GetEnrichmentPlant()->FuelNatLoad(t);
        fReactor[r]->GetEnrichmentPlant()->FuelConversion(t);
        fReactor[r]->GetEnrichmentPlant()->PushUApp(t);
        fReactor[r]->Load(t);
      }
      
      if(fStatus[t] == 4) {
        fReactor[r]->Evolution(t); // Evolution under neutron flux
        fReactor[r]->Drain(t); // Push spent uox in stock
      }
    }
  }
}

//-----------------------------------------------------------
void Scenario::BuildStatusVector() {
  // Status of the events
  // 0 nothing
  // 1 reactor Starting
  // 2 reactor new cycle
  // 4 reactor ShutDown
  
  for(int t = 0; t < fScenarioTime; t++) { fStatus.push_back(0); }
  
  for(int r = 0; r < fReactor.size(); r++) {
    int R_StartingTime = fReactor[r]->GetStartingTime();
    int R_ShutdownTime = (fReactor[r]->GetStartingTime()) +
                         (fReactor[r]->GetLifeTime());
    int R_CycleTime = fReactor[r]->GetCycleTime();
    
    for(int t = R_StartingTime; t <= R_ShutdownTime; t++) {
// ----------  Reactor Loop ----------  //
      if(t == R_StartingTime) {
        fStatus[r] = 1;
      }
      
      if(t == R_ShutdownTime) {
        fStatus[r] = 4;
      }
      
      if(((t - R_StartingTime) % R_CycleTime) == 0 &&
          t != R_StartingTime &&
          t != R_ShutdownTime)  {
          
        fStatus[r] = 2;
      }
    }
  }
}

//-----------------------------------------------------------
void Scenario::WriteOutput(string OutputFileName) {
	ofstream fOutputFileName;

	for(int t=0; t<fScenarioTime; t++) {

		fOutputFileName << t << " ";

		for (int r=0; r< fReactor.size(); r++) {
    		double reactor_U5 = fReactor[r]->GetMassU5React(t);
    		double reactor_U8 = fReactor[r]->GetMassU8React(t);

    		fOutputFileName << reactor_U5 << " " << reactor_U8 << " ";
  		}

  		for (int e=0; e<fEnrichmentPlant.size(); e++) {
    		double EP_U5App = fEnrichmentPlant[e]->GetMassU5AppEP(t);
    		double EP_U8App = fEnrichmentPlant[e]->GetMassU8AppEP(t);

    		double EP_U5Nat = fEnrichmentPlant[e]->GetMassU5NatEP(t);
    		double EP_U8Nat = fEnrichmentPlant[e]->GetMassU8NatEP(t);

    		double EP_U5Enr = fEnrichmentPlant[e]->GetMassU5EnrEP(t);
    		double EP_U8Enr = fEnrichmentPlant[e]->GetMassU8EnrEP(t);

    		fOutputFileName << EP_U5App << " " << EP_U8App << " " << EP_U5Nat << " " << EP_U8Nat << " " << EP_U5Enr << " " << EP_U8Enr << " ";
    	}

  		for (int s=0; s<fStock.size(); s++) {
    		double stock_U5App = fStock[s]->GetMassU5AppStock(t);
    		double stock_U8App = fStock[s]->GetMassU8AppStock(t);

			double stock_U5Waste = fStock[s]->GetMassU5WasteStock(t);
    		double stock_U8Waste = fStock[s]->GetMassU8WasteStock(t);

			double stock_U5Nat = fStock[s]->GetMassU5NatStock(t);
    		double stock_U8Nat= fStock[s]->GetMassU8NatStock(t);

    		fOutputFileName << stock_U5App << " " << stock_U8App << " " << stock_U5Waste << " " << stock_U8Waste << " " << stock_U5Nat << " " << stock_U8Nat;
  		}
		fOutputFileName << endl;
	}
}
