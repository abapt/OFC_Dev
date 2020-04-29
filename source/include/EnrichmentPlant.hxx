#ifndef _EnrichmentPlant_
#define _EnrichmentPlant_

#include<vector>
#include <string>

using namespace std;

class Reactor;
class Scenario;
class Stock;

class EnrichmentPlant {
public :
	EnrichmentPlant(double WasteU5Content); //Constructeur simple
	~EnrichmentPlant(); //Destructeur
	
	void SetName(string Name) {
		fName = Name;
	}
	
	double GetUnatEachLoad(){
		return fNeededUnatMassesByReactorLoading;
	}
	double GetUappEachLoad() {
		return fNeededUappMassesByReactorLoading;
	}
	double GetUenrEachLoad(){
		return fNeededUenrMassesByReactorLoading;
	}
	double GetRendement() {
		return fRendement;
	}

	vector<double> GetMassU5App() {
    	return fMassU5App;
  	}
 	vector<double> GetMassU8App() {
    	return fMassU8App;
  	}	
  	vector<double> GetMassU5Nat() {
    	return fMassU5Nat;
  	}
  	vector<double> GetMassU8Nat() {
    	return fMassU8Nat;
  	}
  	vector<double> GetMassU5Enr() {
    	return fMassU5Enr;
  	}
  	vector<double> GetMassU8Enr() {
    	return fMassU8Enr;
  	}

	double CalculateNeededMasses();

	void FuelNatLoad(int t); 
	void FuelConversion(int t);
	void PushUApp(int t);
	
private :
	vector<double> fMassU5Enr; // AMount of U5 
	vector<double> fMassU8Enr;

	vector<double> fMassU5App;
 	vector<double> fMassU8App;
  
 	vector<double> fMassU5Nat;
 	vector<double> fMassU8Nat;

 	Stock* fStock;
	Reactor* fReactor;
	
	string fName;
	double fU5ContentInUapp;
	double fU5ContentInUenr;
	double fU5ContentInUnat;
	double fRendement;
	double fNeededUenrMassesByReactorLoading;
	double fNeededUappMassesByReactorLoading;
	double fNeededUnatMassesByReactorLoading;
};

#endif