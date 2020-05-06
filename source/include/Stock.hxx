#ifndef _Stock_
#define _Stock_

#include<vector>
#include <string>

using namespace std;

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
  string GetName() {
    return fName;
  }
  
  vector<double> GetMassU5() {
    return fMassU5; // U5 in stock
  }
  vector<double> GetMassU8() {
    return fMassU8; // U8 in stock
  }
  
  double GetMassU5(int t) {
    return fMassU5[t];
  }
  double GetMassU8(int t) {
    return fMassU8[t];
  }

  void RemoveMassU5(int time, double mass);
  void AddMassU5(int time, double mass);

  void RemoveMassU8(int time, double mass);
  void AddMassU8(int time, double mass);

private :

  string fName;
  
  vector<double> fMassU5;
  vector<double> fMassU8;
  
};

#endif