#ifndef DATO_H 
#define DATO_H

#include "Conj.h"
#include <iostream>
#include "Tipos.h"

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
	void nuevoDatoNat( Nat nat);
	///////////////////////////////////
	void nuevoDatoString(String palabra);
	///////////////////////////////////
	bool tipo() const;
	///////////////////////////////////
	bool sonMismoTipo(const dato& otro);
	///////////////////////////////////
	Nat valorNat();
	///////////////////////////////////
	const Nat valorNat_const() const;
	///////////////////////////////////
	String valorString();	
	///////////////////////////////////
	const String valorString_const() const;	
	///////////////////////////////////
	bool esMenor(const dato& d);
	///////////////////////////////////
	bool operator==(dato d);
	bool operator==(const dato d) const;
	void operator= (Nat n);
	void operator=(String s);

private:
	Nat n;
	String s;
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
void dato::nuevoDatoNat(Nat nat){
	n=nat;
	t=true;
} 
///////////////////////////////////
void dato::nuevoDatoString(String palabra){
	s=palabra;
	t=false;
}
///////////////////////////////////
bool dato::tipo() const{
	return t;
}
///////////////////////////////////
bool dato::sonMismoTipo(const dato& otro){
	return (t==otro.t);
}
///////////////////////////////////
Nat dato::valorNat(){
	return n;
}
///////////////////////////////////
const Nat dato::valorNat_const() const{
	return n;
}
///////////////////////////////////
String dato::valorString(){
	return s;
}
///////////////////////////////////
const String dato::valorString_const() const{
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
void dato::operator=(Nat n){
	nuevoDatoNat(n);
}
void dato::operator=(String s){
	nuevoDatoString(s);
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
