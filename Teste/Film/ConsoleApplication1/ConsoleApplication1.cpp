#include <iostream>
//#include<string>
using namespace std;
class Film {
	string nume;
	int nr_cinematografe;
	float* incasari;

	const int id;
public:
	static int nr_filme;

	//Film(){...} nu am constructor default!
	
	//constructor cu un singur parametru (id-ul)
	Film(int idDeTrimis) :id(idDeTrimis) {
		nume = "Necunoscut";
		nr_cinematografe = 0;
		incasari = NULL;

		nr_filme++;
	}

	string getNume() {
		return nume;
	}

	int getNrCinematografe() {
		return nr_cinematografe;
	}

	//constructor cu toti param
	Film(int idDeTrimis, string num, float* incas, int nr):id(idDeTrimis) {
		nume = num;
		nr_cinematografe = nr;
		incasari = new float[nr];
		for (int i = 0;i < nr;i++) {
			incasari[i] = incas[i];
		}
		nr_filme++;
	}
	
	//Constructor de copiere
	Film(const Film& sursa):id(sursa.id) { //iau id-ul de la ob din care copiez
		nume = sursa.nume;
		nr_cinematografe = sursa.nr_cinematografe;
		incasari = new float[sursa.nr_cinematografe];
		for (int i = 0;i < sursa.nr_cinematografe;i++) {
			incasari[i] = sursa.incasari[i];
		}
		nr_filme++;
	}

	float incasareMinima() {
		float min = incasari[0];//primul element din vector
		for (int i = 0;i < nr_cinematografe;i++) {
			if (incasari[i] < min) {
				min = incasari[i];
			}
		}
		return min;
	}

	void setIncasari(float* incasariNoi, int nrNou) {
		if (nrNou > 0) {
			nr_cinematografe = nrNou;
		}
		if (incasari != NULL) {
			delete[] incasari;
		}
		incasari = new float[nrNou];
		for (int i = 0;i < nrNou;i++) {
			incasari[i] = incasariNoi[i];
		}
	}

	friend ostream& operator<<(ostream& out, Film& sursa) {
		out << "Filmul " << sursa.nume;
		out << ", cu id " << sursa.id;
		out << " a fost difuzat in " << sursa.nr_cinematografe << " cinematografe";
		out << " inregistrand veniturile: ";
		for (int i = 0;i < sursa.nr_cinematografe;i++) {
			out << sursa.incasari[i] << ", ";
		}
		return out;
	}
	
	
	//operator egal
	Film& operator=(const Film& sursa) {
		if (incasari != NULL) {
			delete[] incasari;
		}
		nume = sursa.nume;
		nr_cinematografe = sursa.nr_cinematografe;
		incasari = new float[sursa.nr_cinematografe];
		for (int i = 0;i < sursa.nr_cinematografe;i++) {
			incasari[i] = sursa.incasari[i];
		}
		return *this; //returneaza obiectul cu valorile modificate
	}
	//operator +
	//nota 7 
	Film operator+(float nr) {
		Film copie = *this;

		float* vn = new float[nr_cinematografe + 1];
		for (int i = 0;i < nr_cinematografe;i++) {
			vn[i] = incasari[i];
		}

		///vn[nr_cinematografe] = 0;

		if (copie.incasari != NULL) {
			delete[] copie.incasari;
		}
		copie.incasari = new float[copie.nr_cinematografe + 1];
		for (int i = 0;i < nr_cinematografe;i++) {
			copie.incasari[i] = vn[i];
		}

		copie.incasari[copie.nr_cinematografe] = nr;
		copie.nr_cinematografe++;
		return copie;
	} 

	//operator functie () 
	//nota 8
	float operator()() {
		float S = 0;
		for (int i = 0;i < nr_cinematografe;i++) {
			S += incasari[i];
		}
		return S;
	}
	
	//operator INDEX
	//nota 9
	//se foloseste doar pt vectori
	float& operator[](int index) {
		if (incasari != NULL && index >= 0 && index < nr_cinematografe) {
			return incasari[index];
		}
	}

	//operatori de comparatie
	//nota 10
	bool operator==(Film& sursa) {
		if (nume == sursa.nume) {
			return 1;
		}
		else {
			return 0;
		}
	}
	//destructor //nota 2!
	~Film() {
		if (incasari != NULL) {
			delete[] incasari;
		}
		nr_filme--;
	}
};
int Film::nr_filme = 0;
int main()
{
	cout << endl << "-------------------NOTA 3:------------" << endl;
	Film f2(100);
	cout << f2.getNume()<<endl;
	cout << f2.getNrCinematografe()<<endl;

	cout << endl << "-------------------NOTA 4:------------"<<endl;
	float incasari[2] = { 10.6,5.2 };
	Film f3(101, "Stapanul inelelor", incasari, 2);
	Film f4 = f3;  //adica vrea constructor de copiere!

	cout << endl << "-------------------NOTA 5:------------" << endl;
	cout << f4.incasareMinima() << endl;
	cout << f4<<endl;
	float incasari2[3] = { 11.6,7.8,20.6 };
	f3.setIncasari(incasari2, 3);
	cout << f3.incasareMinima() << endl;

	cout << endl << "-------------------NOTA 6:------------" << endl;
	//operator egal, apel in cascada le face pe toate ca pe f3!
	f2 = f4 = f3;
	cout << f4.incasareMinima() << endl;
	cout << f2.incasareMinima() << endl;

	cout << endl << "-------------------NOTA 7:------------" << endl;
	Film* pf5 = new Film(102, "Harry Potter", incasari, 2);
	Film f6 = (*pf5) + 2.8;
	cout << pf5->getNrCinematografe() << endl;
	cout << f6.getNrCinematografe() << endl; //afiseaza 2 nu 3 ???
	cout << f6.incasareMinima() << endl;

	cout << endl << "-------------------NOTA 8:------------" << endl;
	delete pf5;
	cout << "In aplicatie sunt in total: " << Film::nr_filme << " filme" << endl;
	cout << "Incasari totale: " << f2();

	cout << endl << "-------------------NOTA 9:------------" << endl;
	f2[0] = 1.3;
	cout << f2[0];

	cout << endl << "-------------------NOTA 10:------------" << endl;
	if (f2 == f3) {
		cout << "Filmele au acelasi nume!" << endl;
	}
	else {
		cout << "Filmele au nume diferite!" << endl;
	}
}

