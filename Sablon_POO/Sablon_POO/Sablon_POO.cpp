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
	const int id;
	static int contor; //static arata un comportament al clasei;o sa initializez id-ului studentului cu ajutorul acestui contor
	string nume; //<=>char*
	char dataNastere[11]; // 12.12.2012
	char gen; //M sau F
	float bursa;
	int nrNote;
	int* note;
	bool prezente[5];  //Luni-Vineri

public:
	//orice functie membra in clasa primeste implicit THIS (pointer care retine adresa obiectului pt care s-a apelat); eu nu il mai scriu, e pierdere de timp ;)
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
		if (num.length()) {//daca exista num atunci initializez campul
			nume = num;
		}
		strcpy(dataNastere, data);

		//exemplu de validare pentru gen: daca este F sau M
		if (g == 'f' || g == 'm') {
			gen = g;
		}

		//exemplu de validare pentru float bursa (sa fie mai mare decat zero)
		if (burs) {
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
}
