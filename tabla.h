#ifndef TABLA_H
#define TABLA_H

#include "registro.h"
#include "Conj.h"
#include "dicA.h"
#include "dicT.h"


using namespace aed2;

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

class tabla
{
public:
	


	tabla();
	tabla( const tabla& otra);
	~tabla(); 
	void nuevaTabla(String nombre, Registro& columnas ,  Conj<NombreCampo>& claves);
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
	//Conj<Registro> dameColumna(NombreCampo c);
	dicA<Nat, Lista<estrAux> >* dameColumnaNat();
	dicT< Lista<estrAux> >* dameColumnaString();
	dicA<Nat, Lista<estrAux> > dameColumnaNatParaTest();

	
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



	//AUXILIARES:

	bool pertenece(NombreCampo c, Conj<NombreCampo> cc){
		typename::Conj<NombreCampo>::Iterador it=cc.CrearIt();
		bool res=false;
		while(it.HaySiguiente()){
			if(it.Siguiente()==c) res=true;
			it.Avanzar();
			}
		return res;	
		}
		
	bool hayIndiceString(){
		bool res=false;
		if(indiceS_.nombreC.size()!=0){res=true;}
		return res;
		}
	bool hayIndiceNat(){
		bool res=false;
		if(indiceN_.nombreC.size()!=0){res=true;}
		return res;
		}			
	void indexarNatAux(){ //si no lo paso por referencia hay un error q no sabria bien como resolver
		typename Lista<Registro>::Iterador it = registros_.CrearIt();
		while(it.HaySiguiente()){
			Nat valorADefinir = it.Siguiente().Significado(indiceN_.nombreC).dameNat();
			
			// creo la base para lo que viene
			if(! indiceN_.valoresYreg.definido(valorADefinir)){
					Lista<estrAux> vacia;
					indiceN_.valoresYreg.definir(valorADefinir, vacia);
			}
			
			if(hayIndiceString()){
				String valorDelOtro = it.Siguiente().Significado(indiceS_.nombreC).dameString();
				
				typename Lista<estrAux>::Iterador itListEstr= indiceS_.valoresYreg.obtener(valorDelOtro).CrearIt();
				//mientras no haya llegado a la estrAux que apuntan al mismo registro
				while(itListEstr.HaySiguiente() && !(itListEstr.Siguiente().itReg.Siguiente() == it.Siguiente()) ){
					itListEstr.Avanzar();
				}
				//Salen itListEstr.Siguiente().itReg.Siguiente()  e it apuntando al mismo registro
				typename Lista<estrAux>::Iterador itAux = indiceN_.valoresYreg.obtener(valorADefinir).CrearItUlt();
				estrAux estrTemp;
				estrTemp.itReg= it;
				estrTemp.itEstr= itListEstr;
				itAux.AgregarComoSiguiente(estrTemp);
				itListEstr.Siguiente().itEstr= itAux; 
			}
			else{
				typename Lista<estrAux>::Iterador itAux = indiceN_.valoresYreg.obtener(valorADefinir).CrearItUlt();
				estrAux estrTemp;
				estrTemp.itReg= it;
				itAux.AgregarComoSiguiente(estrTemp);
			}
			it.Avanzar();
		}
		///ACTUALIZAR MAXIMO Y MINIMO!!!
	}	
	void indexarStringAux(){
		typename Lista<Registro>::Iterador it = registros_.CrearIt();
		while(it.HaySiguiente()){
			String valorADefinir = it.Siguiente().Significado(indiceS_.nombreC).dameString();
			
			// creo la base para lo que viene
			if(! indiceS_.valoresYreg.definido(valorADefinir)){
					Lista<estrAux> vacia;
					indiceS_.valoresYreg.definir(valorADefinir, vacia);
			}
			
			if(hayIndiceNat()){
				Nat valorDelOtro = it.Siguiente().Significado(indiceN_.nombreC).dameNat();
				
				typename Lista<estrAux>::Iterador itListEstr= indiceN_.valoresYreg.obtener(valorDelOtro).CrearIt();
				//mientras no haya llegado a la estrAux que apuntan al mismo registro
				while(itListEstr.HaySiguiente() && !(itListEstr.Siguiente().itReg.Siguiente() == it.Siguiente()) ){
					itListEstr.Avanzar();
				}
				//Salen itListEstr.Siguiente().itReg.Siguiente()  e it apuntando al mismo registro
				typename Lista<estrAux>::Iterador itAux = indiceS_.valoresYreg.obtener(valorADefinir).CrearItUlt();
				estrAux estrTemp;
				estrTemp.itReg= it;
				estrTemp.itEstr= itListEstr;
				itAux.AgregarComoSiguiente(estrTemp);
				itListEstr.Siguiente().itEstr= itAux; 
			}
			else{
				typename Lista<estrAux>::Iterador itAux = indiceS_.valoresYreg.obtener(valorADefinir).CrearItUlt();
				estrAux estrTemp;
				estrTemp.itReg= it;
				itAux.AgregarComoSiguiente(estrTemp);
			}
			it.Avanzar();
		}
	}


	bool esValidoIndiceNat(indiceNat i){
		return i.nombreC.size()!=0;
	}
	bool esValidoIndiceString(indiceString i){
		return i.nombreC.size()!=0;
	}
	
	
};



tabla::tabla(): accesos_(0)
{}//preguntar si esta bien que deje todos los valores por defecto

tabla::tabla( const tabla& otra){
	accesos_=otra.accesos_;
	
	String nombre_=otra.nombre_;
	registros_=Lista<Registro>(otra.registros_);
	campos_=Dicc<NombreCampo, TipoCampo>(otra.campos_);
	claves_=Conj<NombreCampo>(otra.claves_);
	indiceN_=indiceNat();
	indiceS_=indiceString();
	indiceN_.nombreC=otra.indiceN_.nombreC;
	indiceN_.maximo=otra.indiceN_.maximo;
	indiceN_.minimo=otra.indiceN_.minimo;
	if(!(otra.indiceN_.valoresYreg.esVacio())){
	indiceN_.valoresYreg=dicA<Nat,Lista<estrAux> >(otra.indiceN_.valoresYreg);
	}
	indiceS_.nombreC=otra.indiceS_.nombreC;
	indiceS_.maximo=otra.indiceS_.maximo;
	indiceS_.minimo=otra.indiceS_.minimo;
	if(!(otra.indiceS_.valoresYreg.esVacio())){
	indiceS_.valoresYreg=dicT<Lista<estrAux> >(otra.indiceS_.valoresYreg);
	}
	
	}

tabla::~tabla()
{}

void tabla::nuevaTabla(String n, Registro& col, Conj<NombreCampo>& c){
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
	if(hayIndiceNat()){
		if(!(indiceN_.valoresYreg.definido(r.Significado(indiceN_.nombreC).dameNat()))){
			Lista<estrAux> comelaFrancisco; // no se llama aux :DD
			indiceN_.valoresYreg.definir(r.Significado(indiceN_.nombreC).dameNat(), comelaFrancisco);
		}
		typename Lista<estrAux>::Iterador it = indiceN_.valoresYreg.obtener(r.Significado(indiceN_.nombreC).dameNat()).CrearItUlt();
		typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
		estrAux yaMeMuero;
		if(itRegistros.HayAnterior()){
		itRegistros.Retroceder();
		}
		yaMeMuero.itReg = itRegistros;
		it.AgregarComoSiguiente(yaMeMuero);
		///actualizo maximo y minimo
		if(r.Significado(indiceN_.nombreC).dameNat()>indiceN_.maximo) indiceN_.maximo=r.Significado(indiceN_.nombreC).dameNat();
		if(r.Significado(indiceN_.nombreC).dameNat()<indiceN_.minimo) indiceN_.minimo=r.Significado(indiceN_.nombreC).dameNat();
	}//end if

	if(hayIndiceString()){
		if(!(indiceS_.valoresYreg.definido(r.Significado(indiceS_.nombreC).dameString()))){
			Lista<estrAux> aux; 
			indiceS_.valoresYreg.definir(r.Significado(indiceS_.nombreC).dameString(), aux);
		}
		if(esValidoIndiceNat(indiceN_)){
			typename Lista<estrAux>::Iterador it = indiceN_.valoresYreg.obtener(r.Significado(indiceN_.nombreC).dameNat()).CrearItUlt();
			typename Lista<estrAux>::Iterador it1 = indiceS_.valoresYreg.obtener(r.Significado(indiceS_.nombreC).dameString()).CrearItUlt();
			estrAux yaMeMuero;
			typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
			if(itRegistros.HayAnterior()){
			itRegistros.Retroceder();
			}
			yaMeMuero.itReg= itRegistros;
			yaMeMuero.itEstr= it;
			it1.AgregarComoSiguiente(yaMeMuero);
			it.Siguiente().itEstr= it1;  
		}
		else{
			typename Lista<estrAux>::Iterador it1 = indiceS_.valoresYreg.obtener(r.Significado(indiceS_.nombreC).dameString()).CrearItUlt();
			estrAux yaMeMuero;
			typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
			if(itRegistros.HayAnterior()){
			itRegistros.Retroceder();
			}
			yaMeMuero.itReg= itRegistros;
			it1.AgregarComoSiguiente(yaMeMuero);
		}
		//actualizo maximo y minimo
		if(r.Significado(indiceS_.nombreC).dameString()>indiceS_.maximo) indiceS_.maximo=r.Significado(indiceS_.nombreC).dameString();
		if(r.Significado(indiceS_.nombreC).dameString()<indiceS_.minimo) indiceS_.minimo=r.Significado(indiceS_.nombreC).dameString();
	}
}

void tabla::borrarRegistro(Registro& crit){
	accesos_++;
	typename Dicc<NombreCampo, Dato>::Iterador itCrit=crit.CrearIt();
	NombreCampo claveCrit=itCrit.SiguienteClave();
	Dato significadoCrit=itCrit.SiguienteSignificado();
	if(pertenece(claveCrit,indices())){
		if(tipoCampo(claveCrit)==NAT){
			if(indiceN_.valoresYreg.definido(significadoCrit.dameNat())){
				typename Lista<estrAux>::Iterador it=indiceN_.valoresYreg.obtener(significadoCrit.dameNat()).CrearIt();
				while(it.HaySiguiente()){
					if(indices().Cardinal()==2){
						Dato datoDelOtroIndice= it.Siguiente().itReg.Siguiente().Significado(indiceS_.nombreC);
						it.Siguiente().itEstr.EliminarSiguiente();
						if(indiceS_.valoresYreg.obtener(datoDelOtroIndice.dameString()).EsVacia()){
							indiceS_.valoresYreg.borrar(datoDelOtroIndice.dameString());
							indiceS_.maximo=indiceS_.valoresYreg.Maximo();
							indiceS_.minimo=indiceS_.valoresYreg.Minimo();
							}	
						}
					it.Siguiente().itReg.EliminarSiguiente();
					it.Avanzar();
					}
				indiceN_.valoresYreg.borrar(significadoCrit.dameNat());	
				indiceN_.maximo=indiceN_.valoresYreg.Maximo();
				indiceN_.minimo=indiceN_.valoresYreg.Minimo();		
			}
		}
		else{
			if(indiceS_.valoresYreg.definido(significadoCrit.dameString())){
				typename Lista<estrAux>::Iterador it=indiceS_.valoresYreg.obtener(significadoCrit.dameString()).CrearIt();
				while(it.HaySiguiente()){
					if(indices().Cardinal()==2){
						Dato datoDelOtroIndice= it.Siguiente().itReg.Siguiente().Significado(indiceN_.nombreC);
						it.Siguiente().itEstr.EliminarSiguiente();
						if(indiceN_.valoresYreg.obtener(datoDelOtroIndice.dameNat()).EsVacia()){
							indiceN_.valoresYreg.borrar(datoDelOtroIndice.dameNat());
							indiceN_.maximo=indiceN_.valoresYreg.Maximo();
							indiceN_.minimo=indiceN_.valoresYreg.Minimo();
							}	
						}
					it.Siguiente().itReg.EliminarSiguiente();
					it.Avanzar();
					}
				indiceS_.valoresYreg.borrar(significadoCrit.dameString());	
				indiceS_.maximo=indiceS_.valoresYreg.Maximo();
				indiceS_.minimo=indiceS_.valoresYreg.Minimo();		
			}
			}	
	}
	else{
		typename Lista<Registro>::Iterador it=registros_.CrearIt();
		while(it.HaySiguiente()){
			bool b=false;
			if(tipoCampo(claveCrit) == NAT) {
				if(it.Siguiente().Significado(claveCrit) == significadoCrit.dameNat())	b=true;
			}
			else {
				if(it.Siguiente().Significado(claveCrit) == significadoCrit.dameString()) b=true;
			}
						
			if(b){
				Registro registroABorrar=it.Siguiente();
				if(hayIndiceNat()){
					Nat valor=registroABorrar.Significado(indiceN_.nombreC).dameNat();
					typename Lista<estrAux>::Iterador itN=indiceN_.valoresYreg.obtener(valor).CrearIt();
					while(itN.HaySiguiente() && !(itN.Siguiente().itReg.Siguiente() == registroABorrar)){
						itN.Avanzar();
						}
					itN.EliminarSiguiente();	
					}
				if(hayIndiceString()){
					String valor=registroABorrar.Significado(indiceS_.nombreC).dameString();
					typename Lista<estrAux>::Iterador itS=indiceS_.valoresYreg.obtener(valor).CrearIt();
					while(itS.HaySiguiente() && !(itS.Siguiente().itReg.Siguiente() == registroABorrar)){
						itS.Avanzar();
						}
					itS.EliminarSiguiente();
					}
				it.Avanzar();
				it.EliminarAnterior();
				}
			else it.Avanzar();	
			
			}
		}
	}

	void tabla::indexar(NombreCampo c){
		if(tipoCampo(c)==NAT){
			indiceN_.nombreC=c;
			indexarNatAux();
		}
		else{
			indiceS_.nombreC=c;
			indexarStringAux();
		}
	}

	Dato tabla::minimo(NombreCampo c){
		if(tipoCampo(c)==NAT && hayIndiceNat()){
			Dato res (indiceN_.valoresYreg.Minimo());
			return res;
		}else if(hayIndiceString()){
			Dato res (indiceS_.valoresYreg.Minimo());
			return res;
		}
		Dato res (3);
		return res;
	}
	Dato tabla::maximo(NombreCampo c){
		if(tipoCampo(c)==NAT && hayIndiceNat()){
			Dato res (indiceN_.valoresYreg.Maximo());
			return res;
		}else if(hayIndiceString()){
			Dato res (indiceS_.valoresYreg.Maximo());
			return res;
		}
		Dato res (3);
		return res;
	}

	dicA<Nat, Lista<estrAux> >* tabla::dameColumnaNat(){
		dicA<Nat, Lista<estrAux> >* res= &indiceN_.valoresYreg;
		return res;
	}
	
	dicT<Lista<estrAux> >* tabla::dameColumnaString(){
		dicT<Lista<estrAux> >* res= &indiceS_.valoresYreg;
		return res;
	}
	
	dicA<Nat, Lista<estrAux> > tabla::dameColumnaNatParaTest(){
		return indiceN_.valoresYreg;
	}
	
	
 
#endif
