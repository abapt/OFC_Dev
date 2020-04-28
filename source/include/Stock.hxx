#include<vector>
#include <string>

using namespace std;

class EnrichmentPlant;
class Scenario;

class Stock
{
public :
	Stock();
	Stock(double fMassUNat,
		  double fMineU5UContent); //Constructeur
	~Stock(); //Destructeur

	void SetName(string Name){
		fName = Name;
	}
	void PrelevementEPUnat(int t);

	vector<double> GetMassU5Waste() {
		return fMassU5Waste;
	}
	vector<double> GetMassU8Waste() {
		return fMassU8Waste;
	}
	vector<double> GetMassU5App() {
		return fMassU5App;
	}
	vector<double> GetMassU8App() {
		return fMassU8App;
	}
	vector<double> GetMassU5Nat() {
		return fMassU5Nat;
	}
	vector<double> GetMassU8Nat() {
		return fMassU8Nat;
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