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

void f(dicT <int> x){
	cout <<x.obtener("seis")<<endl;
} 

int main(){
	dicT<int> a;
	int cuatro= 4;
	int cinco = 5;
	int seis= 6;
	int siete=7;
	int ocho=8;
	a.definir("cuatro",cuatro);
	a.definir("cinco",cinco);
	a.definir("seis", seis);
	a.definir("siete", siete);
	a.definir("ocho", ocho);

	cout << a.obtener("seis")<<endl;
	f(a);

	return 0;
}
