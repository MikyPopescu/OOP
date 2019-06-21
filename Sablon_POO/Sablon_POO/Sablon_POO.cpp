#include "pch.h"
#include <iostream>
#include<string>
using namespace std;
//CRT_SECURE_NO_WARNINGS!


//definire clasa
class Student {
	//private continut vizibil doar in clasa, ca sa vedem continutul variabilelor private avem nevoie de metode get/set;
			//private e default;
			//incapsularea presupune sa am date private
	//public continut vizibil peste tot
	//protected <=>public PENTRU CLASE MOSTENITE
private:
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
	Student(string num, const char data[11], char g, float burs, int nr, int* nt, bool prez[5]) :id(contor++) { //id-ul este initializat pe baza campului static
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
	
	void setNume(string numeNou) {
		if (numeNou.length() > 0) {
			nume = numeNou;
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
	
	
	
	
	//DESTRUCTOR
	//dezaloca acele campuri cu * pentru a evita MEMORY LEAKS
	~Student() {
		if (note) {
			delete[] note;
		}
	}
};
int Student::contor = 0; //ATRIBUTUL STATIC SE INITIALIZEAZA MEREU AICI
int main()
{
	//apel constructor default
	Student s;

	//apel constructor cu toti parametrii
	int vectorNote[2] = { 7,8 };
	bool vectorPrez[5] = { 1,1,1,0,0 };
	Student s1("Gigel", "10.10.2003", 'M', 345, 2, vectorNote, vectorPrez); ///"10.10.2003" apare cu eroare daca scot constul din constructor
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
}
