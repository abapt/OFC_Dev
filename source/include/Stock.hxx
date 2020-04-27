#include<vector>
#include <string>

using namespace std;

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

	/*void Evolution(int t);*/

private :

	string fName;
	double fMassUNat;
	double fMineU5UContent;

	vector<double> fMassU5Evolution;
	vector<double> fMassU8Evolution;
};