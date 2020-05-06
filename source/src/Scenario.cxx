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
Scenario::Scenario(int ScenarioTime) {
  fScenarioTime = ScenarioTime*8766;
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
        //fReactor[r]->GetEnrichmentPlant()->PushUApp(t);
        fReactor[r]->Load(t);
      }
      
      if(fStatus[t] == 2) {
        fReactor[r]->Evolution(t); // Evolution under neutron flux
        fReactor[r]->Drain(t); // Push spent uox in stock
        fReactor[r]->GetEnrichmentPlant()->FuelNatLoad(t);
        fReactor[r]->GetEnrichmentPlant()->FuelConversion(t);
        //fReactor[r]->GetEnrichmentPlant()->PushUApp(t);
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
        fStatus[t] = 1;
      }
      
      if(t == R_ShutdownTime) {
        fStatus[t] = 4;
      }
      
      if((t>R_StartingTime) && 
         (t<R_ShutdownTime) &&
         ((t - R_StartingTime) % (R_CycleTime) == 0))  {
        fStatus[t] = 2;
      }
    }
  }
}

//-----------------------------------------------------------
void Scenario::WriteOutput(string Out) {
  fOutputFile = Out;
	ofstream output(fOutputFile.c_str());

	for(int t=0; t<fScenarioTime; t++) {

		output << t << " " ;

		for (int r=0; r< fReactor.size(); r++) {
    		double reactor_U5 = fReactor[r]->GetMassU5React(t);
    		double reactor_U8 = fReactor[r]->GetMassU8React(t);

    		output << reactor_U5 << " " << reactor_U8 << " ";
  		}

  		for (int e=0; e<fEnrichmentPlant.size(); e++) {
    		//double EP_U5Waste = fEnrichmentPlant[e]->GetMassU5WasteEP(t);
    		//double EP_U8Waste = fEnrichmentPlant[e]->GetMassU8WasteEP(t);

    		double EP_U5Feed = fEnrichmentPlant[e]->GetMassU5FeedEP(t);
    		double EP_U8Feed = fEnrichmentPlant[e]->GetMassU8FeedEP(t);

    		double EP_U5Product = fEnrichmentPlant[e]->GetMassU5ProductEP(t);
    		double EP_U8Product = fEnrichmentPlant[e]->GetMassU8ProductEP(t);
        output << EP_U5Feed << " " << EP_U8Feed << " " << EP_U5Product << " " << EP_U8Product << " ";
    		//output << EP_U5Waste << " " << EP_U8Waste << " " << EP_U5Feed << " " << EP_U8Feed << " " << EP_U5Product << " " << EP_U8Product << " ";
    	}

  		for (int s=0; s<fStock.size(); s++) {
    		//double stock_U5Waste = fStock[s]->GetMassU5WasteStock(t);
    		//double stock_U8Waste = fStock[s]->GetMassU8WasteStock(t);

		    //double stock_U5Spent = fStock[s]->GetMassU5SpentStock(t);
    		//double stock_U8Spent = fStock[s]->GetMassU8SpentStock(t);

		    double stock_U5Feed = fStock[s]->GetMassU5FeedStock(t);
    		double stock_U8Feed= fStock[s]->GetMassU8FeedStock(t);
            
        output << stock_U5Feed << " " << stock_U8Feed << endl;
    		//output << stock_U5Waste << " " << stock_U8Waste << " " << stock_U5Spent << " " << stock_U8Spent << " " << stock_U5Feed << " " << stock_U8Feed;
  		}
		output << endl;
	}

}
