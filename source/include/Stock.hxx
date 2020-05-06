#ifndef _Stock_
#define _Stock_

#include<vector>
#include <string>

using namespace std;

class EnrichmentPlant;
class Reactor;
class Scenario;

class Stock {
public :
  	Stock(int fScenarioTime);
  	Stock(double fMassUApp,
  		  int fScenarioTime);
  	Stock(double fMassUNat,
          double fMineU5UContent,
          int fScenarioTime); //Constructeur
  	~Stock(); //Destructeur
  
  	void SetName(std::string Name) {
    	fName = Name;
  	}
  	string GetName(){
  		return fName;
  	}
  
  	vector<double> GetMassU5Waste() { 
    	return fMassU5Waste; // Waste U5 stock (after reactor)
  	}
  	vector<double> GetMassU8Waste() {
    	return fMassU8Waste; // Waste U8 stock (after reactor)
  	}
  	vector<double> GetMassU5App() {
    	return fMassU5App; // App U5 stock (after EP)
  	}
  	vector<double> GetMassU8App() {
    	return fMassU8App; // App U8 stock (after EP)
  	}
  	vector<double> GetMassU5Nat() {
    	return fMassU5Nat; // U5 stock (mine)
  	}
  	vector<double> GetMassU8Nat() {
    	return fMassU8Nat; // U8 stock (mine)
  	}

  	double GetMassU5WasteStock(int t){
		return fMassU5Waste[t];
	}
	double GetMassU8WasteStock(int t){
		return fMassU8Waste[t];
	}
	double GetMassU5AppStock(int t){
		return fMassU5App[t];
	}
	double GetMassU8AppStock(int t){
		return fMassU8App[t];
	}
	double GetMassU5NatStock(int t){
		return fMassU5Nat[t];
	}
	double GetMassU8NatStock(int t){
		return fMassU8Nat[t];
	}


private :

  string fName;
  double fMassUNat;
  double fMineU5UContent;
  int fScenarioTime;
  double fMassUApp;
  double fMassUWaste;

  Scenario* sScenario;
  
  vector<double> fMassU5App;
  vector<double> fMassU8App;
  
  vector<double> fMassU5Nat;
  vector<double> fMassU8Nat;
  
  vector<double> fMassU5Waste;
  vector<double> fMassU8Waste;
};

#endif