#include "EnrichmentPlant.hxx"
#include "Stock.hxx"
#include "Reactor.hxx"

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::EnrichmentPlant(double WasteU5Content) {
  fU5ContentInUapp = 0.003;
  fU5ContentInUnat = 0.0072;
  fU5ContentInUenr = WasteU5Content;
  SetName("EnrichmentPlant.");

  fRendement = (fU5ContentInUnat - fU5ContentInUapp) / 
  			   (fU5ContentInUenr - fU5ContentInUapp);
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::~EnrichmentPlant() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
double EnrichmentPlant::CalculateNeededMasses() {
	fNeededUenrMassesByReactorLoading = fReactor->GetMassHN();
	fNeededUnatMassesByReactorLoading = fNeededUenrMassesByReactorLoading/ 
										fRendement;
	fNeededUappMassesByReactorLoading = fNeededUnatMassesByReactorLoading-
                                        fNeededUenrMassesByReactorLoading;
}

void EnrichmentPlant::FuelNatLoad(int t) {
	vector<double> fMassU5NatMine = fStock->GetMassU5Nat();
	vector<double> fMassU8NatMine = fStock->GetMassU8Nat();


	fMassU5Nat[t-2] = fNeededUnatMassesByReactorLoading*fU5ContentInUnat;
	fMassU8Nat[t-2] = fNeededUnatMassesByReactorLoading/(1-fU5ContentInUnat);
	fMassU5NatMine[t-2] -= fMassU5Nat[t-2];
	fMassU8NatMine[t-2] -= fMassU8Nat[t-2];
	fMassU5Enr[t-2] = 0;
	fMassU8Enr[t-2] = 0;
}

void EnrichmentPlant::FuelConversion(int t) {
	fMassU5Nat[t] = 0;
	fMassU8Nat[t] = 0;
	fMassU5Enr[t] = fNeededUenrMassesByReactorLoading*
					fU5ContentInUenr;
	fMassU8Enr[t] = fNeededUenrMassesByReactorLoading*
					(1-fU5ContentInUenr);
// -----------------------------------------
	fMassU5Nat[t-1] = fMassU5Nat[t-2] / 2;
	fMassU8Nat[t-1] = fMassU8Nat[t-2] / 2;
	fMassU5Enr[t-1] = fMassU5Enr[t] / 2;
	fMassU8Enr[t-1] = fMassU8Enr[t] / 2;
// -----------------------------------------
	fMassU5App[t] = fNeededUappMassesByReactorLoading*
					fU5ContentInUapp;
	fMassU8App[t] = fNeededUappMassesByReactorLoading*
					(1-fU5ContentInUapp);

	fMassU5App[t-1] = fMassU5App[t] / 2;
	fMassU8App[t-1] = fMassU8App[t] / 2;

	fMassU5App[t-2] = 0;
	fMassU8App[t-2] = 0;
}

void EnrichmentPlant::PushUApp(int t) {
	vector<double> fMassU5AppStock = fStock->GetMassU5App();
	vector<double> fMassU8AppStock = fStock->GetMassU8App();

	fMassU5AppStock[t] += fMassU5App[t];
	fMassU8AppStock[t] += fMassU8App[t];

	fMassU5App[t] = 0;
	fMassU8App[t] = 0;
}
                                                                                                         