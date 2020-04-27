#include"Scenario.hxx"
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
void Scenario::EnrichmentPlantEvolution(){
	for (int i=0; i<(int)fEnrichmentPlant.size(); ++i)
	{
		fEnrichmentPlant[i]->Evolution();
	}
	for (int i=0; i<(int)fEnrichmentPlant.size(); ++i)
	{
		fEnrichmentPlant[i]->GiveReactor();
	}
}
// -----------------------------------------------------------
void Scenario::StockEvolution(){
	for (int i=0; i<(int)fStock.size(); ++i)
	{
		fStock[i]->PrelevementEP();
	}
}
void Scenario::Evolution(int t){
}

void Scenario::BuildStatusVector(){
  // Status of the events
  // 0 nothing
  // 1 reactor Starting
  // 2 reactor new cycle
  // 4 reactor ShutDown

  for (t(0); t<fScenarioTime; t++) fStatus.push_back(0);

  // loop on reactors
  // => Reactor Add 1 
}



