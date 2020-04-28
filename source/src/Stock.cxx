#include "Stock.hxx"
#include "EnrichmentPlant.hxx"
#include "Scenario.hxx"

#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Stock::Stock(){
	SetName("Stock.");
}

Stock::Stock(double MassUNat,
			 double MineU5UContent)
{
	fMassUNat = MassUNat;
	fMineU5UContent = MineU5UContent;
	SetName("Stock.");
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Stock::~Stock() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void Stock::PrelevementEPUnat(int t) {
	fMassU5Nat.push_back(0);
	fMassU8Nat.push_back(0);

}
