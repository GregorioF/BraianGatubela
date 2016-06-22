#include <iostream>
#include "pila.h"
#include "dicA.h"
#include <cassert>
#include <string>
#include <sstream>

using namespace std;

struct Nodo{
	int entero;
};

void devolverBool(bool b){
	if(b) cout << "True"<< endl;
	else cout << "False"<< endl;
}


int main(){
	dicA<string, int> edades;
	int emia=20;
	int echaro=20;
	int elucia=20;
	edades.definir("gregorio", emia);	
	edades.definir("charo", echaro);
	edades.definir("turra", elucia); 
	edades.definir("brian", emia);
	edades.definir("dante", emia);
	assert(1==edades.definido("gregorio"));
	assert(1==edades.definido("charo"));
	assert(1==edades.definido("turra")); 
	assert(0==edades.definido("tuvieja")); // funciona defindio
	//edades.definir("brian", emia);
	//edades.definir("dante", emia);
	edades.borrar("gregorio");
	edades.borrar("brian");
	edades.borrar("charo");
	edades.borrar("dante");
	edades.borrar("turra");
	cout << "\nHago borrado: "<<endl;
	//funciona borrar bien

	cout << "Segun claves, las claves son : "<<endl;
	edades.definir("gregorio", emia);	
	edades.definir("charo", echaro);
	edades.definir("turra", elucia); 
	edades.definir("brian", emia);
	edades.definir("dante", emia);

	Conj<string> cla = edades.claves();
	typename Conj<string>::Iterador it= cla.CrearIt();
	while(it.HaySiguiente()){
		cout << it.Siguiente()<< endl;
		it.Avanzar();
	}

	cout << "\n y segun el iterador de diccioanrio son: "<<endl;
	typename dicA<string, int>::Iterador itDic = edades.CrearIt();
	while(itDic.HaySiguiente()){
		cout << itDic.SiguienteClave()<< endl;
		itDic.Avanzar();
	}

	cout << "\n y segun el iterador constante de diccioanrio son: "<<endl;

	typename dicA<string, int>::const_Iterador itDic_const= edades.CrearIt();
	while(itDic_const.HaySiguiente()){
		cout << itDic_const.SiguienteClave()<< endl;
		itDic_const.Avanzar();
	}	

	return 0;
}	
