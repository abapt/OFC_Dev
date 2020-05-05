#include "EnrichmentPlant.hxx"
#include "Stock.hxx"
#include "Reactor.hxx"
#include "Scenario.hxx"

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::EnrichmentPlant(double WasteU5Content,
								 int ScenarioTime) {
  	fU5ContentInUapp = 0.003;
  	fU5ContentInUnat = 0.0072;
  	fU5ContentInUenr = WasteU5Content;
  	SetName("EnrichmentPlant.");

  	fRendement = (fU5ContentInUnat - fU5ContentInUapp) / 
  			   (fU5ContentInUenr - fU5ContentInUapp);

	fScenarioTime = ScenarioTime;

  	for(int t=0; t<fScenarioTime; t++) {
    	fMassU5App.push_back(0);
    	fMassU8App.push_back(0);

    	fMassU5Enr.push_back(0);
    	fMassU8Enr.push_back(0);

    	fMassU5Nat.push_back(0);
    	fMassU8Nat.push_back(0);
  	}
  	cout << "EP U5 " << fMassU5Nat.size() << endl; 
    fMassU5App[0]=0;
    fMassU8App[0]=0;
    fMassU5Enr[0]=0;
    fMassU8Enr[0]=0;
    fMassU5Nat[0]=0;
    fMassU8Nat[0]=0;

}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::~EnrichmentPlant() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void EnrichmentPlant::CalculateNeededMasses() {
	fNeededUenrMassesByReactorLoading = fReactor->GetMassHN();
	fNeededUnatMassesByReactorLoading = fNeededUenrMassesByReactorLoading/ 
										fRendement;
	fNeededUappMassesByReactorLoading = fNeededUnatMassesByReactorLoading-
                                        fNeededUenrMassesByReactorLoading;
}

void EnrichmentPlant::FuelNatLoad(int t) {
	cout << "EP " << fMassU5Nat.size() << endl;
	//vector<double> fMassU5NatMine = fStock->GetMassU5Nat();
	//vector<double> fMassU8NatMine = fStock->GetMassU8Nat();

	//cout << "size Stock" << fMassU8NatMine.size() << endl;

	fMassU5Nat[t] = fNeededUnatMassesByReactorLoading*fU5ContentInUnat;
	fMassU8Nat[t] = fNeededUnatMassesByReactorLoading/(1-fU5ContentInUnat);
	//fStock->fMassU5Nat[t-2*8766] -= fMassU5Nat[t-2*8766];
	//Stock::fMassU8Nat[t-2*8766] -= fMassU8Nat[t-2*8766];
	//fMassU5Enr[t-2*8766] = 0;
	//fMassU8Enr[t-2*8766] = 0;
}

void EnrichmentPlant::FuelConversion(int t) {
	fMassU5Nat[t] = 0;
	fMassU8Nat[t] = 0;
	fMassU5Enr[t] = fNeededUenrMassesByReactorLoading*
					fU5ContentInUenr;
	fMassU8Enr[t] = fNeededUenrMassesByReactorLoading*
					(1-fU5ContentInUenr);
// -----------------------------------------
	fMassU5Nat[t-8766] = fMassU5Nat[t-2*8766] / 2;
	fMassU8Nat[t-8766] = fMassU8Nat[t-2*8766] / 2;
	fMassU5Enr[t-8766] = fMassU5Enr[t] / 2;
	fMassU8Enr[t-8766] = fMassU8Enr[t] / 2;
// -----------------------------------------
	fMassU5App[t] = fNeededUappMassesByReactorLoading*
					fU5ContentInUapp;
	fMassU8App[t] = fNeededUappMassesByReactorLoading*
					(1-fU5ContentInUapp);

	fMassU5App[t-8766] = fMassU5App[t] / 2;
	fMassU8App[t-8766] = fMassU8App[t] / 2;

	fMassU5App[t-2*8766] = 0;
	fMassU8App[t-2*8766] = 0;
}

void EnrichmentPlant::PushUApp(int t) {
	vector<double> fMassU5AppStock = fStock->GetMassU5App();
	vector<double> fMassU8AppStock = fStock->GetMassU8App();

	fMassU5AppStock[t] += fMassU5App[t];
	fMassU8AppStock[t] += fMassU8App[t];

	fMassU5App[t] = 0;
	fMassU8App[t] = 0;
}
                                                                                                         