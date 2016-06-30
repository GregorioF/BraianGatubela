#ifndef PILA_H
#define PILA_H

#include <iostream>

using namespace std;

template<typename T>
class pila
{
public:
	pila();
	~pila();
	pila(const pila<T>& otro);
	void apilar(T& elem);
	void desapilar();
	T& tope();
	int size();
	bool EsVacia()const;
	void vaciar();
	void operator =(const pila<T>& otra){
		Nodo* actual = otra.primero;
		while(actual!=NULL){
			apilar(*(actual->elem));
			actual=actual->siguiente;
		}
	}
	void Ultimo(){
		cout << *(ultimo->elem)<<endl;
	}
private:
	struct Nodo{
		Nodo(T& valor, Nodo* ant): elem(&valor), anterior(ant), siguiente(NULL) {}
		T* elem;
		Nodo* anterior;
		Nodo* siguiente;
	};
	int cantidad;
	Nodo* primero; //solo para copiar
	Nodo* ultimo;
};

template<typename T>
pila<T>::pila(): cantidad(0), ultimo(NULL){}

template<typename T>
pila<T>::pila(const pila<T>& otra){
	primero = NULL;
	ultimo =NULL;
	Nodo* actual = otra.primero;
	while(actual!=NULL){
		apilar(*(actual->elem));
		actual=actual->siguiente;
	}
	cantidad --;    //WHY?!!!!!!!!!!!!!!!!!!!?!?!??!??!?!?!!!!!!!!!!!!!!!!!!!
}

template<typename T>
pila<T>::~pila(){
	primero=NULL;
	Nodo* actual=ultimo;
	while(actual!=NULL){
		Nodo* aux=actual;
		actual= actual->anterior;
		delete(aux);
	}
}

template<typename T>
void pila<T>::apilar(T& elem){
	if(ultimo==NULL){
		ultimo= new Nodo(elem, NULL);
		primero =ultimo;
	}
	else{
		ultimo->siguiente=new Nodo(elem, ultimo);
		ultimo= ultimo ->siguiente;
	}
	cantidad++;	
}

template<typename T>
void pila<T>::desapilar(){
	cantidad --;
	if(cantidad==0){
		
		delete(ultimo);
		ultimo=NULL;
		primero=NULL;
		}
	else{
		ultimo=ultimo->anterior;
		delete(ultimo->siguiente);
		ultimo->siguiente= NULL;
	}
}

template<typename T>
T& pila<T>::tope(){
	return *(ultimo->elem);
}

template<typename T>
int pila<T>::size(){
	return cantidad;
}

template<typename T>
bool pila<T>::EsVacia()const{
	return (ultimo==NULL);
}
 
template<typename T>
void pila<T>::vaciar(){
	if(!EsVacia()){
		Nodo* actual=ultimo;
		while(actual!=NULL){
		Nodo* aux=actual;
		actual= actual->anterior;
		delete(aux);
		}
	}
	
}

#endif