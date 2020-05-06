#include "Stock.hxx"
#include "EnrichmentPlant.hxx"
#include "Scenario.hxx"

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ----------------------------------------------------------
Stock::Stock(int ScenarioTime) {

  for(int t = 0; t < ScenarioTime; t++) {
    fMassU5.push_back(0);
    fMassU8.push_back(0);
  }
  
  SetName("Stock.");
}
// ----------------------------------------------------------
Stock::Stock(double Mass,
             double U5Content,
             int ScenarioTime) {
             
  SetName("Stock.");
  
  for(int t = 0; t < ScenarioTime; t++) {
    fMassU5.push_back(0);
    fMassU8.push_back(0);
  }
  
  fMassU5[0] = Mass * U5Content;
  fMassU8[0] = Mass * (1 - U5Content);
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Stock::~Stock() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// ----------------------------------------------------------
void Stock::RemoveMassU5(int time, double mass) {

  if(fMassU5[time] - mass < 0) {
    cout << "ERROR in EnrichmentPlant::RemoveMassU5(t,m)" << endl;
    cout << "You try to remove the mass " << mass << endl;
    cout << "in the stock " << GetName() << endl;
    exit(1);
  }
  
  fMassU5[time] = fMassU5[time] - mass;
}
// ----------------------------------------------------------
void Stock::RemoveMassU8(int time, double mass) {

  if(fMassU8[time] - mass < 0) {
    cout << "ERROR in EnrichmentPlant::RemoveMassU8(t,m)" << endl;
    cout << "You try to remove the mass " << mass << endl;
    cout << "in the stock " << GetName() << endl;
    exit(1);
  }
  
  fMassU8[time] = fMassU8[time] - mass;
}
// ----------------------------------------------------------
void Stock::AddMassU5(int time, double mass) {
  fMassU5[time] = fMassU5[time] + mass;
}
// ----------------------------------------------------------
void Stock::AddMassU8(int time, double mass) {
  fMassU8[time] = fMassU8[time] + mass;
}




