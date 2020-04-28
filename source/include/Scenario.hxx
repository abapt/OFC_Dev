#include<vector>
#include<string>

using namespace std;

class Reactor;
class Stock;
class EnrichmentPlant;

class Scenario {
public :
	Scenario(int startingTime);
	~Scenario();
	
	int GetStartingTime() const {
		return fStartingTime;
	}
	int GetScenarioTime() const {
		return fScenarioTime;
	}
	int GetEndingTime() const {
		return fEndingTime;
	}
	void SetStartingTime(int StartingTime) {
		fStartingTime = StartingTime;
	}
	void SetScenarioTime(int ScenarioTime) {
		fScenarioTime = ScenarioTime;
	}
	void SetEndingTime(int EndingTime) {
		fEndingTime = EndingTime;
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
	
	void AddReactor(Reactor* reactor);
	void AddStock(Stock* stock);
	void AddEnrichmentPlant(EnrichmentPlant* enrichmentplant);
	
	void BuildStatusVector(); // Build the time vector with facilities status event
	void Evolution(int t);  // Evolution
	void ReactorEvolution();           // Reactor Evolution
	void EnrichmentPlantEvolution();  // EnrichmentPlant Evolution
	void StockEvolution();           // Stock Evolution
	
private :

	vector<int> fStatus; // Events status
	
	int fStartingTime; // début de simulation (an)
	int fEndingTime; // fin de simulation (an)
	int fScenarioTime; // Durée de la simulation (an)
	
	
	vector<Stock*> fStock; // Vecteur Stock
	vector<Reactor*> fReactor; // Vecteur Reactor
	vector<EnrichmentPlant*> fEnrichmentPlant; // Vecteur EnrichmentPlant
};