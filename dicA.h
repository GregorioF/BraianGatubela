	#ifndef DICC_A
#define DICC_A

#include "pila.h"
#include "Conj.h"
#include <iostream>

using namespace aed2;
using namespace std;

template<typename K, typename T>
class dicA{
public:
	struct Nodo{
			Nodo(const K c, const T& s, Nodo* p)
			: significado(s), clave(c), padre(p), izq(NULL), der(NULL){}
			T significado;
			K clave;
			Nodo* padre;
			Nodo* izq;
			Nodo* der;
	};

	class Iterador;
	class const_Iterador;
	///////////////////////////
	dicA();  				//definida
	///////////////////////////
	dicA(const dicA<K,T> &otro);// 
	///////////////////////////
	~dicA();  				//definida
	///////////////////////////
	bool esVacio() const;  	//definida
	///////////////////////////
	void definir(const K clave, const T& elem);  //definida
	///////////////////////////
	bool definido(const K clave) const;  //definida
	///////////////////////////
	T& obtener(K clave);  //definida
	///////////////////////////
	void borrar(K clave);  //definida  
	///////////////////////////
	aed2::Conj<K> claves();  //definida
	///////////////////////////
	Iterador CrearIt();  
	///////////////////////////
	const_Iterador CrearIt2() const;
	///////////////////////////
	bool operator ==( const dicA<K,T> &otro) ;  //definida
	///////////////////////////
	K Minimo(); 		//definida
	///////////////////////////
	K Maximo(); 		//definida
	///////////////////////////
	





	class Iterador{
	public:
		Iterador();
        ///////////////////////////
		Iterador(const typename dicA<K,T>::Iterador& otra);
		///////////////////////////
		bool HaySiguiente();
		///////////////////////////
		K  SiguienteClave();
		///////////////////////////
		T& SiguienteSignificado();
		///////////////////////////
		void Avanzar();
	private:
		Iterador(dicA<K,T>* d, Nodo* raiz): dic(d){
			siguiente = raiz;
			apilarHijos(siguiente, camino);
		}
		friend typename dicA<K,T>::Iterador dicA<K,T>::CrearIt(); 

		Nodo* siguiente;
		pila<Nodo> camino;
		dicA<K,T>* dic;
		//AUXILAR QUE SE UTILIZA EN AVANZAR
		void apilarHijos(Nodo* n, pila<Nodo>& p){
		if(n->der!=NULL)p.apilar(*(n->der));
		if(n->izq!=NULL)p.apilar(*(n->izq));
		}
	};








	class const_Iterador{
	public:
		const_Iterador();
        ///////////////////////////
		const_Iterador(const typename dicA<K,T>::const_Iterador& otra);
		///////////////////////////
		bool HaySiguiente() const;
		///////////////////////////
		const K  SiguienteClave() const;
		///////////////////////////
		const T& SiguienteSignificado() const;
		///////////////////////////
		void Avanzar();
	private:
		const_Iterador(const dicA<K,T>* d, Nodo* raiz): dic(d){
			siguiente = raiz;
			apilarHijos(siguiente, camino);
		}
		friend typename dicA<K,T>::const_Iterador dicA<K,T>::CrearIt2() const; 

		Nodo* siguiente;
		pila<Nodo> camino;
		const dicA<K,T>* dic;
		//AUXILAR QUE SE UTILIZA EN AVANZAR
		void apilarHijos(Nodo* n, pila<Nodo>& p){
		if(n->der!=NULL)p.apilar(*(n->der));
		if(n->izq!=NULL)p.apilar(*(n->izq));
		}	

	};
private:
	
	Nodo* raiz;
	








	///////////////////////////////////////////////
	//FUNCIONES AUXILIARES
	///////////////////////////////////////////////
	void destruir(Nodo* n){
		if(n!=NULL){
			if(n->der!=NULL) destruir(n->der);
			if(n->izq!=NULL) destruir(n->izq);
			if(n!=NULL)delete(n);
		}
	}
	/////////////////////////////////////////////
	//Se utiliza en borrar, devuelve en actual el nodo con la clave c
	void dameNodo(Nodo*& actual, K c){
		while(actual->clave != c){
			if(c > actual->clave) actual = actual->der;
			else actual=actual->izq;
		}
	}
	/////////////////////////////////////////////
	// Se utiliza en borrar, devuelve si es hoja
	bool esHoja(Nodo* n){
		return( n->izq==NULL && n->der==NULL);
	}
	/////////////////////////////////////////////
	// Se utiliza en borrar
	bool tieneUnHijo(Nodo* n){
		bool res = (n->izq==NULL && n->der!=NULL);
		res= (res || (n->izq!=NULL && n->der ==NULL));
		return res;
	}
	/////////////////////////////////////////////
	// No se utiliza
	bool tieneDosHijos(Nodo* n){
		return (n->izq != NULL && n->der != NULL);
	}
	/////////////////////////////////////////////
	// pre: que tenga padre;
	//Se utiliza en borrar
	bool esHijoDer(Nodo* n){
		return (n->clave > n->padre->clave);
	}
	/////////////////////////////////////////////
	// Se utiliza en borrar, devuelve el nodo por el que voy a remplazar a n que quiero borrar.
	Nodo* predecesorInmediato(Nodo* n){
		Nodo* res=n->izq;
		while(res->der!=NULL){
			res=res->der;
		}
		return res;
	}
	/////////////////////////////////////////////
	// Se utiliza en borrar, es para acortar el codigo de borrar...
	void borrarRaiz(Nodo*& n){
		if(esHoja(n)) {
			delete(n);
			raiz=NULL;
		}
		else if(tieneUnHijo(n)){
			if(n->izq!=NULL)raiz=n->izq;
			else raiz=n->der;
			delete(n);
			raiz->padre=NULL;
		}
		else{
			Nodo* predecesor = predecesorInmediato(n);
			n->clave=predecesor->clave;
			n->significado=predecesor->significado;
			Nodo* padre=predecesor->padre;
			if(esHoja(predecesor)){
				if(esHijoDer(predecesor)) padre->der=NULL;
				else padre->izq=NULL;
				delete(predecesor);
			}
			else if(tieneUnHijo(predecesor)){
				if(esHijoDer(predecesor)){
					if(predecesor->der!=NULL){
						padre->der=predecesor->der;
						predecesor->der->padre= padre;	
					}
					else {
						padre->der = predecesor->izq;
						predecesor->izq->padre=padre;
					}
					delete(predecesor);
				}
				else{
					if(predecesor->der!=NULL){
						padre->izq=predecesor->der;

						predecesor->der->padre= padre;	
					}
					else {
						padre->izq = predecesor->izq;
						predecesor->izq->padre=padre;
					}
					delete(predecesor);

				}
			}
		}
	}
	/////////////////////////////////////////////
	// Se utiliza en Claves
	void apilarHijos(Nodo* n, pila<Nodo>& p){
		if(n->der!=NULL)p.apilar(*(n->der));
		if(n->izq!=NULL)p.apilar(*(n->izq));
	}
};
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
dicA<K,T>::dicA(): raiz(NULL)
{}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T> 
dicA<K,T>::dicA (const dicA<K,T>& otro){
	typename dicA<K,T>::const_Iterador it= otro.CrearIt2();
	while(it.HaySiguiente()){
		definir(it.SiguienteClave(), it.SiguienteSignificado());
		it.Avanzar();
	}
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
dicA<K,T>::~dicA(){
	destruir(raiz);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
bool dicA<K,T>::esVacio() const{
	return (raiz==NULL);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
void dicA<K,T>::definir(const K c, const T& elem){
	if(raiz==NULL)raiz=new Nodo(c, elem, NULL);  
	else{
		Nodo* actual =raiz;
		while(actual->clave != c){
			if(actual->clave < c){
				if(actual->der==NULL){
					actual->der=new Nodo(c, elem, actual);
				}
				actual=actual->der;	
			}
			else{
				if(actual->izq==NULL) actual->izq = new Nodo(c, elem, actual);
				actual=actual->izq;
			}
		}
	}
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
bool dicA<K, T>::definido(K c) const{
	Nodo* actual=raiz;
	while(actual!=NULL){
		if(actual->clave == c) return true;
		else if(actual->clave < c){
			actual=actual->der;
		}
		else{
			actual = actual->izq;
		}
	}
	return false;
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
T& dicA<K,T>::obtener(K c){
	Nodo* actual=raiz;
	while(actual->clave != c){
		if(actual->clave < c) actual=actual->der;
		else actual=actual->izq;
	}
	return actual->significado;
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
void dicA<K,T>::borrar(K c){
	Nodo* actual= raiz;
	dameNodo(actual, c);
	Nodo* padre = actual->padre;
	if(actual==raiz) borrarRaiz(actual);
	else if(esHoja(actual)){
		if(esHijoDer(actual)) padre->der=NULL;
		else padre->izq=NULL;
		delete(actual);
	}
	else if(tieneUnHijo(actual)){
		if(esHijoDer(actual)){
			if(actual->der!=NULL){
				padre->der=actual->der;
				actual->der->padre= padre;	
			}
			else {
				padre->der = actual->izq;
				actual->izq->padre=padre;
			}
			delete(actual);
		}
		else{
			if(actual->der!=NULL){
				padre->izq=actual->der;
				actual->der->padre= padre;	
			}
			else {
				padre->izq = actual->izq;
				actual->izq->padre=padre;
			}
			delete(actual);

		}
	}
	else{
		Nodo* predecesor = predecesorInmediato(actual);
		actual->clave=predecesor->clave;
		actual->significado=predecesor->significado;
		padre=predecesor->padre;
		if(esHoja(predecesor)){
			if(esHijoDer(predecesor)) padre->der=NULL;
			else padre->izq=NULL;
			delete(predecesor);
		}
		else if(tieneUnHijo(predecesor)){
			if(esHijoDer(predecesor)){
				if(predecesor->der!=NULL){
					padre->der=predecesor->der;
					predecesor->der->padre= padre;	
				}
				else {
					padre->der = predecesor->izq;
					predecesor->izq->padre=padre;
				}
				delete(predecesor);
			}
			else{
				if(predecesor->der!=NULL){
					padre->izq=predecesor->der;

					predecesor->der->padre= padre;	
				}
				else {
					padre->izq = predecesor->izq;
					predecesor->izq->padre=padre;
				}
				delete(predecesor);

			}
		}
	}
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
Conj<K> dicA<K,T>::claves(){
	Conj<K> res;
	pila<Nodo> p;
	Nodo* actual=raiz;
	if(actual!=NULL){
		apilarHijos(actual,p);
		res.AgregarRapido(actual->clave);
		while(!(p.EsVacia())){
			actual= &p.tope();
			p.desapilar();
			res.AgregarRapido(actual->clave);
			apilarHijos(actual, p);
		}
	}
	return res;
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
K dicA<K,T>::Minimo(){
	Nodo* actual=raiz;
	while(actual->izq!=NULL) actual=actual->izq;
	return (actual->clave);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
K dicA<K,T>::Maximo(){
	Nodo*actual = raiz;
	while(actual->der!=NULL)actual=actual->der;
	return (actual->clave);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
bool dicA<K,T>::operator==(const dicA<K,T>& otro){
	Conj<string> clavesOtro= otro.claves();
	typename Conj<string>::Iterador it = clavesOtro.CrearIt();
	while(it.HaySiguiente()){
		if(!definido(it.Siguiente())) return false;
		if(otro.obtener(it.Siguiente()) != obtener(it.Siguiente())) return false;
		it.Avanzar();
	}
	return true;
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
typename dicA<K,T>::Iterador dicA<K,T>::CrearIt(){
	return Iterador(this, raiz);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
typename dicA<K,T>::const_Iterador dicA<K,T>::CrearIt2() const{
	return const_Iterador(this, raiz);
}















//FUNCIONES ITERADOR DICA
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename K, typename T>
dicA<K,T>::Iterador::Iterador()
	: siguiente(NULL), dic(NULL)
{}
///////////////////////////////////////////////////////////
template<typename K, typename T>
dicA<K,T>::Iterador::Iterador(const dicA<K,T>::Iterador& otro){
	siguiente=otro.siguiente;
	camino=otro.camino;
	dic=otro.dic;
}
///////////////////////////////////////////////////////////
template<typename K, typename T>
bool dicA<K,T>::Iterador::HaySiguiente(){
	return siguiente!=NULL;
}
///////////////////////////////////////////////////////////
template<typename K, typename T>
K dicA<K,T>::Iterador::SiguienteClave(){
	return siguiente->clave;
}
///////////////////////////////////////////////////////////
template<typename K, typename T>
T& dicA<K,T>::Iterador::SiguienteSignificado(){
	return siguiente->significado;
}
///////////////////////////////////////////////////////////
template<typename K, typename T>
void dicA<K,T>::Iterador::Avanzar(){
	if(!(camino.EsVacia())){
		siguiente = &camino.tope();
		camino.desapilar();
		apilarHijos(siguiente, camino);
	}
	else siguiente=NULL;
}








/////////////////////////////////////
//FUNCIONES ITERADOR CONST
/////////////////////////////////////
template<typename K, typename T>
dicA<K,T>::const_Iterador::const_Iterador()
	: siguiente(NULL), dic(NULL)
{}
///////////////////////////////////////////////////////////
template<typename K, typename T>
dicA<K,T>::const_Iterador::const_Iterador(const dicA<K,T>::const_Iterador& otro){
	siguiente=otro.siguiente;
	camino=otro.camino;
	dic=otro.dic;
}
///////////////////////////////////////////////////////////
template<typename K, typename T>
bool dicA<K,T>::const_Iterador::HaySiguiente() const{
	return siguiente!=NULL;
}
///////////////////////////////////////////////////////////
template<typename K, typename T>
const K dicA<K,T>::const_Iterador::SiguienteClave() const{
	return siguiente->clave;
}
///////////////////////////////////////////////////////////
template<typename K, typename T>
const T& dicA<K,T>::const_Iterador::SiguienteSignificado() const{
	return siguiente->significado;
}
///////////////////////////////////////////////////////////
template<typename K, typename T>
void dicA<K,T>::const_Iterador::Avanzar() {
	if(!(camino.EsVacia())){
		siguiente = &camino.tope();
		camino.desapilar();
		apilarHijos(siguiente, camino);
	}
	else siguiente=NULL;
}


#endif