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

	vector<double> GetMassU5Waste() {
    	return fMassU5Waste; // Mass U5 in App created
  	}
 	vector<double> GetMassU8Waste() {
    	return fMassU8Waste; // Mass U8 in App created
  	}	
  	vector<double> GetMassU5Feed() {
    	return fMassU5Feed; // Mass U5 in Nat taken from mine
  	}
  	vector<double> GetMassU8Feed() {
    	return fMassU8Feed; // Mass U8 in Nat taken from mine
  	}
  	vector<double> GetMassU5Product() {
    	return fMassU5Product; // Mass U5 in Enr created
  	}
  	vector<double> GetMassU8Product() {
    	return fMassU8Product; // Mass U8 in Enr created
  	}

  	double GetMassU5ProductEP(int t){
		return fMassU5Product[t];
	}
	double GetMassU8ProductEP(int t){
		return fMassU8Product[t];
	}
	double GetMassU5WasteEP(int t){
		return fMassU5Waste[t];
	}
	double GetMassU8WasteEP(int t){
		return fMassU8Waste[t];
	}
	double GetMassU5FeedEP(int t){
		return fMassU5Feed[t];
	}
	double GetMassU8FeedEP(int t){
		return fMassU8Feed[t];
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

	void AddFeedStock(FeedStock* feedstock);
	void AddWasteStock(WasteStock* wastestock);

	void CalculateNeededMasses();

	void FuelNatLoad(int t); 
	void FuelConversion(int t);
	void PushUApp(int t);
	
private :
	vector<double> fMassU5Product; // Amount of U5 
	vector<double> fMassU8Product;

	vector<double> fMassU5Waste;
 	vector<double> fMassU8Waste;
  
 	vector<double> fMassU5Feed;
 	vector<double> fMassU8Feed;

 	Stock* fStock; // point to stock
	Reactor* fReactor; // point to reactor
	Scenario* fScenario;


	vector<FeedStock*> fFeedStock;
	vector<WasteStock*> fWasteStock;
	FeedStock* fFeedStockPoint;
	WasteStock* fWasteStockPoint;
	

	string fName;
	double fU5ContentInUWaste;
	double fU5ContentInUProduct;
	double fU5ContentInUFeed;
	double fRendement;
	int fScenarioTime;
	double fNeededUenrMassesByReactorLoading;
	double fNeededUappMassesByReactorLoading;
	double fNeededUnatMassesByReactorLoading;
};

#endif