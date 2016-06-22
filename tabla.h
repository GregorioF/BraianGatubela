#ifndef TABLA_H
#define TABLA_H

#include <iostream>
#include "Conj.h"

using namespace std;
using namespace ae2;

class tabla
{
public:
	struct estrAux
	{
		typename Conj<registro>::Iterador itReg;
		typename Lista<estrAux>::Iterador itEstr;		
	};


	tabla();
	tabla( const tabla& otra);
	~tabla();
	void nuevaTabla(String nombre, Conj<NombreCampo>& claves, registro& columnas);
	String nombre();
	Conj<NombreCampo> claves();
	Conj<NombreCampo> indices();
	Conj<NombreCampo> campos();
	TipoCampo tipoCampo(NombreCampo c);
	Conj<registro> registros();
	Nat cantDeAccesos();

	void agregarRegistro(registro& r);
	void borrarRegistro(registro& crit);
	void indexar(NombreCampo c);
	dato minimo(NombreCampo c);
	dato maximo(NombreCampo c);
	Conj<registro> buscar(registro& crit);
	Conj<registro> dameColumna(NombreCampo c);
	dicA<Nat,Lista(estrAux)> dameColumnaNat();
	dicT<Lista(estrAux)> dameColumnaString();

private:
	struct indiceNat{
		indiceNat(): maximo(0), minimo(0){}
		NombreCampo nombreC;
		Nat maximo;
		Nat minimo;
		dicA<Nat, Lista<estrAux>> valoresYreg;

	};
	struct indiceString{
		NombreCampo nombreC;
		String maximo;
		String minimo;
		dicT<Lista<estrAux>> valoresYreg;		
	};

	Nat accesos_;
	String nombre_;
	Lista<registro*> registros_;
	Dicc<NombreCampo,tipoCampo> campos_;
	Conj<NombreCampo> claves_;
	indiceNat indiceN_;
	indiceString indiceS_;
	
};

tabla::tabla()
{}//preguntar si esta bien que deje todos los valores por defecto

tabla::~tabla(): accesos_(0)
{}

void tabla::nuevaTabla(String n, Conj<NombreCampo>& c, registro& col){
	nombre_= n;
	claves_=c;
	typename ::registro::Iterador it = col.CrearIt();
	while(it.HaySiguiente()){
			campos_.definir(it.SiguienteClave(), tipo(it.SiguienteSignificado()));
			it.Avanzar();
	}
}

String tabla::nombre(){
	return nombre_;
}

Conj<NombreCampo> tabla::claves(){
	return claves_;
}

Conj<NombreCampo> tabla::indices(){
	Conj<NombreCampo> res;
	if(indiceN_.nombreC.size()!=0) res.AgregarRapido(indiceN_.nombreC);
	if(indiceS_.nombreC.size()!=0) res.AgregarRapido(indiceS_.nombreC);
	return res;
}

Conj<NombreCampo> tabla::campos(){
	Conj<NombreCampo> res;
	typename Dicc<NombreCampo, tipoCampo>::Iterador it = campos_.CrearIt();
	while(campos_.HaySiguiente()){
		res.AgregarRapido(it.SiguienteClave());
		it.Avanzar();
	}
	return res;
}

TipoCampo tabla::tipoCampo(NombreCampo c){
	return campos_.Significado(c);
}

Conj<registro> tabla::registros(){
	return registros_;
}
Nat tabla::cantDeAccesos(){
	return accesos_;
}x

void tabla::agregarRegistro(registro& r){
	typename Lista<registro*>::Iterador it = registros_.CrearIt();
	it.AgregaroComoSiguiente(&r);
	accesos_++;
	if(indiceN_.nombreC.size()!=0){
		String campoN = r.Significado(indiceN_.nombreC);
		if(!(indiceN_.valoresYreg.definido(campoN)))
			indiceN_.valoresYreg.definir(campoN)
	}
}
 
#endif