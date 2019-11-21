#include <iostream>
using namespace std;
class IntretinereApartament {
	const int id;
	static int nrApartamente;
	float costFix;
	int nrLuni;
	float* costVariabil;
public:
	IntretinereApartament():id(nrApartamente++) {
		costFix = 0;
		nrLuni = 0;
		costVariabil = NULL;
	}
	float getCostFix() {
		return costFix;
	}
	float* getCostVariabil() {
		return costVariabil;
	}
	void setCostFix(float costNou) {
		if (costNou > 0) {
			costFix = costNou;
		}
	}
	void setCostVariabil(int nrNou, float* costNou) {
		if (nrNou > 0) {
			nrLuni = nrNou;
		}
		if (costVariabil != NULL) {
			delete[] costVariabil;
		}
		costVariabil = new float[nrNou];
		for (int i = 0;i < nrNou;i++) {
			costVariabil[i] = costNou[i];
		}
	}

	IntretinereApartament(float cf, int nr, float* cost) :id(nrApartamente++) {
		costFix = cf;
		nrLuni = nr;
		costVariabil = new float[nr];
		for (int i = 0;i < nr;i++) {
			costVariabil[i] = cost[i];
		}
	}
	~IntretinereApartament() {
		if (costVariabil != NULL) {
			delete[] costVariabil;
		}
	}

	int lunaCostMaxim() {
		float max = costVariabil[0];
		int poz = 0;
		for (int i = 0;i < nrLuni;i++) {
			if (costVariabil[i] > max) {
				max = costVariabil[i];
			}
		}
		for (int i = 0;i < nrLuni;i++) {
			if (costVariabil[i] == max) {
				poz = i;
				i = nrLuni + 1;
			}
		}
		return poz;
	}

	IntretinereApartament(const IntretinereApartament& sursa):id(sursa.id) {
		costFix = sursa.costFix;
		nrLuni = sursa.nrLuni;
		costVariabil = new float[sursa.nrLuni];
		for (int i = 0;i < sursa.nrLuni;i++) {
			costVariabil[i] = sursa.costVariabil[i];
		}
	}

	IntretinereApartament& operator=(const IntretinereApartament& sursa) {
		if (costVariabil != NULL) {
			delete[] costVariabil;
		}
		costFix = sursa.costFix;
		nrLuni = sursa.nrLuni;
		costVariabil = new float[sursa.nrLuni];
		for (int i = 0;i < sursa.nrLuni;i++) {
			costVariabil[i] = sursa.costVariabil[i];
		}
		return *this;
	}

	explicit operator float() {
		float S = 0;
		for (int i = 0;i < nrLuni;i++) {
			S += costVariabil[i] + costFix;
		}
		return S / nrLuni;
	}

	friend ostream& operator<<(ostream& out, IntretinereApartament& sursa) {
	//	out << "Id apartament: " << sursa.id << endl;
		out << "Cost fix lunar: " << sursa.costFix << endl;
		out << "Nr luni inregistrate: " << sursa.nrLuni << endl;
		out << "Costuri variabile: " << endl;
		for (int i = 0;i < sursa.nrLuni;i++) {
			out << sursa.costVariabil[i] << " ";
		}
		return out;
	}
	friend istream& operator>>(istream& in, IntretinereApartament& sursa) {
		cout << "Introduceti costul fix: " << endl;
		in >> sursa.costFix;

		cout << "Introduceti nr de luni: " << endl;
		in >> sursa.nrLuni;
	
		if (sursa.costVariabil != NULL) {
			delete[] sursa.costVariabil;
		}
		sursa.costVariabil = new float[sursa.nrLuni];

		for (int i = 0;i < sursa.nrLuni;i++) {
			cout << "Introdu costul " << i + 1 << ": ";
			in >> sursa.costVariabil[i];
		}
		return in;
	}

	IntretinereApartament operator-=(float nr) {
		float* vectNou = new float[nrLuni - 1];
		for (int i = 0;i < nrLuni-1;i++) {
			vectNou[i] = costVariabil[i];
		}
		if (costVariabil != NULL) {
			delete[] costVariabil;
		}
		nrLuni--;
		costVariabil = new float[nrLuni];
		for (int i = 0;i < nrLuni;i++) {
			costVariabil[i] = vectNou[i];
		}
		return *this;
	}

	bool operator!=(IntretinereApartament& sursa) {
		if ((costFix != sursa.costFix) && (nrLuni != sursa.nrLuni)) {
			return 1;
		}
		else {
			return 0;
		}
	}
};
int IntretinereApartament::nrApartamente = 0;
int main()
{
	//Nota 2:
	IntretinereApartament ia;
	ia.setCostFix(500); cout << ia.getCostFix() << endl;
	ia.setCostVariabil(2, new float[2] {80, 100});
	for (int i = 0;i < 2;i++) {
		cout << ia.getCostVariabil()[i] << " ";
	}
	

	//Nota 3:
	IntretinereApartament ia1(250, 3, new float[3]{ 80.5,300, 120});
	

	//Nota 4: 
	cout << ia1.lunaCostMaxim() << endl;
	

	//Nota 5:
	IntretinereApartament ia2(ia1);

	//Nota 6:
	ia = ia2;
	
	//Nota 7:
	float costMediu = (float)ia2;
	cout << "Costul mediu: " <<costMediu<< endl;

	//Nota 8:
	IntretinereApartament ia3;
	cin >> ia3;
	cout << ia3;

	//Nota 9:
	ia2 -= 10;
	

	//Nota 10:
	cout << endl;
	if (ia2 != ia) {
		cout << "Cost fix si numar de luni diferite" << endl;
	}
	else {
		cout << "Acelasi numar de luni si acelasi cost fix" << endl;
	}
}
