#include<vector>
#include<string>

using namespace std;

class Reactor;
class Stock;
class EnrichmentPlant;

class Scenario
{
public :
	Scenario(double startingTime);
	~Scenario();

	double GetStartingTime() const{
		return fStartingTime;
	}
	double GetEndingTime() const{
		return fEndingTime;
	}
	double SetStartingTime(double ZeroTime) {
		fStartingTime = ZeroTime;
	}
	double SetScenarioTime(double EndTime) {
		fEndingTime = EndTime;
	}

	void StatusVectorBuild(double time);
	void Evolution();  // Evolution
  	void ReactorEvolution();           // Reactor Evolution
  	void EnrichmentPlantEvolution();  // EnrichmentPlant Evolution
  	void StockEvolution();           // Stock Evolution

private :
	vector<int> fStatus; // statut des unités
	double fStartingTime; // début de simulation (an)
	double fEndingTime; // fin de simulation (an)
	vector<Stock*> fStock; // Vecteur Stock
  	vector<Reactor*> fReactor; // Vecteur Reactor          
  	vector<EnrichmentPlant*> fEnrichmentPlant; // Vecteur EnrichmentPlant
};