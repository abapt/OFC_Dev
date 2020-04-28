#include<vector>
#include <string>

using namespace std;


class EnrichmentPlant {
public :
	EnrichmentPlant(double WasteU5Content); //Constructeur simple
	~EnrichmentPlant(); //Destructeur
	
	void SetName(string Name) {
		fName = Name;
	}
	
	double GetUnatEachLoad() const {
		return fNeededUnatMassesByReactorLoading;
	}
	double GetUappEachLoad() const {
		return fNeededUappMassesByReactorLoading;
	}
	double GetUenrEachLoad() const {
		return fNeededUenrMassesByReactorLoading;
	}
	
	void CalculateRendement();
	
	void CalculateNeededMasses();
	
private :
	vector<double> fMassU5Evolution;
	vector<double> fMassU8Evolution;
	
	string fName;
	double fU5ContentInUapp;
	double fU5ContentInUenr;
	double fU5ContentInUnat;
	double fRendement;
	double fNeededUenrMassesByReactorLoading;
	double fNeededUappMassesByReactorLoading;
	double fNeededUnatMassesByReactorLoading;
};
