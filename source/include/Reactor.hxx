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
	        double fPower,
	        double fMassHN,
	        double fBurnUp,
	        double fLoadFactor); //Constructeur
	~Reactor(); //Destructeur
	
	int GetStartingTime() const {
		return fStartingTime;
	}
	int GetLifeTime() const {
		return fLifeTime;
	}
	double GetMassHN() const {
		return fMassHN;
	}  // Masse de noyaux lourds au début du cycle
	double GetBurnUp() const {
		return fBurnUp;
	}  // BurnUp à la fin du cycle
	double GetLoadFactor() const {
		return fLoadFactor;
	}  // facteur de "remplissage" du réacteur
	double GetPower() const {
		return fPower;
	}  // temps de cycle du réacteur
	double GetEnrichissement() const {
		return fEnrichissement;
	}
	double GetCrossSection() const {
		return fCrossSection;
	}
	int GetCycleTime() {
		return fCycleTime;
	}
  EnrichmentPlant* GetEnrichmentPlant() {
    return fEnrichmentPlant;
  }
	
  void SetEnrichmentPlant(EnrichmentPlant* EP) {
    fEnrichmentPlant = EP;
  }
	void SetStartingTime(int StartingTime) {
		fStartingTime = StartingTime;
	}
	void SetName(string Name) {
		fName = Name;
	}
	void SetMassHN(double Mass) {
		fMassHN = Mass;
	}  // défini le masse de noyaux fissiles au début du cycle
	
	void Evolution(int t);
	void Start(int t);
	void Drain(int t);
	void Load(int t);
	void Push(int t);
	
	void CalculateU5Enrichment(double fBurnUp);
	
private :

	string fName;
	int fStartingTime;
	int fCycleTime;
	int fLifeTime;
	
	double fMassHN;
	double fPower;
	double fLoadFactor;
	double fBurnUp;
	double fEnrichissement;
	double fCrossSection;

	EnrichmentPlant* fEnrichmentPlant;
	Stock* fStock;
	
	//Evolution data
	double fFlux;
	vector<double> fMassU5Evolution;
	vector<double> fMassU8Evolution;
};

#endif