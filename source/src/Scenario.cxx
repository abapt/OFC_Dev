#include"Scenario.hxx"
#include"Stock.hxx"
#include"Reactor.hxx"
#include"EnrichmentPlant.hxx"

#include<vector>
#include<string>

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Scenario::Scenario(int startingTime){
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
void Scenario::AddReactor(Reactor* reactor){
	fReactor.push_back(reactor);
}
// -----------------------------------------------------------
void Scenario::AddStock(Stock* stock){
	fStock.push_back(stock);
}
// -----------------------------------------------------------
void Scenario::AddEnrichmentPlant(EnrichmentPlant* enrichmentplant){
	fEnrichmentPlant.push_back(enrichmentplant);
}
// -----------------------------------------------------------
void Scenario::ReactorEvolution(){
	for (int i=0; i<(int)fReactor.size(); ++i)
	{
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
void Scenario::StockEvolution(){
	for (int i=0; i<(int)fStock.size(); ++i)
	{
		fStock[i]->PrelevementEPUnat(fScenarioTime);
	}
}

//-----------------------------------------------------------
void Scenario::Evolution(int t){
	BuildStatusVector(t);
// ----------  Status Loop ----------  //
	for (t=0; t<fScenarioTime; ++t)
	{
		if (fStatus[t] == 0) {
			ReactorEvolution();
		}
		if (fStatus[t] == 1) {
			ReactorEvolution();
		}
		if (fStatus[t] == 2) 
		{
			ReactorEvolution();
			// EnrichmentPlantEvolution();
			StockEvolution();
		}
		if (fStatus[t] == 4) {
			ReactorEvolution();
		}
	}

}

//-----------------------------------------------------------
void Scenario::BuildStatusVector(int t){
  // Status of the events
  // 0 nothing
  // 1 reactor Starting
  // 2 reactor new cycle
  // 4 reactor ShutDown

  for (int t=0; t<fScenarioTime; ++t) fStatus.push_back(0);
  for (int i=0; i<fReactor.size(); ++i)
  {
  	int R_StartingTime = fReactor[i]->GetStartingTime();
  	int R_ShutdownTime = (fReactor[i]->GetStartingTime())+
  				 	 	 (fReactor[i]->GetLifeTime());
  	int R_CycleTime = fReactor[i]->GetCycleTime();

// ----------  Reactor Loop ----------  //
	if (i == R_StartingTime) {fStatus[i] += 1;}
	if (i == R_ShutdownTime) {fStatus[i] += 4;}
	if ((i-R_StartingTime)%R_CycleTime == 0 && i != R_StartingTime) 
	{
		fStatus[i] += 2;
	} //A voir

  }
}



