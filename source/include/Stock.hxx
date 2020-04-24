#include<vector>
#include <string>

using namespace std;

class Stock
{
public :
	Stock(); //Constructeur simple
	~Stock(); //Destructeur

	void SetName(string Name){
		fName = Name;
	}

	/*void Evolution(int t);*/

private :

	string fName;

	vector<double> fMassU5Evolution;
	vector<double> fMassU8Evolution;
};