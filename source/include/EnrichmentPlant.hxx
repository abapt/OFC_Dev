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
	EnrichmentPlant(double WasteU5Content,
					int fScenarioTime); //Constructeur simple
	~EnrichmentPlant(); //Destructeur
	
	void SetName(string Name) {
		fName = Name;
	}
	
	double GetUnatEachLoad(){
		return fNeededUnatMassesByReactorLoading; // Mass UNat by Load
	}
	double GetUappEachLoad() {
		return fNeededUappMassesByReactorLoading; // Mass UApp by Load
	}
	double GetUenrEachLoad(){
		return fNeededUenrMassesByReactorLoading; // Mass UEnr by Load
	}
	double GetRendement() {
		return fRendement; // Rendement
	}

	vector<double> GetMassU5App() {
    	return fMassU5App; // Mass U5 in App created
  	}
 	vector<double> GetMassU8App() {
    	return fMassU8App; // Mass U8 in App created
  	}	
  	vector<double> GetMassU5Nat() {
    	return fMassU5Nat; // Mass U5 in Nat taken from mine
  	}
  	vector<double> GetMassU8Nat() {
    	return fMassU8Nat; // Mass U8 in Nat taken from mine
  	}
  	vector<double> GetMassU5Enr() {
    	return fMassU5Enr; // Mass U5 in Enr created
  	}
  	vector<double> GetMassU8Enr() {
    	return fMassU8Enr; // Mass U8 in Enr created
  	}

  	double GetMassU5EnrEP(int t){
		return fMassU5Enr[t];
	}
	double GetMassU8EnrEP(int t){
		return fMassU8Enr[t];
	}
	double GetMassU5AppEP(int t){
		return fMassU5App[t];
	}
	double GetMassU8AppEP(int t){
		return fMassU8App[t];
	}
	double GetMassU5NatEP(int t){
		return fMassU5Nat[t];
	}
	double GetMassU8NatEP(int t){
		return fMassU8Nat[t];
	}

	Stock* GetStock() {
    	return fStock; // point to Stock
  	}
  	void SetStock(Stock* Stock) {
    	fStock = Stock;
 	}
 	Reactor* GetReactor(){
 		return fReactor;
 	}
 	void SetReactor(Reactor* reactor){
 		fReactor = reactor;
 	}

	void CalculateNeededMasses();

	void FuelNatLoad(int t); 
	void FuelConversion(int t);
	void PushUApp(int t);
	
private :
	vector<double> fMassU5Enr; // Amount of U5 
	vector<double> fMassU8Enr;

	vector<double> fMassU5App;
 	vector<double> fMassU8App;
  
 	vector<double> fMassU5Nat;
 	vector<double> fMassU8Nat;

 	Stock* fStock; // point to stock
	Reactor* fReactor; // point to reactor
	Scenario* fScenario;
	
	vector<Stock*> epStock;

	string fName;
	double fU5ContentInUapp;
	double fU5ContentInUenr;
	double fU5ContentInUnat;
	double fRendement;
	int fScenarioTime;
	double fNeededUenrMassesByReactorLoading;
	double fNeededUappMassesByReactorLoading;
	double fNeededUnatMassesByReactorLoading;
};

#endif