
#include<vector>
#include <string>


class Reactor
{
public :
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
  	void SetName(string Name){
  		fName = Name;
  	}
  	void SetMassHN(double Mass) {
    fMassHN = Mass;
  	}  // défini le masse de noyaux fissiles au début du cycle

  	void Evolution(t);  // Evolution jusqu'à t 			-- A voir
 	// void Dump();   Vider   							-- A voir 
  	// void SetNewFuel();   Remplace le combustible 		-- A voir dans scénario

	void CalculateU5Enrichment();

private :

	double fName;
	double fMassHN;
	double fPower;
	double fLoadFactor;
	double fBurnUp;
	double fCycleTime;
	double fStartingTime;
	double fLifeTime;
	vector<double> fMassU5Evolution;					//-- A voir
	vector<double> fMassU8Evolution;					//-- A voir
};