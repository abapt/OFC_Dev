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
    		vector<double> reactor_U5 = fReactor[r]->GetMassU5Evo();
    		vector<double> reactor_U8 = fReactor[r]->GetMassU8Evo();

    		fOutputFileName << reactor_U5[t] << " " << reactor_U8[t] << " ";
  		}

  		for (int e=0; e<fEnrichmentPlant.size(); e++) {
    		vector<double> EP_U5App = fEnrichmentPlant[e]->GetMassU5App();
    		vector<double> EP_U8App = fEnrichmentPlant[e]->GetMassU8App();

    		vector<double> EP_U5Nat = fEnrichmentPlant[e]->GetMassU5Nat();
    		vector<double> EP_U8Nat = fEnrichmentPlant[e]->GetMassU8Nat();

    		vector<double> EP_U5Enr = fEnrichmentPlant[e]->GetMassU5Enr();
    		vector<double> EP_U8Enr = fEnrichmentPlant[e]->GetMassU8Enr();

    		fOutputFileName << EP_U5App[t] << " " << EP_U8App[t] << " " << EP_U5Nat[t] << " " << EP_U8Nat[t] << " " << EP_U5Enr[t] << " " << EP_U8Enr[t] << " ";
    	}

  		for (int s=0; s<fStock.size(); s++) {
    		vector<double> stock_U5App = fStock[s]->GetMassU5App();
    		vector<double> stock_U8App = fStock[s]->GetMassU8App();

			vector<double> stock_U5Waste = fStock[s]->GetMassU5Waste();
    		vector<double> stock_U8Waste = fStock[s]->GetMassU8Waste();

			vector<double> stock_U5Nat = fStock[s]->GetMassU5Nat();
    		vector<double> stock_U8Nat= fStock[s]->GetMassU8Nat();

    		fOutputFileName << stock_U5App[t] << " " << stock_U8App[t] << " " << stock_U5Waste[t] << " " << stock_U8Waste[t] << " " << stock_U5Nat[t] << " " << stock_U8Nat[t];
  		}
		fOutputFileName << endl;
	}
}
