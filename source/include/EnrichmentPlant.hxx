#ifndef _EnrichmentPlant_
#define _EnrichmentPlant_

#include<vector>
#include <string>

using namespace std;

class Stock;

class EnrichmentPlant {
public :
	EnrichmentPlant(double WasteU5Content,
	                int fScenarioTime); //Constructeur simple
	~EnrichmentPlant(); //Destructeur
	
	void SetName(string Name) {
		fName = Name;
	}
	string GetName() {
		return fName;
	}
	
	void SetStock(Stock* feedstock, Stock* productstock, Stock* wastestock);

	void SetFeedStock(Stock* feedstock) {fFeedStock = feedstock;}
	void SetProductStock(Stock* productstock) {fProductStock = productstock;}
	void SetWasteStock(Stock* wastestock) {fWasteStock = wastestock;}
	
	Stock* GetFeedStock() {return fFeedStock;}
	Stock* GetProductStock() {return fProductStock;}
	Stock* GetWasteStock() {return fWasteStock;}
	
	// Main function for enrichment
	// Step 1 : TakeFeedMassForFuel
	// Step 2 : progressive Enrichment process and Push waste
	void FuelEnrichment(int time, double ReactorMass, double U5ContentInUProduct);
	// Take the required mass in Feed stock
	void TakeFeedMassForFuel(int time, double ReactorMass, double U5ContentInUProduct);
	// Take the required mass in Feed stock
	void FuelEnrichmentProcess(int time, double ReactorMass, double U5ContentInUProduct);
	
	void RemoveMassU5(int time, double mass);
	void AddMassU5(int time, double mass);
	
	void RemoveMassU8(int time, double mass);
	void AddMassU8(int time, double mass);
	
	
private :
	string fName;
	
	Stock* fFeedStock; // Pointer to connected Stock for Feed
	Stock* fProductStock; // Pointer to connected Stock for Product
	Stock* fWasteStock; // Pointer to connected Stock for Feed
	
	vector<double> fMassU5; // Amount of U5
	vector<double> fMassU8; // Amount of U8
	
	int fEnrichmentTime;
	
	double fU5ContentInUWaste;
};

#endif