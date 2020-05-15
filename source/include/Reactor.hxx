#ifndef _Reactor_
#define _Reactor_

#include<vector>
#include <string>

using namespace std;

class Stock;
class EnrichmentPlant;

class Reactor {
public :
	Reactor(); //Constructeur simple
	Reactor(double fLifeTime,
			double fStartingTime,
			int fScenarioTime,
	        double fPower,
	        double fMassHN,
	        double fBurnUp,
	        double fLoadFactor); //Constructeur
	~Reactor(); //Destructeur
	
	int GetStartingTime(){
		return fStartingTime;
	}
	int GetLifeTime(){
		return fLifeTime;
	}
	double GetMassHN() {
		return fMassHN*1000;
	}  // Masse de noyaux lourds au début du cycle
	double GetBurnUp() {
		return fBurnUp;
	}  // BurnUp à la fin du cycle
	double GetLoadFactor() {
		return fLoadFactor;
	}  // facteur de "remplissage" du réacteur
	double GetPower() {
		return fPower;
	}  // temps de cycle du réacteur
	double GetEnrichment() {
		return fEnrichment;
	}
	double GetCrossSectionU5() {
		return fCrossSectionU5;  // recup cross section
	}
	double GetCrossSectionU8() {
		return fCrossSectionU8;  // recup cross section
	}
	int GetCycleTime() {
		return fCycleTime; // recup cycle Time
	} 

	vector<double> GetMassU5Evo(){
		return fMassU5Evolution;
	} 
	vector<double> GetMassU8Evo(){
		return fMassU8Evolution;
	}

	double GetMassU5React(int t){
		return fMassU5Evolution[t];
	}
	double GetMassU8React(int t){
		return fMassU8Evolution[t];
	}
	


 	EnrichmentPlant* GetEnrichmentPlant() {
    	return fEnrichmentPlant; // point to EP
  	}
  	void SetEnrichmentPlant(EnrichmentPlant* EP) {
    	fEnrichmentPlant = EP;
 	}

 	Stock* GetStock(){
 		return fStock;
 	}
 	void SetStock(Stock* stock){
 		fStock = stock;
 	}


	void SetName(string Name) {
		fName = Name;
	}
	string GetName(){
		return fName;
	}

	void SetMassHN(double Mass) {
		fMassHN = Mass;
	}  // défini le masse de noyaux fissiles au début du cycle
	
	void Evolution(int t);
	void Start(int t);
	void Drain(int t);
	void Load(int t);
	void Push(int t);
	
	void CalculateU5Enrichment(double BurnUp);
	
private :

	string fName;
	int fStartingTime;
	int fCycleTime;
	int fLifeTime;
	int fScenarioTime;
	
	double fMassHN;
	double fPower;
	double fLoadFactor;
	double fBurnUp;
	double fEnrichment;
	double fCrossSectionU5;
	double fCrossSectionU8;

	EnrichmentPlant* fEnrichmentPlant;
	Stock* fStock;
	
	//Evolution data
	double fFlux;
	vector<double> fMassU5Evolution;
	vector<double> fMassU8Evolution;
	vector<double> fMassOtherEvolution;
};

#endif