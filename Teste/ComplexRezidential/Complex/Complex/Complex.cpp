#include <iostream>
using namespace std;
//Nota 1
class ComplexRezidential {
	const int codComplex;
	int nrAp;
	float* suprafeteAp;
	
	

public:
	static int pretMetruPatrat;

	ComplexRezidential(int cod):codComplex(){
		nrAp = 0;
		suprafeteAp = NULL;
	}
	ComplexRezidential(int cod, float* supraf, int nr) :codComplex(cod) {
		nrAp = nr;
		suprafeteAp = new float[nr];
		for (int i = 0;i < nr;i++) {
			suprafeteAp[i] = supraf[i];
		}
	}
	ComplexRezidential(const ComplexRezidential& sursa):codComplex(sursa.codComplex) {
		nrAp = sursa.nrAp;
		suprafeteAp = new float[sursa.nrAp];
		for (int i = 0;i < sursa.nrAp;i++) {
			suprafeteAp[i] = sursa.suprafeteAp[i];
		}
	}
	int getNrAp() {
		return nrAp;
	}
	int getCodComplex() {
		return codComplex;
	}
	void setSuprafeteAp(float* suprafNoi, int nrNou) {
		if (nrNou > 0) {
			nrAp = nrNou;
		}
		if (suprafeteAp != NULL) {
			delete[] suprafeteAp;
		}
		suprafeteAp = new float[nrNou];
		for (int i = 0;i < nrNou;i++) {
			suprafeteAp[i] = suprafNoi[i];
		}
	}
	ComplexRezidential& operator=(const ComplexRezidential& sursa) {
		if (suprafeteAp != NULL) {
			delete[] suprafeteAp;
		}
		nrAp = sursa.nrAp;
		suprafeteAp = new float[sursa.nrAp];
		for (int i = 0;i < sursa.nrAp;i++) {
			suprafeteAp[i] = sursa.suprafeteAp[i];
		}
		return *this;
	}
	float getSuprafataMedie() {
		float S = 0;
		for (int i = 0;i < nrAp;i++) {
			S += suprafeteAp[i];
		}
		return S / nrAp;
	}
	//ceva+obiect
	friend ComplexRezidential operator+(float ceva, ComplexRezidential& sursa) {
		ComplexRezidential copie = sursa;
		float* vn = new float[copie.nrAp + 1];
		for (int i = 0; i < copie.nrAp; i++) {
			vn[i] = copie.suprafeteAp[i];
		}
		vn[copie.nrAp] = 0;

		if (copie.suprafeteAp != NULL) {
			delete[] copie.suprafeteAp;
		}
		copie.nrAp = copie.nrAp + 1;
		copie.suprafeteAp = new float[copie.nrAp];
		for (int i = 0; i < copie.nrAp; i++) {
			copie.suprafeteAp[i] = vn[i];
		}

		copie.suprafeteAp[copie.nrAp - 1] += ceva;
		
		return copie;

	}
	ComplexRezidential operator--() {
		float* vn = new float[nrAp - 1];

		for (int i = 0;i < nrAp-1;i++) {
			vn[i] = suprafeteAp[i];
		}
	
		if (suprafeteAp != NULL) {
			delete[] suprafeteAp;
		}

		suprafeteAp = new float[nrAp - 1];
		for (int i = 0;i < nrAp-1;i++) {
			suprafeteAp[i]=vn[i];
		}
		nrAp--;
		return *this;
	}
	friend ostream& operator<<(ostream& out, ComplexRezidential& sursa) {
		out << "Complexul cu codul " << sursa.codComplex << " are " << sursa.nrAp << " apartamente: ";
		for (int i = 0; i < sursa.nrAp; i++) {
			out << sursa.suprafeteAp[i] << ' ';
		}
		return out;
	}
	float& operator[](int index) {
		if (suprafeteAp != NULL && index >= 0 && index < nrAp) {
			return suprafeteAp[index];
		}
	}
	bool operator<(ComplexRezidential& sursa) {
		float supraf1 = 0;
		float supraf2 = 0;
		for (int i = 0;i < nrAp;i++) {
			supraf1 += suprafeteAp[i];
		}
		for (int i = 0;i < sursa.nrAp;i++) {
			supraf2 += sursa.suprafeteAp[i];
		}
		if (supraf1 < supraf2) {
			return 1;
		}
		else {
			return 0;
		}
	}
	//Nota 2
	~ComplexRezidential() {
		if (suprafeteAp != NULL) {
			delete[] suprafeteAp;
		}
	}

};
int ComplexRezidential::pretMetruPatrat = 700;
int main()
{	//Nota 3
	
	ComplexRezidential cr1(12);
	cout << "\n" << cr1.getNrAp();
	float suprafeteAp[] = { 65.5,45.5,70.5,85 };
	ComplexRezidential cr2(13, suprafeteAp, 4);
	cout << "\n" << cr2.getCodComplex();

	//Nota 4
	cout <<endl<< "---------------------------" << endl;
	ComplexRezidential cr3 = cr2;
	cout << "\n" << cr3.getNrAp();

	//Nota 5
	cout << endl << "---------------------------" << endl;
	float suprafeteAp2[] = { 50,60.5,70,80.5,120 };
	cr3.setSuprafeteAp(suprafeteAp2, 5);
	cout << "\n" << cr3.getNrAp(); //afișează 5

	//Nota 6
	cout << endl << "---------------------------" << endl;
	cr1 = cr2;
	cout << "\n" << cr1.getSuprafataMedie();

	//Nota 7
	cout << endl << "---------------------------" << endl;
	ComplexRezidential* pcr = new ComplexRezidential(19, suprafeteAp2, 5);
	ComplexRezidential cr4 = 50 + *pcr;
	cout << cr4; 


	//Nota 8
	cout << endl << "---------------------------" << endl;
	delete pcr;
	ComplexRezidential cr5 = --cr4; 
	cout << cr5<<endl; 
	cout << cr4<<endl;

	//Nota 9
	cout << endl << "---------------------------" << endl;
	ComplexRezidential::pretMetruPatrat = 800;
	cout << "\n" << cr4[2] * ComplexRezidential::pretMetruPatrat; //afișează 56000 reprezentând prețul apartamentului cu suprafața de pe poziția 2


	//Nota 10
	cout << endl << "---------------------------" << endl;
	if (cr1 < cr2)
		cout << "\ncr1 are o suprafata totala mai mica ca cr2";
	else
		cout << "\ncr2 are o suprafata totala mai mica ca cr1";



}

