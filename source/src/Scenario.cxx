#include"Scenario.hxx"
#include<vector>
#include<string>

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Scenario::Scenario(double startingTime){
	fStartingTime = startingTime;
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Scenario::~Scenario() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void Scenario::ReactorEvolution(){
	for (int i=0; i<(int)fReactor.size(); ++i)
	{
		fReactor[i]->Evolution(fStartingTime);
	}
	for (int i = 0; i < (int)fReactor.size(); ++i) 
	{
		fReactor[i]->Dump();
	}
}

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

void Scenario::StockEvolution(){
	for (int i=0; i<(int)fStock.size(); ++i)
	{
		fStock[i]->PrelevementEP();
	}
}

void Scenario::StatusVectorBuild(double fStartingTime, 
								 double fEndingTime){
	double fTime = fStartingTime - fEndingTime;
	vector<int> fStatus = vector<int> (fTime,0);
	
	// Status of the reactor
	// 0 : Nothing
	// 1 : Fresh Fuel Loading
	// 2 : Spent Fuel Pushing
	// 4 : Evolution
	vector <int> fStatus;


}

void Scenario::Evolution(int t){
StatusVectorBuild(t);

}