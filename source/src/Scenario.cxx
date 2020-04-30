#include"Scenario.hxx"
#include"Stock.hxx"
#include"Reactor.hxx"
#include"EnrichmentPlant.hxx"

#include<vector>
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
        fReactor[r]->GetEnrichmentPlant()[t]->FuelNatLoad(t);
        fReactor[r]->GetEnrichmentPlant()[t]->FuelConversion(t);
        fReactor[r]->GetEnrichmentPlant()[t]->PushUApp(t);
        fReactor[r]->Load(t);
      }
      
      if(fStatus[t] == 2) {
        fReactor[r]->Evolution(t); // Evolution under neutron flux
        fReactor[r]->Drain(t); // Push spent uox in stock
        fReactor[r]->GetEnrichmentPlant()[t]->FuelNatLoad(t);
        fReactor[r]->GetEnrichmentPlant()[t]->FuelConversion(t);
        fReactor[r]->GetEnrichmentPlant()[t]->PushUApp(t);
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



