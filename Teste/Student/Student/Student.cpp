#include <iostream>
using namespace std;
//Nota 1
class Student {
	const int codStud;
	int nrNote;
	int* note;
	
public:
	static int nrPctCredit;

	Student(int cod):codStud(cod) {
		nrNote = 0;
		note = NULL;
	}
	Student(int cod, int* no, int nr):codStud(cod) {
		nrNote = nr;
		note = new int[nr];
		for (int i = 0;i < nr;i++) {
			note[i] = no[i];
			if (note[i] >= 5) {
				nrPctCredit++;
			}
		}
	}
	Student(const Student& sursa) :codStud(sursa.codStud) {
		nrNote = sursa.nrNote;
		note = new int[sursa.nrNote];
		for (int i = 0;i < sursa.nrNote;i++) {
			note[i] = sursa.note[i];
			if (note[i] >= 5) {
				nrPctCredit++;
			}
		}
	}
	int getNrNote() {
		return nrNote;
	}
	int getCod() {
		return codStud;
	}
	void setNote(int* noteNoi, int nrNou) {
		if (nrNou > 0) {
			nrNote = nrNou;
		}
		if (note != NULL) {
			delete[] note;
		}
		note = new int[nrNou];
		for (int i = 0;i < nrNou;i++) {
			note[i] = noteNoi[i];
		}
	}
	Student& operator=(const Student& sursa) {
		if (note != NULL) {
			delete[] note;
		}
		nrNote = sursa.nrNote;
		note = new int[sursa.nrNote];
		for (int i = 0;i < sursa.nrNote;i++) {
			note[i] = sursa.note[i];
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Student& sursa) {
		out << "Studentul cu codul " << sursa.codStud << " are " << sursa.nrNote << " note:";
		for (int i = 0; i < sursa.nrNote; i++) {
			out << sursa.note[i] << ' ';
		}
		return out;
	}
	explicit operator float() {
		float S = 0;
		for (int i = 0;i < nrNote;i++) {
			S += note[i];
		}
		return S / nrNote;
	}
	Student operator++(int) {
		//dubleaza ultima nota
		Student copie = *this;
		int* vn = new int[nrNote + 1];
		for (int i = 0;i < nrNote;i++) {
			vn[i] = note[i];
		}
		
		vn[nrNote] = note[nrNote - 1]; 

		if (note != NULL) {
			delete[] note;
		}

		nrNote++;
		note = new int[nrNote];
		for (int i = 0;i < nrNote;i++) {
			note[i] = vn[i];
		}
		
		return copie;
	}
	bool estePromovat(int nrMinPct) {
		if (nrPctCredit >= nrMinPct) {
			return 1;
		}
		else {
			return 0;
		}
	}
	bool operator==(Student& sursa) {
		int nr1=0;
		int nr2=0;
		for (int i = 0;i < nrNote;i++) {
			if (note[i] >= 5) {
				nr1++;
			}
		}
		for (int i = 0;i < sursa.nrNote;i++) {
			if (sursa.note[i] >= 5) {
				nr2++;
			}
		}
		if (nr1 == nr2) {
			return true;
		}
		else {
			return false;
		}
	}
	//Nota 2
	~Student() {
		if (note != NULL) {
			delete[] note;
		}
	}
};
int Student::nrPctCredit = 3;
int main()
{
	//Nota 3
	Student s1(102);
	cout << s1.getNrNote();
	int note[] {10, 7, 8, 10, 4};
	Student s2(104, note, 5);
	

	//Nota 4
	cout << endl << "---------------------------"<<endl;
	Student s3 = s2;
	cout << "\n" << s3.getCod();

	//Nota 5
	cout << endl << "---------------------------" << endl;
	int note2[]{ 5,5,4,10 };
	s1.setNote(note2, 4);
	cout << "\n" << s1.getNrNote();

	//Nota 6
	cout << endl << "---------------------------" << endl;
	Student::nrPctCredit = 4;
	s3 = s1;
	bool promovat = s3.estePromovat(15);
	if (promovat) {
		cout << "\nStudentul s3 are un numar suficient de puncte credit ";
	}
	else {
		cout << "\nStudentul s3 nu are un numar suficient de puncte credit";
	}

	//Nota 7
	cout << endl << "---------------------------" << endl;
	Student* ps1 = new Student(109);
	*ps1 = s1;
	cout << *ps1;

	//Nota 8
	cout << endl << "---------------------------" << endl;
	delete ps1;
	float medie = (float)s1;
	cout << "\n" << medie;


	//Nota 9
	cout << endl << "---------------------------" << endl;
	s1 = s3++;
	cout << s1;
	cout << s3;

	//Nota 10
	cout << endl << "---------------------------" << endl;
	if (s1 == s3) {
		cout << "\ns4 are acelasi numar de note de trecere cu s3";
	}
	else {
		cout << "\ns4 nu are acelasi numar de note de trecere cu s3";
	}
}


