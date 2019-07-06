#include "pch.h"
#include <iostream>
#include<string>
#include<fstream>
using namespace std;
//ex 6
class Exceptie :public exception {
public:
	float getPretBun() {
		float pretBun = 0;
		cout << "Da un pret bun mai mare decat 0: ";
		cin >> pretBun;
		while (pretBun <= 0) {
			cout << "Da un pret bun mai mare decat 0: ";
			cin >> pretBun;
		}
		return pretBun;
	}

	string getNumeBun() {
		string numeValid;
		cout << "Da un nume cu o lungime mai mare decat 3: ";
		cin >> numeValid;
		while (numeValid.length() <= 3) {
			cout << "Da un nume cu o lungime mai mare decat 3: ";
			cin >> numeValid;
		}
		return numeValid;
	}

};
class Sala {
private:
	//ex 1
	const int id;
	static int nrSali;
	int nrLocuri;
	bool* ocupate;
	string piesa;
	float pretBilet;
public:
	//ex 2
	Sala() :id(nrSali++) {
		nrLocuri = 0;
		piesa = "n/a";
		pretBilet = 0;
		ocupate = NULL;
	}
	Sala(int nrL, bool* ocup, string p, float pret) :id(nrSali++) {
		nrLocuri = nrL;
		ocupate = new bool[nrL];
		for (int i = 0; i < nrL; i++) {
			ocupate[i] = ocup[i];
		}
		piesa = p;
		pretBilet = pret;
	}
	Sala(const Sala& sursa) :id(nrLocuri++) {
		nrLocuri = sursa.nrLocuri;
		ocupate = new bool[sursa.nrLocuri];
		for (int i = 0; i < sursa.nrLocuri; i++) {
			ocupate[i] = sursa.ocupate[i];
		}
		piesa = sursa.piesa;
		pretBilet = sursa.pretBilet;
	}
	~Sala() {
		if (ocupate) {
			delete[] ocupate;
		}
	}

	//ex3
	static int getNrSali() {
		return Sala::nrSali;
	}
	int getNrLocuri() {
		return nrLocuri;
	}
	bool* getOcupate() {
		return ocupate;
	}
	string getPiesa() {
		return piesa;
	}
	float getPretBilet() {
		return pretBilet;
	}

	void setLocuri(int nrNou, bool* ocupNou) {
		if (nrNou > 0) {
			nrLocuri = nrNou;
		}
		if (ocupate) {
			delete[] ocupate;
		}
		ocupate = new bool[nrNou];
		for (int i = 0; i < nrNou; i++) {
			ocupate[i] = ocupNou[i];
		}
	}

	void setPiesa(string piesaNoua) {
		if (piesa.length() > 3) {
			piesa = piesaNoua;
		}
		//ex 6
		else {
			throw new Exceptie();
		}
	}
	void setPret(float pretNou) {
		if (pretNou > 0) {
			pretBilet = pretNou;
		}
		//ex 6
		else {
			throw Exceptie();
		}
	}

	int nrLocOcupate() {
		int k = 0;
		for (int i = 0; i < nrLocuri; i++) {
			if (ocupate[i] == 1) {
				k++;
			}

		}
		return k;
	}
	float VenitTotal() {
		int k = 0;
		for (int i = 0; i < nrLocuri; i++) {
			if (ocupate[i] == 1) {
				k++;
			}

		}
		return k * pretBilet;
	}
	float ProcentOcupare() {
		return (getNrLocuri() / (float)nrLocuri) * 100;
	}

	//ex 4
	Sala& operator=(const Sala& sursa) {
		if (ocupate) {
			delete[] ocupate;
		}
		nrLocuri = sursa.nrLocuri;
		ocupate = new bool[sursa.nrLocuri];
		for (int i = 0; i < sursa.nrLocuri; i++) {
			ocupate[i] = sursa.ocupate[i];
		}
		piesa = sursa.piesa;
		pretBilet = sursa.pretBilet;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Sala& sursa) {
		out << "Piesa: " << sursa.piesa << endl;
		out << "Nr de locuri: " << sursa.nrLocuri << endl;
		out << "Pret bilet: " << sursa.pretBilet << endl;
		out << "Locurile sunt: ";
		for (int i = 0; i < sursa.nrLocuri; i++) {
			out << sursa.ocupate[i] << " ";
		}
		out << endl;
		return out;
	}
	bool operator==(Sala& sursa) {
		if (pretBilet == sursa.pretBilet) {
			return 1;
		}
		else {
			return 0;
		}
	}
	Sala operator++(int) {
		Sala copie = *this;
		pretBilet += 5;
		return copie;
	}

	//ex 5
	friend ofstream& operator<<(ofstream& out, Sala& sursa) {
		out << "Piesa: " << sursa.piesa << endl;
		out << "Nr de locuri: " << sursa.nrLocuri << endl;
		out << "Pret bilet: " << sursa.pretBilet << endl;
		out << "Locurile sunt: ";
		for (int i = 0; i < sursa.nrLocuri; i++) {
			out << sursa.ocupate[i] << " ";
		}
		out << endl;
		return out;
	}


};
int Sala::nrSali = 0;
int main()
{
	//Apeluri ex 2
	Sala s;
	bool vect[4] = { 1,0,0,1 };
	Sala s1(4, vect, "O scrisoare pierduta", 20);
	Sala s2(s1);

	//Apeluri ex 3
	//cout << s.getNrSali();
	s2.setPiesa("O noapte furtunoasa"); cout << s2.getPiesa() << endl;
	s2.setPret(35.5); cout << s2.getPretBilet() << endl;
	s2.setLocuri(3, new bool[3]{ 1,1,1 });
	for (int i = 0; i < s2.getNrLocuri(); i++) {
		cout << s2.getOcupate()[i] << " ";
	}
	cout << endl;
	cout << s2.nrLocOcupate() << endl;
	cout << s2.VenitTotal() << endl;
	cout << s2.ProcentOcupare() << endl;


	//Apeluri ex 4
	s = s2;
	cout << s;
	if (s == s2) {
		cout << "Piesele au acelasi pret" << endl;
	}
	else {
		cout << "Preturi diferite!" << endl;
	}
	s2++; //adauga 5 lei la pretul biletului

	//Apeluri ex 5
	/*ofstream fout;
	string numeFisier = "fisier.txt";
	Sala vectSala[3] = { s1,s2,s };
	fout.open(numeFisier, ios::out);
	if (fout.is_open()) {
		for (int i = 0; i < 3; i++) {
			if (vectSala[i].nrLocOcupate() > 0) {
				fout << vectSala[i];
			}
		}
	}
	fout.close();*/

	//Apeluri ex 6
	//try {
	//	s2.setPiesa("n");
	//}
	//catch (Exceptie* e) {
	//	s2.setPiesa(e->getNumeBun());
	//}

	//try {
	//	s1.setPret(0);
	//}
	//catch (Exceptie e) {
	//	s1.setPret(e.getPretBun());
	//}
}
