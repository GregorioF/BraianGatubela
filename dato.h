#ifndef DATO_H 
#define DATO_H

#include "Conj.h"
#include <iostream>

using namespace std;
using namespace aed2;

class dato{
public:
	dato();
	///////////////////////////////////
	dato(const dato& otro);
	///////////////////////////////////
	~dato();
	///////////////////////////////////
	void nuevoDatoNat( int nat);
	///////////////////////////////////
	void nuevoDatoString(string palabra);
	///////////////////////////////////
	bool tipo();
	///////////////////////////////////
	bool sonMismoTipo(const dato& otro);
	///////////////////////////////////
	int valorNat();
	///////////////////////////////////
	const int valorNat_const() const;
	///////////////////////////////////
	string valorString();	
	///////////////////////////////////
	const string valorString_const() const;	
	///////////////////////////////////
	bool esMenor(const dato& d);
	///////////////////////////////////
	bool operator==(dato d);
	bool operator==(const dato d) const;

private:
	int n;
	string s;
	bool t;

};
///////////////////////////////////
//FUNCIONES
///////////////////////////////////
dato::dato():n(0), t(1)
{}
///////////////////////////////////
dato::dato(const dato& otro){
	n=otro.n;
	s=otro.s;
	t=otro.t;
}
///////////////////////////////////
dato::~dato(){}
//pre: t = true;
void dato::nuevoDatoNat(int nat){
	n=nat;
	t=1;
} 
///////////////////////////////////
void dato::nuevoDatoString(string palabra){
	s=palabra;
	t=false;
}
///////////////////////////////////
bool dato::tipo(){
	return t;
}
///////////////////////////////////
bool dato::sonMismoTipo(const dato& otro){
	return (t==otro.t);
}
///////////////////////////////////
int dato::valorNat(){
	return n;
}
///////////////////////////////////
const int dato::valorNat_const() const{
	return n;
}
///////////////////////////////////
string dato::valorString(){
	return s;
}
///////////////////////////////////
const string dato::valorString_const() const{
	return s;
}
///////////////////////////////////
bool dato::esMenor(const dato& otro){
	if(otro.t) return (otro.n < n);
	else return (otro.s < s);
}

bool dato::operator==(dato d){
	if(sonMismoTipo(d)){
		if(tipo()){return valorNat()==d.valorNat();}
		else{return valorString()==d.valorString();}
		}
	else{return false;}	
	}
	
bool dato::operator==(const dato d) const{
	if(t==d.t){
		if(t){return valorNat_const()==d.valorNat_const();}
		else{return valorString_const()==d.valorString_const();}
		}
	else{return false;}	
	}	

namespace Dato{
	dato maximo(Conj<dato>& cd){
		typename Conj<dato>::Iterador it = cd.CrearIt();
		dato res= it.Siguiente();
		it.Avanzar();
		if(res.tipo())
			while(it.HaySiguiente()){
				if(it.Siguiente().valorNat_const() > res.valorNat()) res= it.Siguiente();
				it.Avanzar();
			}	
		else
			while(it.HaySiguiente()){
				if(it.Siguiente().valorString_const() > res.valorString()) res=it.Siguiente();
				it.Avanzar();
			}
		return res;
	}

	dato minimo(Conj<dato>& cd){
		typename Conj<dato>::Iterador it = cd.CrearIt();
		dato res= it.Siguiente();
		it.Avanzar();
		if(res.tipo())
			while(it.HaySiguiente()){
				if(it.Siguiente().valorNat_const() < res.valorNat()) res=it.Siguiente();
				it.Avanzar();
			}
		else
			while(it.HaySiguiente()){
				if(it.Siguiente().valorString_const() < res.valorString()) res= it.Siguiente();
				it.Avanzar();
			}
		return res;
	}
}



#endif
