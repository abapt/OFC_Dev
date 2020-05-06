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
  	Stock(double fMassUWaste,
  		  int fScenarioTime);
  	Stock(double fMassUFeed,
          double fMineU5UContent,
          int fScenarioTime); //Constructeur
  	~Stock(); //Destructeur
  
  	void SetName(std::string Name) {
    	fName = Name;
  	}
  	string GetName(){
  		return fName;
  	}
  
  	vector<double> GetMassU5Spent() { 
    	return fMassU5Spent; // Waste U5 stock (after reactor)
  	}
  	vector<double> GetMassU8Spent() {
    	return fMassU8Spent; // Waste U8 stock (after reactor)
  	}
  	vector<double> GetMassU5Waste() {
    	return fMassU5Waste; // App U5 stock (after EP)
  	}
  	vector<double> GetMassU8Waste() {
    	return fMassU8Waste; // App U8 stock (after EP)
  	}
  	vector<double> GetMassU5Feed() {
    	return fMassU5Feed; // U5 stock (mine)
  	}
  	vector<double> GetMassU8Feed() {
    	return fMassU8Feed; // U8 stock (mine)
  	}

  	double GetMassU5SpentStock(int t){
		return fMassU5Spent[t];
	}
	double GetMassU8SpentStock(int t){
		return fMassU8Spent[t];
	}
	double GetMassU5WasteStock(int t){
		return fMassU5Waste[t];
	}
	double GetMassU8WasteStock(int t){
		return fMassU8Waste[t];
	}
	double GetMassU5FeedStock(int t){
		return fMassU5Feed[t];
	}
	double GetMassU8FeedStock(int t){
		return fMassU8Feed[t];
	}


private :

  string fName;
  double fMassUFeed;
  double fMineU5UContent;
  int fScenarioTime;
  double fMassUWaste;
  double fMassUSpent;

  Scenario* sScenario;
  
  vector<double> fMassU5Spent;
  vector<double> fMassU8Spent;
  
  vector<double> fMassU5Feed;
  vector<double> fMassU8Feed;
  
  vector<double> fMassU5Waste;
  vector<double> fMassU8Waste;
};

#endif