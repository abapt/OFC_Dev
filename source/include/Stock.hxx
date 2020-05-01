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
  Stock();
  Stock(double fMassUNat,
        double fMineU5UContent); //Constructeur
  ~Stock(); //Destructeur
  
  void SetName(std::string Name) {
    fName = Name;
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

private :

  string fName;
  double fMassUNat;
  double fMineU5UContent;
  
  vector<double> fMassU5App;
  vector<double> fMassU8App;
  
  vector<double> fMassU5Nat;
  vector<double> fMassU8Nat;
  
  vector<double> fMassU5Waste;
  vector<double> fMassU8Waste;
};

#endif