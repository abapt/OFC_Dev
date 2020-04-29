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
// -----------------------------------------------------------
void Scenario::ReactorEvolution(int t) {
	for(int i = 0; i < (int)fReactor.size(); i++) {
		fReactor[i]->Evolution(t);
	}
}
// -----------------------------------------------------------
void Scenario::ReactorStarting(int t) {
	for(int i = 0; i < (int)fReactor.size(); i++) {
		fReactor[i]->Start(t);
	}
}
// -----------------------------------------------------------
void Scenario::EPFuelEnrichment(int t){
	for (int i=0; i<(int)fEnrichmentPlant.size(); i++)
	{
		fEnrichmentPlant[i]->FuelNatLoad(t);
		fEnrichmentPlant[i]->FuelConversion(t);
		fEnrichmentPlant[i]->PushUApp(t);
	}
}
// -----------------------------------------------------------
void Scenario::ReactorDrainFuel(int t) {
	for(int i = 0; i < (int)fReactor.size(); i++) {
		fReactor[i]->Drain(t);
}
}
// -----------------------------------------------------------
void Scenario::ReactorLoadFuel(int t) {
	for(int i = 0; i < (int)fReactor.size(); i++) {
		fReactor[i]->Load(t);
	}
}

//-----------------------------------------------------------
void Scenario::Evolution(int t) {
	BuildStatusVector();
	
// ----------  Status Loop ----------  //
	for(t = 0; t < fScenarioTime; t++) {
	
		if(fStatus[t] == 0) {
			ReactorEvolution(t); // Evolution under neutron flux
		}

		if(fStatus[t] == 1) {
			ReactorStarting(t);
		}
		
		if(fStatus[t] == 2) {
			ReactorEvolution(t); // Evolution under neutron flux
			ReactorDrainFuel(t); // Push spent uox in stock
			EPFuelEnrichment(t);   // Take Feed and Push Uapp and Keep Uenr
			ReactorLoadFuel(t);  // Take Uenr from EP
		}
		
		if(fStatus[t] == 3) {
			EPFuelEnrichment(t);   // Take Feed and Push Uapp and Keep Uenr
			ReactorLoadFuel(t);  // Take Uenr from EP
		}
		
		if(fStatus[t] == 4) {
			ReactorEvolution(t); // Evolution under neutron flux
			ReactorDrainFuel(t); // Push spent uox in stock
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
				fStatus[r] += 1;
			}
			
			if(t == R_ShutdownTime) {
				fStatus[r] += 4;
			}
			
			if(((t - R_StartingTime) % R_CycleTime) == 0)  {
				fStatus[r] += 2;
			} 
		}
	}
}



