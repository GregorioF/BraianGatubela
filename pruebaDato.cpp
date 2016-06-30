#include <iostream>
#include "pila.h"

using namespace std;

int main(){
	pila<int> p;
	int a,b,c,d,e,f;
	//cout << a << b<< endl;
	p.apilar(a);
	p.apilar(b);
	p.apilar(c);
	p.apilar(d);
	p.apilar(e);
	p.apilar(f);
	while(!p.EsVacia()){
		cout << p.tope()<< endl;
		p.desapilar();
	}

	p.apilar(a);
	p.apilar(b);
	p.apilar(c);
	p.apilar(d);
	p.apilar(e);
	p.apilar(f);

	cout << "\nsegunda pila : "<<endl;
	pila<int> p2= p;
	cout << "\n" <<endl;
	while(!p2.EsVacia()){
		cout << p2.tope()<< endl;
		p2.desapilar();
	}


	return 0;
}