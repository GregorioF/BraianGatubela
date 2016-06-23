#ifndef TABLA_H
#define TABLA_H

#include "registro.h"
#include "Conj.h"
#include "dicA.h"
#include "dicT.h"


using namespace aed2;

class tabla
{
public:
	struct estrAux
	{
		estrAux(){}
		estrAux( const estrAux& otra){
			itReg=otra.itReg;
			itEstr=otra.itEstr;
		}
		typename Lista<Registro>::Iterador itReg;
		typename Lista<estrAux>::Iterador itEstr;		
	};


	tabla();
	tabla( const tabla& otra);
	~tabla();
	void nuevaTabla(String nombre, Conj<NombreCampo>& claves, Registro& columnas);
	String nombre();
	Conj<NombreCampo> claves();
	Conj<NombreCampo> indices();
	Conj<NombreCampo> campos();
	TipoCampo tipoCampo(NombreCampo c);
	Lista<Registro> registros();
	Nat cantDeAccesos();

	void agregarRegistro(Registro& r);
	void borrarRegistro(Registro& crit);
	void indexar(NombreCampo c);
	Dato minimo(NombreCampo c);
	Dato maximo(NombreCampo c);
	Conj<Registro> buscar(Registro& crit);
	Conj<Registro> dameColumna(NombreCampo c);
	dicA<Nat, Lista<estrAux> > dameColumnaNat();
	dicT< Lista<estrAux> > dameColumnaString();

private:
	struct indiceNat{
		indiceNat(): maximo(0), minimo(0){}
		NombreCampo nombreC;
		Nat maximo;
		Nat minimo;
		dicA<Nat, Lista<estrAux> > valoresYreg;

	};
	struct indiceString{
		NombreCampo nombreC;
		String maximo;
		String minimo;
		dicT<Lista<estrAux> > valoresYreg;		
	};

	Nat accesos_;
	String nombre_;
	Lista<Registro> registros_;
	Dicc<NombreCampo,TipoCampo> campos_;
	Conj<NombreCampo> claves_;
	indiceNat indiceN_;
	indiceString indiceS_;

	bool esValidoIndiceNat(indiceNat i){
		return i.nombreC.size()!=0;
	}
	bool esValidoIndiceString(indiceString i){
		return i.nombreC.size()!=0;
	}
	
};

tabla::tabla(): accesos_(0)
{}//preguntar si esta bien que deje todos los valores por defecto

tabla::~tabla()
{}

void tabla::nuevaTabla(String n, Conj<NombreCampo>& c, Registro& col){
	nombre_= n;
	claves_=c;
	typename ::Registro::Iterador it = col.CrearIt();
	while(it.HaySiguiente()){
			campos_.Definir(it.SiguienteClave(), it.SiguienteSignificado().tipo());
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
	typename Dicc<NombreCampo, TipoCampo>::Iterador it = campos_.CrearIt();
	while(it.HaySiguiente()){
		res.AgregarRapido(it.SiguienteClave());
		it.Avanzar();
	}
	return res;
}

TipoCampo tabla::tipoCampo(NombreCampo c){
	return campos_.Significado(c);
}

Lista<Registro> tabla::registros(){
	return registros_;
}
Nat tabla::cantDeAccesos(){
	return accesos_;
}

void tabla::agregarRegistro(Registro& r){
	accesos_++;
	registros_.AgregarAtras(r);
	if(esValidoIndiceNat(indiceN_)){
		if(!(indiceN_.valoresYreg.definido(r.Significado(indiceN_.nombreC).dameNat()))){
			Lista<estrAux> comelaFrancisco; // no se llama aux :DD
			indiceN_.valoresYreg.definir(r.Significado(indiceN_.nombreC).dameNat(), comelaFrancisco);
		}
		typename Lista<estrAux>::Iterador it = indiceN_.valoresYreg.obtener(r.Significado(indiceN_.nombreC).dameNat()).CrearItUlt();
		typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
		estrAux yaMeMuero;
		yaMeMuero.itReg = itRegistros;
		it.AgregarComoSiguiente(yaMeMuero);
		///actualizo maximo y minimo
		if(r.Significado(indiceN_.nombreC).dameNat()>indiceN_.maximo) indiceN_.maximo=r.Significado(indiceN_.nombreC).dameNat();
		if(r.Significado(indiceN_.nombreC).dameNat()<indiceN_.minimo) indiceN_.minimo=r.Significado(indiceN_.nombreC).dameNat();
	}//end if

	if(esValidoIndiceString(indiceS_)){
		if(!(indiceS_.valoresYreg.definido(r.Significado(indiceS_.nombreC).dameString()))){
			Lista<estrAux> aux; 
			indiceS_.valoresYreg.definir(r.Significado(indiceS_.nombreC).dameString(), aux);
		}
		if(esValidoIndiceNat(indiceN_)){
			typename Lista<estrAux>::Iterador it = indiceN_.valoresYreg.obtener(r.Significado(indiceN_.nombreC).dameNat()).CrearItUlt();
			typename Lista<estrAux>::Iterador it1 = indiceS_.valoresYreg.obtener(r.Significado(indiceS_.nombreC).dameString()).CrearItUlt();
			estrAux yaMeMuero;
			typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
			yaMeMuero.itReg= itRegistros;
			yaMeMuero.itEstr= it;
			it1.AgregarComoSiguiente(yaMeMuero);
			it.Siguiente().itEstr= it1;  
		}
		else{
			typename Lista<estrAux>::Iterador it1 = indiceS_.valoresYreg.obtener(r.Significado(indiceS_.nombreC).dameString()).CrearItUlt();
			estrAux yaMeMuero;
			typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
			yaMeMuero.itReg= itRegistros;
			it1.AgregarComoSiguiente(yaMeMuero);
		}
		//actualizo maximo y minimo
		if(r.Significado(indiceS_.nombreC).dameString()>indiceS_.maximo) indiceS_.maximo=r.Significado(indiceS_.nombreC).dameString();
		if(r.Significado(indiceS_.nombreC).dameString()<indiceS_.minimo) indiceS_.minimo=r.Significado(indiceS_.nombreC).dameString();
	}
}
 
#endif