#include "pch.h"
#include <iostream>
#include<string>
#include<fstream> //pt fisier txt
//STL (ultimul exercitiu)
#include<vector>
#include<list>
#include<set>
#include<map>
using namespace std;
//CRT_SECURE_NO_WARNINGS!


//try-catch (PAS 1)
class ExceptieNume : public exception { // Creez o clasa ExceptieNume derivata din exception
public:
	string what() {  //metoda what arunca o exceptie daca lungimea numelui studentului este mai mica de 5
		string numeValid;
		cout << "da nume valid : ";
		cin >> numeValid;
		while (numeValid.length() <= 5) {
			cout << "da nume valid : ";
			cin >> numeValid;      //metoda lasa utilizatorul sa reintroduca un nume corect
		}
		return numeValid;
	}
};


//Exercitiu Virtualizare (PAS 1)
class Interfata {
public:
	virtual void afisareVirtuala() = 0;
};


//definire clasa
class Student:public Interfata  { //pt ex de virtualizare PAS(2.1)
	//private continut vizibil doar in clasa, ca sa vedem continutul variabilelor private avem nevoie de metode get/set;
			//private e default;
			//incapsularea presupune sa am date private
	//public continut vizibil peste tot
	//protected <=>public PENTRU CLASE MOSTENITE
protected:  //am schimbat din ptivate in protected pt MOSTENIRE
	//zona inaccesibila!
	const int id; //const: odata initializat nu se mai schimba
	static int contor; //static arata un comportament al clasei;o sa initializez id-ului studentului cu ajutorul acestui contor
	string nume; //<=>char*
	char dataNastere[11]; // 12.12.2012
	char gen; //M sau F
	float bursa;
	int nrNote;
	int* note;
	bool prezente[5];  //Luni-Vineri

public:
	//orice functie membra in clasa primeste implicit THIS (pointer care retine adresa obiectului pt care s-a apelat); 
	//eu nu il mai scriu, e pierdere de timp ;)
	//CONSTRUCTOR DEFAULT/ FARA PARAMETRI
	//apel in main: Student s;
	Student() :id(-1) {   //initializare atribut constant cu -1, in acest constructor nu folosesc Staticul
		//initializez fiecare valoare din clasa cu o valoare default
		//initializare string
		nume = "Anonim";
		//initializare vector static de char
		strcpy(dataNastere, "00.00.0000");
		//initializare caracter
		gen = 'n';
		//initializare valoare numerica
		bursa = 0;
		nrNote = 0;
		//initializare vector dinamic
		note = NULL;
		//initializare vector static
		for (int i = 0; i < 5; i++) {
			prezente[i] = false; //0 ; implicit studentul este absent
		}
		cout << "S-a apelat constructorul default" << endl;


	}

	
	//CONSTRUCTOR CU TOTI PARAMETRII
	//apel in main: Student s1("Nume","12.12.2012",'M',...)
	//am folosit const char data pentru ca in main, in VS 2017 nu merge sa bagi un sir de caractere pur si simplu; daca se scoate const-ul apelul nu mai merge
	Student(int id,string num, const char data[11], char g, float burs, int nr, int* nt, bool prez[5]) :id(contor++) { //id-ul este initializat pe baza campului static
		//fiecare camp din clasa va fi initializat cu valoarea din apelul constructorului
		//exemplu de validare pe string, se poate folosi/ exclude
		if (num.length()>0) {//daca exista num atunci initializez campul
			nume = num;
		}
		strcpy(dataNastere, data);

		//exemplu de validare pentru gen: daca este F sau M
		if (g == 'f' || g == 'm') {
			gen = g;
		}

		//exemplu de validare pentru float bursa (sa fie mai mare decat zero)
		if (burs>0) {
			bursa = burs;
		}
		nrNote = nr;
		//exemplu de validare pentru vector dinamic
		if (nr) { //daca am elemente in vectorul de note
			note = new int[nr]; //aloc memorie pentru vector [nr/nrNote pt ca au ac valoare in acest moment]
			for (int i = 0; i < nr; i++) {
				note[i] = nt[i];
			}
		}

		cout << "S-a apelat constructorul cu parametri" << endl;
	}

	
	//CONSTRUCTOR CU NUMAR VARIABIL DE PARAMETRII (ex: nume, nr de note si notele)
	//Apel main: Student s2("Dorel,3,new int [3]{7,5,8})
	Student(string num, int nr, int* nt):id(contor++) {
		//toate campurile trebuie initializate (copy-paste de la construcotorul default pentru campurile care nu sunt in lista de parametrii a constr), altfel compilatorul va arunca din memorie valori 
		//nu mai folosesc validari, dar se pot folosi ;)
		nume = num;
		strcpy(dataNastere, "00.00.0000");
		gen = 'n';
		nrNote = nr;
		bursa = 0;
		note = new int[nr]; 
		for (int i = 0; i < nr; i++) {
			note[i] = nt[i];
		}
		for (int i = 0; i < 5; i++) {
			prezente[i] = false; 
		}
		cout << "S-a apelat constructorul cu 3 param"<<endl;
	}

	
	//CONSTRUCTOR DE COPIERE
	//Creez un obiect pe baza unui alt obiect DEJA EXISTENT
	//Apel main: Student s3(s2) sau Student s3=s2;
	Student(const Student& sursa):id(sursa.id) { //semnatura este mereu asa ; id-ul este preluat de la obiectul pe care il copiez
		//se pot folosi validarile din constructorul cu parametri si aici (in loc de atributele constructorului se va folosi "sursa."->ia din obiectul sursa si construieste obiectul copiat)
		nume = sursa.nume;
		strcpy(dataNastere, sursa.dataNastere);
		gen = sursa.gen;
		nrNote = sursa.nrNote;
		bursa = sursa.bursa;
		note = new int[sursa.nrNote];
		for (int i = 0; i < sursa.nrNote; i++) {
			note[i] = sursa.note[i];
		}
		for (int i = 0; i < 5; i++) {
			prezente[i] = sursa.prezente[i];
		}
		cout << "S-a apelat constructorul de copiere" << endl;
	}

	//OPERATOR =
	//Egalare intre obiecte il fac pe s1 ca pe s2
	//identic cu constructorul de copiere doar ca trebuie sa golesc campurile dinamice!
	//Apel s1=s2
	Student& operator=(const Student & sursa) {//semnatura este mereu la fel
		if (note) {
			delete[] note;
		}
		nume = sursa.nume;
		strcpy(dataNastere, sursa.dataNastere);
		gen = sursa.gen;
		nrNote = sursa.nrNote;
		bursa = sursa.bursa;
		note = new int[sursa.nrNote];
		for (int i = 0; i < sursa.nrNote; i++) {
			note[i] = sursa.note[i];
		}
		for (int i = 0; i < 5; i++) {
			prezente[i] = sursa.prezente[i];
		}
		return *this; //returnez obiectul cu noile valori
	}

	
	//FUNCTII ACCESOR/ METODE GET/SET (sunt functii membre => primesc THIS)
	string getNume() {
		return nume;
	}
	char* getDataNastere() {
		return dataNastere;
	}
	char getGen() {
		return gen;
	}
	float getBursa() {
		return bursa;
	}
	int* getNote() {
		return note;
	}
	int getNrNote() {
		return nrNote;
	}
	bool* getPrezente() {
		return prezente;
	}
	

	//try catch(PAS 2)
	void setNume(string numeNou) {
		if (numeNou.length() > 5) {
			nume = numeNou;
		}
		else {
			throw new ExceptieNume(); //alocam exceptii care sa ne impuna sa dam un nume valid de la tastatura
		}
	}
	void setDataNastere(const char dataNoua[11]) {
		if (strlen(dataNoua) == 10) {
			strcpy(dataNastere, dataNoua);
		}
	}
	void setGen(char genNou) {
		if (genNou == 'm' || genNou == 'f') {
			gen = genNou;
		}
	}
	void setBursa(float bursaNoua) {
		if (bursaNoua > 0) {
			bursa = bursaNoua;
		}
	}
	//numarul de note + notele se seteaza impreuna
	void setNote(int nrNou, int* noteNoi) {
		if (nrNou > 0) {
			nrNote = nrNou;
			if (note) {
				delete[] note; //sterg vechile note
			}
			note = new int[nrNou]; //aloc memorie
			for (int i = 0; i < nrNou; i++) {
				note[i] = noteNoi[i]; //creez noul vector de note
			}
		}
	}
	void setPrezente(bool prezNoi[5]) {
		for (int i = 0; i < 5; i++) {
			prezente[i] = prezNoi[i];
		}
	}
	
	//OPERATOR <<
	//tipul returnat: ostream& flux de date (string,float etc), punem & ca sa nu faca o copie pe care sa lucreze
	//parametrii: ostream& out - alt flux de date unde salvez, sursa - obiectul de unde copiez (poate lipsi & deoarece am constructor de copiere)
	//friend anuleaza this
	//Apel in main: cout<<s1
	friend ostream& operator<<(ostream& out, Student& sursa) {
		out << "Cod: " << sursa.id << endl;
		out << "Nume: " << sursa.nume << endl;
		out << "Data nastere: " << sursa.dataNastere << endl;
		if (sursa.gen == 'f') {
			out << "Gen: feminin" << endl;
		}
		else if(sursa.gen=='m'){
			out << "Gen: masculin" << endl;
		}
		else {
			out << "Gen: nedefinit"<<endl;
		}
		out << "Bursa: " << sursa.bursa << " ron" << endl;
		out << "Numar note: " << sursa.nrNote << endl;
		for (int i = 0; i < sursa.nrNote; i++) {
			out << "Nota " << i + 1 << " este " << sursa.note[i] << endl;
		}
		for (int i = 0; i < 5; i++) {
			if (sursa.prezente[i] == 0) {
				out << "Ziua " << i + 1 << ": Absent" << endl;
			}
			else {
				out << "Ziua " << i + 1 << ": Prezent" << endl;
			}
		}
		return out;
	}
	
	//OPERATOR >>
	//Apel in main: cin>>s1;
	//CITIRI STRING/CHAR CU SPATII: getline(in, VAR_STRING);/in.getline(VAR_CHAR, 20);
	friend istream& operator>>(istream& in, Student& sursa) {
		cout << "Introduceti nume: ";
		getline(in, sursa.nume);
		//in.getline(sursa.nume,50);

		cout << "Introduceti data nastere: ";
		in >> sursa.dataNastere;

		cout << "Introduceti gen: ";
		in >> sursa.gen;

		cout << "Introduceti bursa: ";
		in >> sursa.bursa;

		cout << "Introduceti nr de note: ";
		in >> sursa.nrNote;

		//in cazul in care exista note in vector, acestea se sterg
		if (sursa.note) {
			delete[] sursa.note;
		}
		sursa.note = new int[sursa.nrNote];
		for (int i = 0; i < sursa.nrNote; i++) {
			cout << "Introdu nota " << i + 1 << ": ";
			in >> sursa.note[i];
		}

		for (int i = 0; i < 5; i++) {
			cout << "Introdu prezenta: " << i + 1 << ": ";
			in >> sursa.prezente[i];
		}
		return in;
	}

	//exemple de functii pt examen
	//minimul din vector
	int notaMin() {
		int min = note[0];
		for (int i = 0; i < nrNote; i++) {
			if (note[i] < min) {
				min = note[i];
			}
		}
		return min;
	}
	//maximul din vector
	int notaMax() {
		int max = note[0];
		for (int i = 0; i < nrNote; i++) {
			if (note[i] > max) {
				max = note[i];
			}
		}
		return max;
	}
	//sortarea vectorului de note
	void sorteazaCrescator() {
		int aux;
		for (int i = 0; i < nrNote; i++) {
			for (int j = i + 1; j < nrNote; j++) {
				if (note[i] > note[j]) {
					aux = note[i];
					note[i] = note[j];
					note[j] = aux;
				}
			}
		}
	}
	void sorteazaDescrescator() {
		int aux;
		for (int i = 0; i < nrNote; i++) {
			for (int j = i + 1; j < nrNote; j++) {
				if (note[i] < note[j]) {
					aux = note[i];
					note[i] = note[j];
					note[j] = aux;
				}
			}
		}
	}
	//media din vectorul de note 
	float media() {
		float S = 0;
		for (int i = 0; i < nrNote; i++) {
			S += note[i];
		}
		return (float)S / nrNote;
	}

	//OPERATORI
	//Operatori BINARI: *, /, +, -
	//Pot sa adun doi studenti sau un student cu un numar
	//LUCREAZA CU O COPIE SI RETURNEAZA MEREU O COPIE
	
	//s1+ceva
	Student operator+(float b) {
		Student copie = *this;
		copie.bursa += b; //maresc valoarea bursei
		return copie;
	}

	//ceva+s1
	friend Student operator+(float b, Student& sursa) {
		Student copie = sursa;
		copie.bursa += b;
		return copie;
	}
	
	//Operatori unari: *=,+=,/=,-=
	//Fac aceleasi lucruri ca si cei binari doar ca lucreaza pe obiectul original
	//s1 += 50;
	Student operator+=(float b) {
		bursa = bursa + b;
		return *this;
	}

	//Operatori post incrementare
	//Aduna/scad, implicit nu au parametrii
	//Fac o copie apoi modifica obiectul original si returneaza copia
	//s1++;
	Student operator++(int) { //punem int ca sa faca compilatorul diferenta intre pre si post incrementare
		Student copie = *this;
		bursa += 100; //maresc bursa cu 100
		return copie;
	}

	//Operatori pre incrementare
	//Lucreaza cu obiectul original si returneaza obiectul original
	//++s1
	Student operator++() {
	    bursa += 100;
		return *this;
	}

	//CAST explicit
	//apel: tip variabila=(tip)s4
	explicit operator float() {
		return bursa;
	}

	//CAST implicit
	//apel: float bursa=s4
	/*
	operator float(){
	return bursa;
	}
	*/

	//operator functie () -- face orice vrei sa faca  
	//apel: s4(parametru_daca_exista)
	//pun o nota noua in vectorul de note
	void operator()(int nr) {
		if (nr >= 1 && nr <= 10) {
			int * vectorNou = new int[nrNote + 1];
			for (int i = 0; i < nrNote; i++) {
				vectorNou[i] = note[i];
			}
			vectorNou[nrNote] = nr;
			if (note) {
				delete[]note;
			}
			note = vectorNou;

			nrNote++;
		}
	}

	//operator index[]
	//Apel: s[1];
	int& operator[](int index) {
		if (index >= 0 && index < nrNote && note != NULL) {
			return note[index];
		}
		//else {
		//	//exceptie sau
		//	cout << "Index out of range!";
		//}
	}

	//Operatori de comparatie: <,>, <=,>=, ==, !=, !
	//Apel: if(s1<s2) => s1 mai mic else=> s2 mai mic
	bool operator<(Student & sursa) {
		float s = 0;
		for (int i = 0; i < nrNote; i++) {
			s += note[i];
		}
		s = s / nrNote;

		float s1 = 0;
		for (int i = 0; i < sursa.nrNote; i++) {
			s1 += sursa.note[i];
		}
		s1 = s1 / sursa.nrNote;
		if (s < s1) {
			return 1;
		}
		else {
			return 0;
		}
	}

	bool operator==(Student& sursa) {
		if (strcmp(dataNastere, sursa.dataNastere) == 0) {
			return true;
		}
		else {
			return false;
		}
	}


	//afisare in fisier txt
	//copiez continutul operatorului << si modific ostream => ofstream
	//#include<fstream>
	friend ofstream& operator<<(ofstream& out, Student& sursa) {
		out << "Cod: " << sursa.id << endl;
		out << "Nume: " << sursa.nume << endl;
		out << "Data nastere: " << sursa.dataNastere << endl;
		if (sursa.gen == 'f') {
			out << "Gen: feminin" << endl;
		}
		else if (sursa.gen == 'm') {
			out << "Gen: masculin" << endl;
		}
		else {
			out << "Gen: nedefinit" << endl;
		}
		out << "Bursa: " << sursa.bursa << " ron" << endl;
		out << "Numar note: " << sursa.nrNote << endl;
		for (int i = 0; i < sursa.nrNote; i++) {
			out << "Nota " << i + 1 << " este " << sursa.note[i] << endl;
		}
		for (int i = 0; i < 5; i++) {
			if (sursa.prezente[i] == 0) {
				out << "Ziua " << i + 1 << ": Absent" << endl;
			}
			else {
				out << "Ziua " << i + 1 << ": Prezent" << endl;
			}
		}
		return out;
	}
	

	//citire din fisier txt (trebuie sa existe in folderul proiectului)
	//copiez continutul operatorului >> si modific istream=> ifstream
	//#include<fstream>
	//ATENTIE: in fisier trebuie sa fie datele fara text aditional pe linii diferite
	//Fisierul:
	//Gigel
	//15.03.1998
	//M
	//780
	//4
	//10 
	//9 
	//8 
	//7
	//1
	//1 
	//1 
	//1 
	//1
	friend ifstream& operator>>(ifstream& in, Student& sursa) {
		getline(in, sursa.nume);
		in.getline(sursa.dataNastere, 11);
		in >> sursa.gen;
		in >> sursa.bursa;
		in >> sursa.nrNote;

		if (sursa.note) {
			delete[] sursa.note;
		}
		sursa.note = new int[sursa.nrNote];
		for (int i = 0; i < sursa.nrNote; i++) {
			in >> sursa.note[i];
		}

		for (int i = 0; i < 5; i++) {
			in >> sursa.prezente[i];
		}
		return in;
	}
	
	//scriere in fisier binar
	void scrieBinar(string numeFisier, Student* studenti, int nrStudenti) {
			ofstream scrie;
			scrie.open(numeFisier, ios::out | ios::binary);
			if (scrie.is_open()) {
				scrie.write((char*)&nrStudenti, sizeof(int)); //pe prima linie se pune neaparat nr de obiecte
				for (int i = 0; i < nrStudenti; i++) {
				
					//pun id-ul (int)
					scrie.write((char*)&id, sizeof(int));
					
					//pun numele (string)
					int dim = nume.length() + 1;
					scrie.write((char*)&dim, sizeof(int)); //pun cate caractere am
					scrie.write(nume.data(), dim * sizeof(char));
					
					//pun data nastere (vector static char)
					dim = strlen(dataNastere) + 1;
					scrie.write((char*)&dim, sizeof(int));
					scrie.write(dataNastere, dim * sizeof(char));

					//pun genul (un caracter) 
					scrie.write((char*)&gen, sizeof(char));

					//pun bursa (float)
					scrie.write((char*)&bursa, sizeof(float));

					//pun nr de note (int)
					scrie.write((char*)&nrNote, sizeof(int));
					
					//pun vectorul de note (int*)
					for (int i = 0; i < nrNote; i++) {
						scrie.write((char*)&note[i], sizeof(int));
					}

					//pun vectorul de prezente (vector static bool)
					for (int i = 0; i < 5; i++) {
						scrie.write((char*)&prezente[i], sizeof(bool));
					}
				}

				scrie.close();
			}
			else {
				cout << "Fisierul nu s-a putut deschide" << endl;
			}
		
		
	}
	//incarcare/citire din binar
	Student* citesteBinar(string numeFisier, int& nrStudenti) {
		if (numeFisier.length() > 0) {
			Student* studenti = NULL;
			ifstream citeste;
			citeste.open(numeFisier, ios::in | ios::binary);
			if (citeste.is_open()) {
				//pe prima linie este numarul de elemente pus in scrieBinar
				citeste.read((char*)&nrStudenti, sizeof(int));
				studenti = new Student[nrStudenti];
				for (int i = 0; i < nrStudenti; i++) {
					
					//citesc id (int)
					citeste.read((char*)&id, sizeof(int));
					
					//citesc nume(string)
					int dimNume;
					citeste.read((char*)&dimNume,sizeof(int));
					citeste.read((char*)&studenti[i].nume, sizeof(char)*dimNume);
					
					//citesc data nastere
					int dimDataNastere;
					citeste.read((char*)&dimDataNastere, sizeof(int));
					citeste.read((char*)&studenti[i].dataNastere, sizeof(char)*dimDataNastere);

					//citesc gen (char)
					citeste.read((char*)&gen, sizeof(char));
					
					//citesc bursa
					citeste.read((char*)&bursa, sizeof(float));
					
					//citesc nr note
					citeste.read((char*)&nrNote, sizeof(int));
					//citesc notele
					studenti[i].note = new int[nrNote];
					for (int j = 0; j < nrNote; j++) {
						citeste.read((char*)&studenti[i].note[j], sizeof(int));
					}
					//prezentele
					for (int j = 0; j < 5; j++) {
						citeste.read((char*)&studenti[i].prezente[j], sizeof(bool));
					}

					studenti[i] = Student(id,nume, dataNastere, gen, bursa, nrNote, note, prezente);

			
				}
				citeste.close();
			}
			else {
				cout << "Fisierul nu s-a putut deschide " << endl;
			}
			return studenti;
		}
	}
	//DESTRUCTOR
	//dezaloca acele campuri cu * pentru a evita MEMORY LEAKS
	~Student() {
		if (note) {
			delete[] note;
		}
		cout << "S-a apelat destructorul Student" << endl;
	}



	//Exercitiu Virtualizare (PAS 2.2)
	virtual void afisareVirtuala() {
		//afisez numele studentului+ notele
		cout << "Nume STUDENT: " << nume << " are " << nrNote << " note"<<endl;
		cout << "Notele:";
		for (int i = 0; i < nrNote; i++) {
			cout << note[i] << " ";
		}
		cout << endl;
	}
};
int Student::contor = 0; //ATRIBUTUL STATIC SE INITIALIZEAZA MEREU LA FINALUL CLASEI

//MOSTENIRE/DERIVARE/IS A
class StudentMaster : public Student {
	string master;
	int nrExamene;
	int* examene;
public:
	//Toate functiile constructor se apeleaza ascendent de la clasa de baza la clasa derivata
	//Apel main: StudentMaster sm;
	StudentMaster() :Student() {  //prima data se apeleaza constructorul default din clasa student, iar apoi constructorul fara param din clasa derivata
		master = "n/a";
		nrExamene = 0;
		examene = NULL;
		cout << "S-a apelat constructorul default din Student Master" << endl;
	}
	//Apel main: StudentMaster sm1(.......)
	StudentMaster(int id, string num, const char data[11], const char g, float burs, int nr, int* nt, bool prez[5], string mast, int nrE, int* exam) :Student(id,nume,data,g,burs,nr,nt,prez) {
		master = mast;
		nrExamene = nrE;
		examene = new int[nrE];
		for (int i = 0; i < nrE; i++) {
			examene[i] = exam[i];
		}
		cout << "S-a apelat constructorul cu param din Student Master" << endl;
	}
	//Apel main StudentMaster sm2(sm1)
	StudentMaster( const StudentMaster & sursa):Student(sursa) {  
		nume = sursa.nume;
		strcpy(dataNastere, sursa.dataNastere);
		gen = sursa.gen;
		nrNote = sursa.nrNote;
		bursa = sursa.bursa;
		note = new int[sursa.nrNote];
		for (int i = 0; i < sursa.nrNote; i++) {
			note[i] = sursa.note[i];
		}
		for (int i = 0; i < 5; i++) {
			prezente[i] = sursa.prezente[i];
		}
		master = sursa.master;
		nrExamene = sursa.nrExamene;
		examene = new int[sursa.nrExamene];
		for (int i = 0; i < sursa.nrExamene; i++) {
			examene[i] = sursa.examene[i];
		}
		cout << "S-a apelat constructorul de copiere din clasa Student Master" << endl;
	}
	//Apel: sm1=sm2
	StudentMaster& operator=(const StudentMaster & sursa) {
		if (note) {
			delete[] note;
		}
		if (examene) {
			delete[] examene;
		}
		nume = sursa.nume;
		strcpy(dataNastere, sursa.dataNastere);
		gen = sursa.gen;
		nrNote = sursa.nrNote;
		bursa = sursa.bursa;
		note = new int[sursa.nrNote];
		for (int i = 0; i < sursa.nrNote; i++) {
			note[i] = sursa.note[i];
		}
		for (int i = 0; i < 5; i++) {
			prezente[i] = sursa.prezente[i];
		}
		master = sursa.master;
		nrExamene = sursa.nrExamene;
		examene = new int[sursa.nrExamene];
		for (int i = 0; i < sursa.nrExamene; i++) {
			examene[i] = sursa.examene[i];
		}
		return *this; 
	}
	//Destructorul se apeleaza descendent de la clasa derivata la clasa de baza
	~StudentMaster() {
		if (examene) {
			delete[] examene;
		}
		cout << "Destructor clasa Student Master" << endl;
	}

	virtual void afisareVirtuala() { //Exercitiu virtualizare (PAS 3)
		//afisez numele studentului master + denumirea masterlui la care este
		cout << "Nume STUDENT MASTER: " << nume<<" este student la "<<master<<endl;
	}
};
int main()
{
	//apel constructor default
	Student s;

	//apel constructor cu toti parametrii
	int vectorNote[2] = { 7,8 };
	bool vectorPrez[5] = { 1,1,1,0,0 };
	Student s1(1,"Gigel", "10.10.2003", 'M', 345, 2, vectorNote, vectorPrez); ///"10.10.2003" apare cu eroare daca scot constul din constructor
	
    //apel constructor cu nr variabil de param
	Student s2("Dorel", 3, new int[3]{ 7,8,5 });
	
	//constructor de copiere
	Student s3(s2); //creez un obiect s3 care este de fapt copia lui s2
	
	//Operator =
	s1 = s2; //pe s1 il fac ca pe s2; s1 si s2 sunt obiecte deja existente!
	
	//Test accesor
	Student accesor;
	accesor.setNume("NumeSetat"); cout<<accesor.getNume()<<endl;
	accesor.setDataNastere("15.05.2001"); cout<<accesor.getDataNastere()<<endl;
	accesor.setGen('f'); cout << accesor.getGen() << endl;
	accesor.setNote(5, new int[5]{ 10,10,10,10,10 }); 
	cout << accesor.getNote() << endl; //ne da adresa la care este vectorul 
	//pt continut este nevoie de for
	for (int i = 0; i < accesor.getNrNote(); i++) {
		cout << "Nota " << i + 1 << " este: " << accesor.getNote()[i] << endl;
	}
	accesor.setBursa(1000); cout << accesor.getBursa();
	accesor.setPrezente(new bool[5]{ 1,1,0,1,1 });
	for (int i = 0; i < 5; i++) {
		cout << accesor.getPrezente()[i] << endl;
	}

	//apel operator <<
	Student s4(2,"Ionel", "10.10.2000", 'M', 500, 2, vectorNote, vectorPrez);
	cout << s4;

	//apel operator>>
	Student s5;
	//cin >> s5;
	//cout << s5;

	//APELURI FUNCTII
	int min = s4.notaMin(); cout << "Cea mai mica nota a studentului este: " << min << endl;
	int max = s4.notaMax(); cout << "Cea mai mare nota a studentului este: " << max<<endl;
	s4.sorteazaDescrescator();
	cout << s4.media();

	//Operatori
	s4 + 50;
	100 + s4;
	s4 += 30;
	s4++;
	++s4;
	float bursa = (float)s4;
	//float bursa=s4;
	s4(8);
	s4[3];
	if (s1 < s2) {
		cout << "Media lui s1 este mai mica decat media lui s2" << endl;
	}
	else {
		cout << "Media lui s2 este mai mica decat media lui s1" << endl;
	}
	if (s3 == s4) {
		cout << "Aceeasi data de nastere!"<<endl;
	}
	else {
		cout << "Diferite!"<<endl;
	}


	///afisare in fisier
	//ofstream obiectAfisare;
	//string numeFisier;
	//cout << "Introduceti numele fisierului de la tastatura:";
	//cin >> numeFisier; //fisier.txt
	//obiectAfisare.open(numeFisier, ios::out);
	//if (obiectAfisare.is_open()) {
	//	obiectAfisare << s4;
	//}
	//obiectAfisare.close();
	//fisierul apare in folderul proiectului


	//citire din fisier txt
	ifstream obiectCitire;
	//obiectCitire.open("fisierCreatDeMine.txt", ios::in);
	//cout << "Citire din fisier text " << endl;
	//if (obiectCitire.is_open()) {
	//	while (!obiectCitire.eof()) {
	//		Student student;
	//		obiectCitire >> student;
	//		cout << student;
	//	}
	//
	//}
	//obiectCitire.close();


	//Try catch(PAS 3)
	//try {
	//	s4.setNume("n/a"); //lungimea acestui nume <=5 deci va arunca exceptie
	//}
	//catch (ExceptieNume* e) {
	//	s1.setNume(e->what()); //pt pointerul e apelez functia din clasa ExceptieNume
	//}




	//problema pt char gen/ int id!!!

	//scriere/salvare in fisier binar
	Student* studenti = NULL;
	int nr=2;
	s4.scrieBinar("fisier.dat", studenti, nr);
	//in folderul proiectului apare "fisier.dat"

	//incarcare/citire din fisier binar
	nr = 1;
	Student* studenti2 = s4.citesteBinar("fisier.dat", nr);
	for (int i = 0; i < nr; i++) {
		cout << studenti2[i] << endl;
	}



	//DERIVARE MOSTENIRE APELURI
	//constructor default
	StudentMaster sm;
	//constructor cu param
	StudentMaster sm1(1, "Gabriel Popescu", "12.06.1996", 'M', 800, 2, new int[2]{ 6,8 }, new bool[5]{ 1,1,0,0,0 }, "IE", 5, new int[5]{ 1,2,3,1,2 });
	//constructor de copiere
	StudentMaster sm2(sm1);
	//operator egal
	sm = sm2;
	//pentru a vedea continutul functiilor de mai sus este necesara supraincarcarea operatorului << in clasa StudentMaster


	//Exercitiu Virtualizare (PAS 4)
	//s4.afisareVirtuala(); //afiseaza nume student +note
	//sm2.afisareVirtuala(); //afiseaza nume student + master






	///STL
	//Vector int
	vector<int> vect; //int* vect;
	vect.push_back(1);
	vect.push_back(2);
	vect.push_back(3); // vect[3] = {1,2,3}
	vect.pop_back(); //vect[2]={1,2}
	for (int i = 0; i < vect.size(); i++) {
		cout << vect[i] << endl;
	}

	//Vector obiecte
	vector<Student> vectStudenti;
	vectStudenti.push_back(s1);
	vectStudenti.push_back(s2);
	vectStudenti.push_back(s3);
	vectStudenti.push_back(s4);
	//vectStudenti.pop_back();
	for (int i = 0; i < vect.size(); i++) {
		cout << vect[i] << endl;
	}
	
	
	//List
	list<int> l;
	l.push_front(1);
	l.push_back(3);
	l.push_front(100);
	l.push_front(50);
	list<int>::iterator it;//int* it 
	cout << "Parcurgere lista" << endl;
	for (it = l.begin(); it != l.end(); it++) {
		cout << *it << endl;
	}
	l.sort();
	cout << "Parcurgere lista sortata crescator" << endl;
	for (it = l.begin(); it != l.end(); it++) {
		cout << *it << endl;
	}
	l.reverse();
	cout << "Parcurgere lista sortata descrescator" << endl;
	for (it = l.begin(); it != l.end(); it++) {
		cout << *it << endl;
	}

	list<Student> listaStudenti;
	listaStudenti.push_back(s1);
	listaStudenti.push_front(s2);
	listaStudenti.push_back(s1);
	listaStudenti.push_front(s3);
	listaStudenti.push_back(s4);


}
