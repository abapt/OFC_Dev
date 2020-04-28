#include"Scenario.hxx"
#include"Stock.hxx"
#include"Reactor.hxx"
#include"EnrichmentPlant.hxx"

#include<vector>
#include<string>

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
void Scenario::ReactorEvolution() {
	for(int i = 0; i < (int)fReactor.size(); ++i) {
		fReactor[i]->Evolution(fStartingTime);
	}
}
// -----------------------------------------------------------
/*void Scenario::EnrichmentPlantEvolution(){
	for (int i=0; i<(int)fEnrichmentPlant.size(); ++i)
	{
		fEnrichmentPlant[i]->GiveReactorUenr();
		fEnrichmentPlant[i]->PushUapp();
	}
}*/
// -----------------------------------------------------------
void Scenario::StockEvolution() {
	for(int i = 0; i < (int)fStock.size(); ++i) {
		fStock[i]->PrelevementEPUnat(fScenarioTime);
	}
}

//-----------------------------------------------------------
void Scenario::Evolution(int t) {
	BuildStatusVector();
	
// ----------  Status Loop ----------  //
	for(t = 0; t < fScenarioTime; ++t) {
	
		if(fStatus[t] == 0) {
			ReactorEvolution(); // Evolution under neutron flux
		}

		if(fStatus[t] == 1) {
			ReactorStarting();
		}
		
		if(fStatus[t] == 2) {
			ReactorDrainFuel(); // Push spent uox in stock
			FuelEnrichment();   // Take Feed and Push Uapp and Keep Uenr
			ReactorLoadFuel();  // Take Uenr from EP
		}
		
		if(fStatus[t] == 3) {
			FuelEnrichment();   // Take Feed and Push Uapp and Keep Uenr
			ReactorLoadFuel();  // Take Uenr from EP
		}
		
		if(fStatus[t] == 4) {
			ReactorDrainFuel(); // Push spent uox in stock
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
		int R_StartingTime = fReactor[i]->GetStartingTime();
		int R_ShutdownTime = (fReactor[i]->GetStartingTime()) +
		                     (fReactor[i]->GetLifeTime());
		int R_CycleTime = fReactor[i]->GetCycleTime();
		
		for(int t = R_StartingTime; t <= R_ShutdownTime; t++) {
// ----------  Reactor Loop ----------  //
			if(t == R_StartingTime) {
				fStatus[i] += 1;
			}
			
			if(t == R_ShutdownTime) {
				fStatus[i] += 4;
			}
			
			if(((t - R_StartingTime) % R_CycleTime) == 0)  {
				fStatus[i] += 2;
			} //A voir
		}
	}
}



