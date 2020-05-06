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
  	fU5ContentInUapp = WasteU5Content;
  	fU5ContentInUnat = 0.0072;
  	fU5ContentInUenr = 0.034;	
  	//string nom = fReactor->GetName();
  	//cout << nom << endl;
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
  	CalculateNeededMasses();
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::~EnrichmentPlant() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void EnrichmentPlant::CalculateNeededMasses() {
	fNeededUenrMassesByReactorLoading = 100000;
	fNeededUnatMassesByReactorLoading = fNeededUenrMassesByReactorLoading/ 
										fRendement;
	fNeededUappMassesByReactorLoading = fNeededUnatMassesByReactorLoading-
                                        fNeededUenrMassesByReactorLoading;
}

void EnrichmentPlant::FuelNatLoad(int t) {
	string nom = fStock->GetName();
	cout << nom << " " << fU5ContentInUapp << " " << fU5ContentInUnat <<" " <<fU5ContentInUenr<< endl;

	cout << fNeededUnatMassesByReactorLoading<<endl;
	vector<double> fMassU5NatMine = fStock->GetMassU5Nat();
	vector<double> fMassU8NatMine = fStock->GetMassU8Nat();

	fMassU5Nat[t-17532] = fNeededUnatMassesByReactorLoading*fU5ContentInUnat;
	fMassU8Nat[t-17532] = fNeededUnatMassesByReactorLoading*(1-fU5ContentInUnat);
	
	fMassU5NatMine[t-17532] -= fMassU5Nat[t-17532];
	fMassU8NatMine[t-17532] -= fMassU8Nat[t-17532];
	
	fMassU5Enr[t-17532] = 0;
	fMassU8Enr[t-17532] = 0;
}

void EnrichmentPlant::FuelConversion(int t) {
	double U5Load = fNeededUenrMassesByReactorLoading*
					fU5ContentInUenr;
	double U8Load = fNeededUenrMassesByReactorLoading*
					(1-fU5ContentInUenr);

	for (int i=1; i<17532; i++) {
		fMassU5Nat[t-17532+i]=fMassU5Nat[t-17532+i-1]-(fMassU5Nat[t-17532]/17532);
		fMassU8Nat[t-17532+i]=fMassU8Nat[t-17532+i-1]-(fMassU8Nat[t-17532]/17532);
	
		fMassU5Enr[t-17532+i]=fMassU5Enr[t-17532+i-1]+ (U5Load/17532);
		fMassU8Enr[t-17532+i]=fMassU8Enr[t-17532+i-1]+ (U8Load/17532);
	}
	for (int j=0; j<=17532; j++) {
		fMassU5App[t-17532+j] = fMassU5Nat[t-j]-fMassU5Enr[t-17532+j];
		fMassU8App[t-17532+j] = fMassU8Nat[t-j]-fMassU8Enr[t-17532+j];
	}

	fMassU5Nat[t]=0;
	fMassU8Nat[t]=0;

	fMassU5Enr[t] = U5Load;
	fMassU8Enr[t] = U8Load;
}

void EnrichmentPlant::PushUApp(int t) {
	vector<double> fMassU5AppStock = fStock->GetMassU5App();
	vector<double> fMassU8AppStock = fStock->GetMassU8App();

	fMassU5AppStock[t] += fMassU5App[t];
	fMassU8AppStock[t] += fMassU8App[t];

	fMassU5App[t] = 0;
	fMassU8App[t] = 0;
}
                                                                                                         