#include<vector>
#include <string>

using namespace std;

class Reactor
{
public :
	Reactor(); //Constructeur simple
	Reactor(double fStartingTime, double fLifeTime, double fPower, double fMassHN,double fBurnUp, 
			double fLoadFactor); //Constructeur
	~Reactor(); //Destructeur

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
  	void SetName(string Name){
  		fName = Name;
  	}
  	void SetMassHN(double Mass) {
    	fMassHN = Mass;
  	}  // défini le masse de noyaux fissiles au début du cycle

  	void Evolution(double t);  // Evolution jusqu'à t 			-- A voir
 	// void Dump();   Vider   							-- A voir 
  	// void SetNewFuel();   Remplace le combustible 		-- A voir dans scénario

	void CalculateU5Enrichment(double fBurnUp);

private :

	string fName;
	double fMassHN;
	double fPower;
	double fLoadFactor;
	double fBurnUp;
	double fCycleTime;
	double fStartingTime;
	double fLifeTime;
	const double fEnrichissement = 0.04;
	const double fCrossSection = 46.933e-24;
	vector<double> fFlux;
	vector<double> fMassU5Evolution;					//-- A voir
	vector<double> fMassU8Evolution;					//-- A voir
};