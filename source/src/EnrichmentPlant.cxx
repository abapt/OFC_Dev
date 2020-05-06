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

  	SetName("EnrichmentPlant.");


	fScenarioTime = ScenarioTime;

  	for(int t=0; t<fScenarioTime; t++) {
    	fMassU5Waste.push_back(0);
    	fMassU8Waste.push_back(0);

    	fMassU5Product.push_back(0);
    	fMassU8Product.push_back(0);

    	fMassU5Feed.push_back(0);
    	fMassU8Feed.push_back(0);
  	}
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::~EnrichmentPlant() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void EnrichmentPlant::AddFeedStock(FeedStock* stock) {
  fFeedStock.push_back(stock);
}

void EnrichmentPlant::AddWasteStock(WasteStock* stock) {
  fWasteStock.push_back(stock);
}


void EnrichmentPlant::CalculateNeededMasses() {
fRendement = (fU5ContentInUFeed - fU5ContentInUWaste) / 
  			     (fU5ContentInUProduct - fU5ContentInUWaste);

	fNeededUenrMassesByReactorLoading = 100000;
	fNeededUnatMassesByReactorLoading = fNeededUenrMassesByReactorLoading/ 
										fRendement;
	fNeededUappMassesByReactorLoading = fNeededUnatMassesByReactorLoading-
                                        fNeededUenrMassesByReactorLoading;
}

void EnrichmentPlant::FuelNatLoad(int t) {
		CalculateNeededMasses();

		vector<double> fMassU5FeedMine = fFeedStock->GetMassU5Feed();
		vector<double> fMassU8FeedMine = fFeedStock->GetMassU8Feed();

		fMassU5Feed[t-17532] = fNeededUnatMassesByReactorLoading
							 *fU5ContentInUnat;
		fMassU8Feed[t-17532] = fNeededUnatMassesByReactorLoading
							 *(1-fU5ContentInUnat);
	
		fMassU5FeedMine[t-17532] -= fMassU5Feed[t-17532];
		fMassU8FeedMine[t-17532] -= fMassU8Feed[t-17532];
	
		fMassU5Product[t-17532] = 0;
		fMassU8Product[t-17532] = 0;
	
}

void EnrichmentPlant::FuelConversion(int t) {
	double U5ByLoad = fNeededUenrMassesByReactorLoading*
					fU5ContentInUenr;
	double U8ByLoad = fNeededUenrMassesByReactorLoading*
					(1-fU5ContentInUenr);

	for (int i=1; i<17531; i++) {
		fMassU5Feed[t-17532+i]=fMassU5Feed[t-17532+i-1]
							-(fMassU5Feed[t-17532]/17531);
		fMassU8Feed[t-17532+i]=fMassU8Feed[t-17532+i-1]
							-(fMassU8Feed[t-17532]/17531);
	
		fMassU5Product[t-17532+i]=fMassU5Product[t-17532+i-1]
							+(U5ByLoad/17531);
		fMassU8Product[t-17532+i]=fMassU8Product[t-17532+i-1]
							+(U8ByLoad/17531);
	}
	for (int j=0; j<=17532; j++) {
		fMassU5Waste[t-17532+j]=fMassU5Feed[t-j]
							 -fMassU5Product[t-17532+j];
		fMassU8Waste[t-17532+j]=fMassU8Feed[t-j]
							 -fMassU8Product[t-17532+j];
	}
	fMassU5Feed[t-1]=0;
	fMassU8Feed[t-1]=0;

	fMassU5Product[t-1] = U5ByLoad;
	fMassU8Product[t-1] = U8ByLoad;
}

void EnrichmentPlant::PushUWaste(int t) {

		vector<double> fMassU5WasteStock = fWasteStock->GetMassU5Waste();
		vector<double> fMassU8WasteStock = fWasteStock->GetMassU8Waste();

		fMassU5WasteStock[t] += fMassU5Waste[t];
		fMassU8WasteStock[t] += fMassU8Waste[t];

		fMassU5Waste[t] = 0;
		fMassU8Waste[t] = 0;
	
}
                                                                                                         