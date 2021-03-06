#ifndef _Scenario_
#define _Scenario_

#include<vector>
#include<string>

using namespace std;

class Reactor;
class Stock;
class EnrichmentPlant;

class Scenario {
public :
	Scenario(int fScenarioTime);
	~Scenario();
	
	int GetStartingTime() {
		return fStartingTime;
	}
	int GetScenarioTime() {
		return fScenarioTime;
	}
	int GetEndingTime() {
		return fEndingTime;
	}
	void SetStartingTime(int StartingTime) {
		fStartingTime = StartingTime;
	}
	void SetEndingTime(int EndingTime) {
		fEndingTime = EndingTime;
	}
	void SetScenarioOutFile(string outName){
		fOutputFile = outName;
	}

	
	vector<Reactor*> GetReactor() {
		return fReactor;
	}
	vector<Stock*> GetStock() {
		return fStock;
	}
	vector<EnrichmentPlant*> GetEnrichmentPlant() {
		return fEnrichmentPlant;
	}
	vector<int> GetStatus() {
		return fStatus;
	}


	void AddReactor(Reactor* reactor);
	void AddStock(Stock* stock);
	void AddEnrichmentPlant(EnrichmentPlant* enrichmentplant);
	
	void BuildStatusVector(); // Build the time vector with facilities status event
	void Evolution(int t);  // Evolution
	void ReactorEvolution(int t);           // Reactor Evolution
	void ReactorStarting(int t); // Start of Reactor
	void ReactorDrainFuel(int t);
	void ReactorLoadFuel(int t);
	void EPFuelEnrichment(int t);  // EnrichmentPlant Evolution
	
	void WriteOutput(string fOutputFile);


private :

	vector<int> fStatus; // Events status
	string fOutputFile;
	
	int fStartingTime; // début de simulation (an)
	int fEndingTime; // fin de simulation (an)
	int fScenarioTime; // Durée de la simulation (an)

	
	vector<Stock*> fStock; // Vecteur Stock
	vector<Reactor*> fReactor; // Vecteur Reactor
	vector<EnrichmentPlant*> fEnrichmentPlant; // Vecteur EnrichmentPlant

	EnrichmentPlant* fEnrichmentPlantPoint; // Pointeur Ep
	Stock* fStockPoint; // Pointeur Stock
	Reactor* fReactorPoint; // Pointeur Reactor
};

#endif