#ifndef TABLA_H
#define TABLA_H

#include "registro.h"
#include "Conj.h"
#include "dicA.h"
#include "dicT.h"
#include "registro.h"

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
	dato minimo(NombreCampo c);
	dato maximo(NombreCampo c);
	void AuxiliarGVJ(tabla* otra, tabla* join, NombreCampo c);
	void AuxBuscar(NombreCampo criterioClave, Registro& criterio, Lista<Registro>& lr);
	bool estaValor(dato d);
	void auxVJ(NombreCampo c, tabla* t1, tabla* t2, dato d);
	
private:
	struct indiceNat{
		indiceNat(): maximo(0), minimo(0){}
		~indiceNat(){}
		NombreCampo nombreC;
		Nat maximo;
		Nat minimo;
		dicA<Nat, Lista<estrAux> > valoresYreg;

	};
	struct indiceString{
		~indiceString(){}
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
		if(indiceN_.nombreC.size()!= 0){res=true;}
		return res;
		}			
	void indexarNatAux(){ //si no lo paso por referencia hay un error q no sabria bien como resolver
		typename Lista<Registro>::Iterador it = registros_.CrearIt();
		while(it.HaySiguiente()){
			
			Nat valorADefinir = it.Siguiente().Significado(indiceN_.nombreC).valorNat();
			
			// creo la base para lo que viene
			if(! indiceN_.valoresYreg.definido(valorADefinir)){
					Lista<estrAux> vacia;
					indiceN_.valoresYreg.definir(valorADefinir, vacia);
			}
			
			if(hayIndiceString()){
				String valorDelOtro = it.Siguiente().Significado(indiceS_.nombreC).valorString();
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
			String valorADefinir = it.Siguiente().Significado(indiceS_.nombreC).valorString();
			
			// creo la base para lo que viene
			if(! indiceS_.valoresYreg.definido(valorADefinir)){
					Lista<estrAux> vacia;
					indiceS_.valoresYreg.definir(valorADefinir, vacia);
			}
			
			if(hayIndiceNat()){
				Nat valorDelOtro = it.Siguiente().Significado(indiceN_.nombreC).valorNat();
				
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
	
	Registro dameRegistroT(dicT<Lista<estrAux> >* d, String s){
		Registro res;
		Lista<estrAux>* aux=&d->obtener(s);
		typename Lista<estrAux>::Iterador itA=aux->CrearIt();
		estrAux eaux=itA.Siguiente();
		res=eaux.itReg.Siguiente();
		return res;
	}
	
	Registro dameRegistroN(dicA<Nat, Lista<estrAux> >* d,Nat n){
		Registro res;
		Lista<estrAux>* aux=&d->obtener(n);
		typename Lista<estrAux>::Iterador itA=aux->CrearIt();
		estrAux eaux=itA.Siguiente();
		res=eaux.itReg.Siguiente();
		return res;
	}		
	
	void generarRegistroYAgregarS(Lista<Registro>& cr, dicT<Lista<estrAux> >* d,NombreCampo c, tabla* join){
		typename::Lista<Registro>::Iterador it=cr.CrearIt();
		while(it.HaySiguiente()){
			Registro rT1=it.Siguiente();
			String valor= rT1.Significado(c).valorString();
			if(d->definido(valor)){
				Registro rCopia=Registro(rT1);
				Registro rT2= dameRegistroT(d,valor);
				rCopia.mergear(rT2); //X COPIA AMBOS!
				join->agregarRegistro(rT1);
				}
			it.Avanzar();	
			}
		}
	void generarRegistroYAgregarN(Lista<Registro>& cr, dicA<Nat, Lista<estrAux> >* d,NombreCampo c, tabla* join){
		typename::Lista<Registro>::Iterador it=cr.CrearIt();
		while(it.HaySiguiente()){
			Registro rT1=it.Siguiente(); //COPIA??
			Nat valor= rT1.Significado(c).valorNat();
			if(d->definido(valor)){
				Registro rCopia=Registro(rT1);
				Registro rT2= dameRegistroN(d,valor);
				rCopia.mergear(rT2); //X COPIA AMBOS!
				join->agregarRegistro(rT1);
				}
			it.Avanzar();	
			}
		}
		
	
	
};



tabla::tabla(): accesos_(0)
{
	indiceN_.nombreC= string();
	indiceN_.valoresYreg.Vacio();
	indiceS_.nombreC=string();
	indiceS_.valoresYreg.Vacio();
	}//preguntar si esta bien que deje todos los valores por defecto

tabla::tabla( const tabla& otra){
	accesos_=otra.accesos_;
	
	nombre_=otra.nombre_;
	registros_=Lista<Registro>(otra.registros_);
	campos_=Dicc<NombreCampo, TipoCampo>(otra.campos_);
	claves_=Conj<NombreCampo>(otra.claves_);
	
	indiceN_.nombreC=otra.indiceN_.nombreC;
	indiceN_.maximo=otra.indiceN_.maximo;
	indiceN_.minimo=otra.indiceN_.minimo;
	indiceN_.valoresYreg = dicA<Nat,Lista<estrAux> >(otra.indiceN_.valoresYreg);
	
	indiceS_.nombreC=otra.indiceS_.nombreC;
	indiceS_.maximo=otra.indiceS_.maximo;
	indiceS_.minimo=otra.indiceS_.minimo;
	indiceS_.valoresYreg = dicT<Lista<estrAux> >(otra.indiceS_.valoresYreg);
}

tabla::~tabla()
{}

void tabla::nuevaTabla(String n, Registro& col, Conj<NombreCampo>& c){
	nombre_= n;
	claves_=c;
	typename ::Registro::Iterador it = col.CrearIt();
	while(it.HaySiguiente()){
			if(it.SiguienteSignificado().tipo()){
			campos_.Definir(it.SiguienteClave(), NAT);
		}
		else{campos_.Definir(it.SiguienteClave(), STR);}
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
		if(!(indiceN_.valoresYreg.definido(r.Significado(indiceN_.nombreC).valorNat()))){
			Lista<estrAux> comelaFrancisco; // no se llama aux :DD
			indiceN_.valoresYreg.definir(r.Significado(indiceN_.nombreC).valorNat(), comelaFrancisco);
		}
		typename Lista<estrAux>::Iterador it = indiceN_.valoresYreg.obtener(r.Significado(indiceN_.nombreC).valorNat()).CrearItUlt();
		typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
		estrAux yaMeMuero;
		if(itRegistros.HayAnterior()){
		itRegistros.Retroceder();
		}
		yaMeMuero.itReg = itRegistros;
		it.AgregarComoSiguiente(yaMeMuero);
		///actualizo maximo y minimo
		if(r.Significado(indiceN_.nombreC).valorNat()>indiceN_.maximo) indiceN_.maximo=r.Significado(indiceN_.nombreC).valorNat();
		if(r.Significado(indiceN_.nombreC).valorNat()<indiceN_.minimo) indiceN_.minimo=r.Significado(indiceN_.nombreC).valorNat();
	}//end if

	if(hayIndiceString()){
		if(!(indiceS_.valoresYreg.definido(r.Significado(indiceS_.nombreC).valorString()))){
			Lista<estrAux> aux; 
			indiceS_.valoresYreg.definir(r.Significado(indiceS_.nombreC).valorString(), aux);
		}
		if(esValidoIndiceNat(indiceN_)){
			typename Lista<estrAux>::Iterador it = indiceN_.valoresYreg.obtener(r.Significado(indiceN_.nombreC).valorNat()).CrearItUlt();
			typename Lista<estrAux>::Iterador it1 = indiceS_.valoresYreg.obtener(r.Significado(indiceS_.nombreC).valorString()).CrearItUlt();
			estrAux yaMeMuero;
			typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
			if(itRegistros.HayAnterior()){
			itRegistros.Retroceder();
			}
			yaMeMuero.itReg= itRegistros;
			yaMeMuero.itEstr= it;
			it1.AgregarComoSiguiente(yaMeMuero);
			it.Anterior().itEstr= it1;  
		}
		else{
			typename Lista<estrAux>::Iterador it1 = indiceS_.valoresYreg.obtener(r.Significado(indiceS_.nombreC).valorString()).CrearItUlt();
			estrAux yaMeMuero;
			typename Lista<Registro>::Iterador itRegistros= registros_.CrearItUlt();
			if(itRegistros.HayAnterior()){
			itRegistros.Retroceder();
			}
			yaMeMuero.itReg= itRegistros;
			it1.AgregarComoSiguiente(yaMeMuero);
		}
		//actualizo maximo y minimo
		if(r.Significado(indiceS_.nombreC).valorString()>indiceS_.maximo) indiceS_.maximo=r.Significado(indiceS_.nombreC).valorString();
		if(r.Significado(indiceS_.nombreC).valorString()<indiceS_.minimo) indiceS_.minimo=r.Significado(indiceS_.nombreC).valorString();
	}
}

void tabla::borrarRegistro(Registro& crit){
	accesos_++;
	typename Registro::Iterador itCrit=crit.CrearIt();
	NombreCampo claveCrit=itCrit.SiguienteClave();
	dato significadoCrit=itCrit.SiguienteSignificado();
	if(pertenece(claveCrit,indices())){
		if(tipoCampo(claveCrit)==NAT){
			if(indiceN_.valoresYreg.definido(significadoCrit.valorNat())){
				typename Lista<estrAux>::Iterador it=indiceN_.valoresYreg.obtener(significadoCrit.valorNat()).CrearIt();
				while(it.HaySiguiente()){
					if(indices().Cardinal()==2){
						dato datoDelOtroIndice= it.Siguiente().itReg.Siguiente().Significado(indiceS_.nombreC);
						it.Siguiente().itEstr.EliminarSiguiente();
						if(indiceS_.valoresYreg.obtener(datoDelOtroIndice.valorString()).EsVacia()){
							indiceS_.valoresYreg.borrar(datoDelOtroIndice.valorString());
							indiceS_.maximo=indiceS_.valoresYreg.Maximo();
							indiceS_.minimo=indiceS_.valoresYreg.Minimo();
							}	
						}
					it.Siguiente().itReg.EliminarSiguiente();
					it.Avanzar();
					}
				indiceN_.valoresYreg.borrar(significadoCrit.valorNat());	
				indiceN_.maximo=indiceN_.valoresYreg.Maximo();
				indiceN_.minimo=indiceN_.valoresYreg.Minimo();		
			}
		}
		else{
			if(indiceS_.valoresYreg.definido(significadoCrit.valorString())){
				typename Lista<estrAux>::Iterador it=indiceS_.valoresYreg.obtener(significadoCrit.valorString()).CrearIt();
				while(it.HaySiguiente()){
					if(indices().Cardinal()==2){
						dato datoDelOtroIndice= it.Siguiente().itReg.Siguiente().Significado(indiceN_.nombreC);
						it.Siguiente().itEstr.EliminarSiguiente();
						if(indiceN_.valoresYreg.obtener(datoDelOtroIndice.valorNat()).EsVacia()){
							indiceN_.valoresYreg.borrar(datoDelOtroIndice.valorNat());
							indiceN_.maximo=indiceN_.valoresYreg.Maximo();
							indiceN_.minimo=indiceN_.valoresYreg.Minimo();
							}	
						}
					it.Siguiente().itReg.EliminarSiguiente();
					it.Avanzar();
					}
				indiceS_.valoresYreg.borrar(significadoCrit.valorString());	
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
				if(it.Siguiente().Significado(claveCrit).valorNat() == significadoCrit.valorNat())	b=true;
			}
			else {
				if(it.Siguiente().Significado(claveCrit).valorString() == significadoCrit.valorString()) b=true;
			}
						
			if(b){
				Registro registroABorrar=it.Siguiente();
				if(hayIndiceNat()){
					Nat valor=registroABorrar.Significado(indiceN_.nombreC).valorNat();
					typename Lista<estrAux>::Iterador itN=indiceN_.valoresYreg.obtener(valor).CrearIt();
					while(itN.HaySiguiente() && !(itN.Siguiente().itReg.Siguiente() == registroABorrar)){
						itN.Avanzar();
						}
					itN.EliminarSiguiente();	
					}
				if(hayIndiceString()){
					String valor=registroABorrar.Significado(indiceS_.nombreC).valorString();
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
		if(tipoCampo(c)== NAT){
			indiceN_.nombreC=c;
			indexarNatAux();
			}
		else{
			indiceS_.nombreC=c;
			indexarStringAux();
		}
		
	}

	dato tabla::minimo(NombreCampo c){
		if(tipoCampo(c)==NAT && hayIndiceNat()){
			dato res;
			res.nuevoDatoNat(indiceN_.valoresYreg.Minimo());
			return res;
		}else if(hayIndiceString()){
			dato res;
			res.nuevoDatoString(indiceS_.valoresYreg.Minimo());
			return res;
		}
	}
	dato tabla::maximo(NombreCampo c){
		if(tipoCampo(c)==NAT && hayIndiceNat()){
			dato res;
			res.nuevoDatoNat(indiceN_.valoresYreg.Maximo());
			return res;
		}else if(hayIndiceString()){
			dato res;
			res.nuevoDatoString(indiceS_.valoresYreg.Maximo());
			return res;
		}

	}

		
	void tabla::AuxiliarGVJ(tabla* otra, tabla* join, NombreCampo c){ 
		
			Lista<Registro> registrosDeOtraCopy=otra->registros();
			typename Lista<Registro>::Iterador regis=registrosDeOtraCopy.CrearIt();
			Lista<Registro> registt;
			
			while(regis.HaySiguiente()){
				Registro r;
				Conj<NombreCampo> camp=regis.Siguiente().campos();
				r.copiarCampos(camp,regis.Siguiente());
				registt.AgregarAtras(r);
				regis.Avanzar();
			}
			
			if(tipoCampo(c)==NAT){
			dicA<Nat, Lista<estrAux> >* iN=&indiceN_.valoresYreg;			
			generarRegistroYAgregarN(registt, iN,c,join);
			}
		else{
			dicT<Lista<estrAux> >* iS=&indiceS_.valoresYreg;
			generarRegistroYAgregarS(registt, iS,c,join);
			}
		}
				
	void tabla::AuxBuscar(NombreCampo criterioClave, Registro& criterio, Lista<Registro>& lr){
	if(tipoCampo(criterioClave)){
			dicA<Nat, Lista<estrAux> >* d= &indiceN_.valoresYreg;
			Nat n=criterio.Significado(criterioClave).valorNat();
			if(d->definido(n)){
			typename Lista<estrAux>::Iterador itLista= d->obtener(n).CrearIt();
			Registro regCriterioClave= itLista.Siguiente().itReg.Siguiente();	
			Conj<NombreCampo> claves=criterio.campos();
			if(criterio.coincidenTodos(claves, regCriterioClave)){
				Registro regCoincide(regCriterioClave);
				lr.AgregarAdelante(regCoincide);
			}
			}
		}
		else{
			dicT< Lista<estrAux> >* d= &indiceS_.valoresYreg;
			String s=criterio.Significado(criterioClave).valorString();
			if(d->definido(s)){
			typename Lista<estrAux>::Iterador itLista= d->obtener(s).CrearIt();
			Registro regCriterioClave= itLista.Siguiente().itReg.Siguiente();	
			Conj<NombreCampo> claves=criterio.campos();
			if(criterio.coincidenTodos(claves, regCriterioClave)){
				Registro regCoincide(regCriterioClave);
				lr.AgregarAdelante(regCoincide);
		}
		}
	}
}	
	bool tabla::estaValor(dato d){
		if(d.tipo()){
			return indiceN_.valoresYreg.definido(d.valorNat());
		}
		else{
			return indiceS_.valoresYreg.definido(d.valorString());
			}	
		}
		
	void tabla::auxVJ(NombreCampo c, tabla* t1, tabla* t2, dato d){
		if(d.tipo()){

			if(t1->indiceN_.valoresYreg.definido(d.valorNat())){
				if(t2->indiceN_.valoresYreg.definido(d.valorNat())){
					dicA<Nat, Lista<estrAux> >* d1=&t1->indiceN_.valoresYreg;
					dicA<Nat, Lista<estrAux> >* d2=&t2->indiceN_.valoresYreg;
					Registro rT1(dameRegistroN(d1,d.valorNat()));
					Registro rT2(dameRegistroN(d2,d.valorNat()));
					rT1.mergear(rT2);
					agregarRegistro(rT1);
					}
				}
			}
		else{
			
			if(t1->indiceS_.valoresYreg.definido(d.valorString())){
				if(t2->indiceS_.valoresYreg.definido(d.valorString())){
					dicT<Lista<estrAux> >* d1=&t1->indiceS_.valoresYreg;
					dicT<Lista<estrAux> >* d2=&t2->indiceS_.valoresYreg;
					Registro rT1(dameRegistroT(d1,d.valorString()));
					Registro rT2(dameRegistroT(d2,d.valorString()));
					rT1.mergear(rT2);
					agregarRegistro(rT1);
					}
				}
			
			}
		}	
	
#endif
