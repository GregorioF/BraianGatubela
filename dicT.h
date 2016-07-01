#ifndef DICCT_H
#define DICCT_H

#include "pila.h"
#include "Conj.h"
#include <iostream>


using namespace aed2;
using namespace std;

template < typename T>
class dicT
{
public:
	class Iterador;
	class const_Iterador;
	///////////////////////////
	dicT();                 //definida
	///////////////////////////
	dicT(const dicT<T> &otro);  // falta definir
	///////////////////////////
	~dicT();                //definida
	///////////////////////////
	bool esVacio() const;   //definida
	///////////////////////////
	void definir(string clave, T& elem);  //definida
	///////////////////////////
	bool definido(string clave) const;  //definida
	///////////////////////////
	T& obtener(string clave) const;  //definida
	///////////////////////////
	void borrar(string clave);  //definida
	///////////////////////////
	aed2::Conj<string> claves() const;  //definida
	///////////////////////////
	Iterador CrearIt();  
	///////////////////////////
	const_Iterador CrearIt2();  
	///////////////////////////
	bool operator ==( dicT<T> &otro) ;  //definida
	///////////////////////////
	string Minimo();        //definida
	///////////////////////////
	string Maximo();        //definida
	///////////////////////////





	class Iterador{
	public:
		Iterador();
		///////////////////////////
		Iterador(const typename dicT<T>::Iterador& otra);
		///////////////////////////
		bool HaySiguiente() const;
		///////////////////////////
		string  SiguienteClave();
		///////////////////////////
		T& SiguienteSignificado();
		///////////////////////////
		void Avanzar();
	private:
		Iterador(dicT<T>* d): dic(d){
			claves= (*d).claves();
			typename Conj<string>::Iterador it = claves.CrearIt();
			siguiente=make_pair(it.Siguiente(), (*d).obtener(it.Siguiente()));
			it.EliminarSiguiente();
		}
		friend typename dicT<T>::Iterador dicT<T>::CrearIt();

		pair<string, T> siguiente;
		aed2::Conj<string> claves;
		dicT<T>* dic;
	};





	class const_Iterador{
	public:
		const_Iterador();
		///////////////////////////
		const_Iterador(const typename dicT<T>::const_Iterador& otra);
		///////////////////////////
		bool HaySiguiente() const;
		///////////////////////////
		const string  SiguienteClave() const;
		///////////////////////////
		const T& SiguienteSignificado() const;
		///////////////////////////
		void Avanzar();
	private:
		const_Iterador(dicT<T>* d): dic(d){
			claves= (*d).claves();
			typename Conj<string>::Iterador it = claves.CrearIt();
			siguiente=make_pair(it.Siguiente(), (*d).obtener(it.Siguiente()));
			it.EliminarSiguiente();
		}
		friend typename dicT<T>::const_Iterador dicT<T>::CrearIt2();

		pair<string, T> siguiente;
		aed2::Conj<string> claves;
		const dicT<T>* dic;

	};




private:
	struct Nodo{
		Nodo():  letra('a'), padre(NULL), esPalabra(false){
			ponerTodoEnNull(hijos);
		}
		Nodo(char c, Nodo* p) :  letra(c), padre(p) , esPalabra(false){
			ponerTodoEnNull(hijos);
		} 
		Nodo(char c, Nodo* p, T& elem ): significado(&elem), letra(c), padre(p), esPalabra(false){
			ponerTodoEnNull(hijos);
		} 
		T significado;
		bool esPalabra;
		char letra;
		Nodo* padre;
		Nodo* hijos [256];
		

		void ponerTodoEnNull(Nodo* hijos []){
			
			for(int i=0; i<256; i++) hijos[i]=NULL;
		}
	};

	Nodo* raiz;
	////////////////////////////////////////////////////////////////////////////////
	//FUNCIONES AUXILIARES PRIVADAS
	////////////////////////////////////////////////////////////////////////////////
	
	// Se utiliza en Claves()
	template <typename K>
	void apilarHijos(Nodo* actual, pila<K>& recoridos) const{
		for(int i=255;i>=0;i--){
			if(actual->hijos[i]!=NULL)recoridos.apilar(*actual->hijos[i]);
		}
	}
	////////////////////////////////////////////////////////////////////////////////
	//No se utiliza por ahora...
	Lista<Nodo*> hijos(Nodo* actual){
		Lista<Nodo*> res;
		int i=0;
		while(i<256){
			if(actual->hijos[i]!=NULL)res.AgregarAtras(actual->hijos[i]);
			i++;
		}
		return res;
	}
	////////////////////////////////////////////////////////////////////////////////
	//Se utiliza en borrar() y en Claves() devuelve true si no tiene hijos el nodo Actual
	bool EsVaciaHijos(Nodo* actual) const{

		int i=0;
		while(i<256){
			if(actual->hijos[i]!=NULL) return false;
			i++;
		}
		return true;}
	////////////////////////////////////////////////////////////////////////////////
	//se utiliza en claves(), en Minimo(), y en Maximo() devuelve si el puntero a significado es != Null
	bool esPalabraFunc(Nodo* actual) const{
		return actual->esPalabra;
	}
	////////////////////////////////////////////////////////////////////////////////
	//Se utiliza en Claves(), en Minimo(), y en Maximo() Devuelve la palabra que se forma hasta n
	string DameNombre(Nodo* n) const{
		Nodo* actual= n;
		string res;
		while(actual->padre!=NULL){
			string aux;
			aux.push_back(actual->letra);
			res.insert(0,aux);
			actual=actual->padre;
		}
		return res;
	}
	////////////////////////////////////////////////////////////////////////////////
	//Se utiliza en el destructor, desturye todos los nodos desde actual, asi abajo
	void destruir(Nodo* actual){
		if(actual!=NULL){
			for(int i=0; i<255;i++) destruir(actual->hijos[i]);
			delete(actual);
		}
	}
	////////////////////////////////////////////////////////////////////////////////
	//Se utiliza en  Minimo() devuelve si tiene un Hijo menor que  n
	bool tieneUnHijosMasChico(Nodo* n){
		int i=0;
		Nodo* actual=NULL;
		while(actual==NULL && i<256){
			actual=n->hijos[i];
			i++;
		}
		if(actual==NULL) return false;
		else if(actual->letra < n->letra)return true;
		else return false;
	}   
	////////////////////////////////////////////////////////////////////////////////
	// Se utiliza en Maximo()
	bool tieneUnHijosMasGrande(Nodo* n){
		int i=255;
		Nodo* actual=NULL;
		while(actual==NULL && i>=0){
			actual=n->hijos[i];
			i--;
		}
		if(actual==NULL) return false;
		else if(actual->letra < n->letra)return true;
		else return false;
	}   
};
///////////////////////////////////////////////////////////
//ALGORITMOS FUNCIONES INTERFAZ
///////////////////////////////////////////////////////////
template <typename T>
dicT<T>::dicT(){
	raiz= new Nodo();
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
dicT<T>::dicT(const dicT<T>& otro){
	raiz= NULL;
	raiz= new Nodo();
	Conj<string> claves = otro.claves();
	typename Conj<string>::const_Iterador it=claves.CrearIt();

	while(it.HaySiguiente()){
		T elem=T(otro.obtener(it.Siguiente())); //FIJARSE SI ES X COPIA O REFERENCIA !!
		//cout <<"\n\nHASTA ACA ALM ENOS LLEGAL A RE CONCHA DE TU REMIL PUTA MADRE \n\n\n\n";
	
		definir(it.Siguiente(), elem);
	
		it.Avanzar();
	}
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <typename T>
dicT<T>::~dicT(){
	destruir(raiz);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <typename T>
bool dicT<T>::esVacio()const {
	int i=0;
	while(i<256){
		if(raiz->hijos[i]!=NULL) return false;
		i++;
	}
	return true;
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
void dicT<T>::definir(string clave, T& elem){
	Nodo* actual = raiz;
	int i=0;
	int tamanio = clave.size();
	while(i<tamanio){
		if( actual->hijos[clave[i]] != NULL) actual= actual->hijos[clave[i]];
		else {
			actual->hijos[clave[i]] = new Nodo( clave[i], actual);
			actual= actual->hijos[clave[i]];
		}
		i++;
	}   
	actual->significado= elem;     /////HACER EL CONSTRUCTOR POR COPIA BIZZARO DE ANTES
	actual->esPalabra=true;
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <typename T>
bool dicT<T>::definido(string clave) const{
	Nodo* actual = raiz;
	int i=0;
	while(i<clave.size() && actual->hijos[clave[i]] != NULL){
		actual = actual->hijos[clave[i]];
		i++;
	}
	if(i==clave.size() && actual->esPalabra){
		return true;
	}
	else{return false;}
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
T& dicT<T>::obtener(string clave) const{
	Nodo* actual = raiz;
	int i=0;
	int tamanio = clave.size();
	while(i<tamanio){
		actual= actual->hijos[clave[i]];
		i++;
	}   
	return actual->significado;
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
void dicT<T>::borrar(string s){
	Nodo* actual= raiz;
	int i=0;
	int tamanio=s.size();
	pila<Nodo> recorridos;
	while(i<tamanio){
		recorridos.apilar(*actual);
		actual= actual -> hijos[s[i]];
		i++;
	}
	recorridos.apilar(*actual);
	while(recorridos.size()>1){
		actual=&recorridos.tope();
		recorridos.desapilar();
		if(EsVaciaHijos(actual)){
			int aux= actual->letra;
			recorridos.tope().hijos[aux]=0;
			delete(actual);
		}
	}
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
aed2::Conj<string> dicT<T>::claves() const{
	Nodo* actual= raiz;
	pila<Nodo> recorridos;
	apilarHijos(actual, recorridos);
	Conj<string> res;
	int contador=0;
	while(!(recorridos.EsVacia())){
		actual = &recorridos.tope();
		recorridos.desapilar();
		if(! EsVaciaHijos(actual)) apilarHijos(actual, recorridos);
		if(esPalabraFunc(actual)){
			string aux= DameNombre(actual); ///ANDA DAME NOMBRE ! :D
			res.AgregarRapido(aux);     
		}
	}   
	return res;
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <typename T>
bool dicT<T>::operator ==(dicT<T> &otro) {
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
template <typename T>
string dicT<T>::Minimo(){
	Nodo* actual=NULL; // para q entre en el primer while
	int i=0;
	while(actual==NULL){
		actual = raiz->hijos[i];
		i++;
	}
	while(!esPalabraFunc(actual)){
		Nodo* aux=NULL;
		i=0;
		while(aux==NULL){
			aux=actual->hijos[i];
			i++;
		}
		actual=aux;
	}
	return DameNombre(actual);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <typename T>
string dicT<T>::Maximo(){
	Nodo* actual=NULL; // para q entre en el primer while
	int i=255;
	while(actual==NULL){
		actual = raiz->hijos[i];
		i--;
	}
	while(!esPalabraFunc(actual)){
		Nodo* aux=NULL;
		i=255;
		while(aux==NULL){
			aux=actual->hijos[i];
			i--;
		}
		actual=aux;
	}
	return DameNombre(actual);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
typename dicT<T>::Iterador dicT<T>::CrearIt(){
	return Iterador(this);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
typename dicT<T>::const_Iterador dicT<T>::CrearIt2(){
	return const_Iterador(this);
}
















///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//FUNCIONES ITERADOR
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////



template<typename T>
dicT<T>::Iterador::Iterador()
	: dic(NULL)
{}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
dicT<T>::Iterador::Iterador(const typename dicT<T>::Iterador& otro)
	: dic(otro.dic), claves(otro.claves), siguiente(otro.siguiente)
{}  
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
bool dicT<T>::Iterador::HaySiguiente() const{
	return (siguiente.first.size()!=0);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
string  dicT<T>::Iterador::SiguienteClave(){
	return (siguiente.first);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
T& dicT<T>::Iterador::SiguienteSignificado(){
	return (siguiente.second);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
void dicT<T>::Iterador::Avanzar(){
	typename Conj<string>::Iterador it = claves.CrearIt();
	if(!it.HaySiguiente()){
		siguiente.first.clear();
	}
	else{
	siguiente.first=it.Siguiente();
	siguiente.second=(*dic).obtener(it.Siguiente());
	it.EliminarSiguiente();
	}   
}




///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//FUNCIONES CONST_ITERADOR
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


template<typename T>
dicT<T>::const_Iterador::const_Iterador()
	: dic(NULL)
{}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
dicT<T>::const_Iterador::const_Iterador(const typename dicT<T>::const_Iterador& otro)
	: dic(otro.dic), claves(otro.claves), siguiente(otro.siguiente)
{}  
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
bool dicT<T>::const_Iterador::HaySiguiente() const{
	return (siguiente.first.size()!=0);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
const string  dicT<T>::const_Iterador::SiguienteClave() const{
	return (siguiente.first);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
const T& dicT<T>::const_Iterador::SiguienteSignificado() const{
	return (siguiente.second);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<typename T>
void dicT<T>::const_Iterador::Avanzar(){
	typename Conj<string>::Iterador it = claves.CrearIt();
	if(!it.HaySiguiente()){
		siguiente.first.clear();
	}
	else{
	siguiente.first=it.Siguiente();
	siguiente.second=(*dic).obtener(it.Siguiente());
	it.EliminarSiguiente();
	}   
}


#endif
