#include <iostream>
#include "pila.h"
#include "dicT.h"
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

void f2(dicT<int>a){}
void f(dicT<int> a){
	f2(a);
} 

int main(){
	dicT<int> a;
	bool c= a.esVacio();
	assert(c==1);
	//////////////////////
	//git hub suck
	string x ="direccion";
	int* num=new int(4174);
	a.definir(x, *num);
	assert(a.definido(x) ==1);
	assert(a.obtener(x) ==4174);
	//////////////////////
	int* num2= new int(5093);
	string y="casa";
	a.definir(y, *num);
	int num3=4541;
	a.definir("superfragilisticoespiralidoso", num3);
	//////////////////////
	Conj<string> cla= a.claves();
	typename Conj<string>::Iterador it=cla.CrearIt();
	cout << "\n"<<endl;
	cout << "Los Hijos Del Diccionario A Son: "<<endl;
	while(it.HaySiguiente()){
		cout <<"   -"<<it.Siguiente()<< endl;
		it.Avanzar();
	}
	cout << "El Hijo mas chico es : " << a.Minimo()<<endl;
	cout << " y su significado es " << a.obtener(a.Minimo())<<endl;
	cout << "\nEl Hijo mas grande es: "<< a.Maximo()<< endl;
	cout << " y su significado es "<< a.obtener(a.Maximo())<< endl;
	
	cout << "\n"<<endl;
	f(a);
	dicT<int> b;
	b.definir(x, *num);
	b.definir(y, *num);
	b.definir("superfragilisticoespiralidoso", num3);

	Conj<string> claB= b.claves();
	typename Conj<string>::Iterador itB=claB.CrearIt();
	cout << "Los Hijos Del Diccionario B Son: "<<endl;
	while(itB.HaySiguiente()){
		cout <<"   -"<<itB.Siguiente()<< endl;
		itB.Avanzar();
	}
	cout << "El Hijo mas chico es : " << b.Minimo()<<endl;
	cout << " y su significado es " << b.obtener(b.Minimo())<<endl;
	cout << "\nEl Hijo mas grande es: "<< b.Maximo()<< endl;
	cout << " y su significado es "<< b.obtener(b.Maximo())<< endl;
	
	c = (a==b);
	cout <<"\nY la funcion de igualdad entre B y A devuelve:  ";

	devolverBool(c); 
	cout << "\n"<<endl;
	cout << "Prueba de Iterador"<< endl;
	typename dicT<int>::Iterador itera= b.CrearIt();
	cout << "Los Hijos Del Diccionario B segun el Iterador Son: "<<endl;
	while(itera.HaySiguiente()){
		cout <<"   -"<<itera.SiguienteClave()<< endl;
		itera.Avanzar();
	}
	itera=b.CrearIt();
	cout << "Y sus Significados son segun el Iterador: "<< endl;
	while(itera.HaySiguiente()){
		cout <<"   -"<<itera.SiguienteSignificado()<< endl;
		itera.Avanzar();
	}
	b.Vacio();

	delete(num);
	delete(num2);
	
	a.borrar(x);
	//TODO OK HASTA ACA, SIN PERDIDA DE MEMORIA :P
	return 0;
}
