#ifndef BD_H
#define BD_H

#include "Dicc.h"
#include "dicT.h"
#include "dicA.h"
#include "tabla.h"
#include "registro.h"
#include <iostream>

using namespace aed2;
using namespace std;


class BD{
public:

	BD();
	
	void agregarTabla(const tabla);	
	
	~BD();  
	
	void insertarEntrada(const Registro, const NombreTabla);
	
	void borrar(Registro, const NombreTabla);
	
	typename::Lista<Registro>::Iterador generarVistaJoin(NombreTabla, NombreTabla, NombreCampo); 
	
	void borrarJoin(NombreTabla, NombreTabla);
	
	typename::Lista<NombreTabla>::Iterador tablas();
	
	tabla* dameTabla(NombreTabla);
		
	bool hayJoin(NombreTabla, NombreTabla);
	
	NombreCampo campoJoin(NombreTabla, NombreTabla); 
	
	typename::Lista<Registro>::Iterador registros(NombreTabla);
	
	typename::Lista<Registro>::Iterador vistaJoin(NombreTabla, NombreTabla);
	
	Nat cantDeAccesos(NombreTabla);
	
	NombreTabla tablaMaxima();
	
	Lista<Registro> buscar(const Registro, NombreTabla);
	
		
private:
	struct modificaciones
	{
		modificaciones(bool b, Registro r): seAgrego_(b), reg_(r){}	
		bool seAgrego_;
		Registro reg_;	
	
	};
	
	
	struct tuplaJoin
	{
		tuplaJoin(NombreCampo c, tabla j){
		campoJ_=c;
		mod_=Lista<modificaciones>();
		join_=j;			
		}	
		
		NombreCampo campoJ_;
		Lista<BD::modificaciones> mod_;
		tabla join_;		
		
	};
	
	Lista<NombreTabla> tablas_;
	dicT<tabla> tablasPuntero;
	dicT<dicT<tuplaJoin> > joins_;
	NombreTabla tablaMax;
	
	///////////////////////////////////////////////
	//FUNCIONES AUXILIARES
	///////////////////////////////////////////////
	Registro merge(Registro r1, Registro r2){
		Registro res=Registro(r1);
		typename::Registro::Iterador it=r2.CrearIt();
		while(it.HaySiguiente()){
			if(!res.Definido(it.SiguienteClave())) res.DefinirRapido(it.SiguienteClave(),it.SiguienteSignificado());
			it.Avanzar();
			}
		return res;	
	}
	
	void crearCamposTablaJoin(Registro r, Conj<NombreCampo> c, tabla t){
		typename::Conj<NombreCampo>::Iterador it=c.CrearIt();
		while(it.HaySiguiente()){
			if(t.tipoCampo(it.Siguiente())){
				Nat n=0;
				Dato d=Dato(n);
				if(!r.Definido(it.Siguiente())){
				r.DefinirRapido(it.Siguiente(),d);
				}
			}
			else{
				String s;
				Dato d=Dato(s);
				if(!r.Definido(it.Siguiente())){
				r.DefinirRapido(it.Siguiente(),d);
				}
			}
			it.Avanzar();
		}				
	}
	
	Registro dameRegistroT(dicT<Lista<estrAux> > d, String s){
		Registro res;
		Lista<estrAux> aux=d.obtener(s);
		typename Lista<estrAux>::Iterador itA=aux.CrearIt();
		estrAux eaux=itA.Siguiente();
		res=eaux.itReg.Siguiente();
		return res;
		}
	Registro dameRegistroN(dicA<Nat, Lista<estrAux> > d,Nat n){
		Registro res;
		Lista<estrAux> aux=d.obtener(n);
		typename Lista<estrAux>::Iterador itA=aux.CrearIt();
		estrAux eaux=itA.Siguiente();
		res=eaux.itReg.Siguiente();
		return res;
		}		
	
	bool pertenece(NombreCampo c, Conj<NombreCampo> cc){
		typename::Conj<NombreCampo>::Iterador it=cc.CrearIt();
		bool res=false;
		while(it.HaySiguiente()){
			if(it.Siguiente()==c) res=true;
			it.Avanzar();
			}
		return res;	
		}
		
	void generarRegistrosJoinT(Lista<Registro> cr, dicT<Lista<estrAux> > cT2, NombreCampo campoJoin, tabla join){
		typename::Lista<Registro>::Iterador it=cr.CrearIt();
		while(it.HaySiguiente()){
			Registro rT1=it.Siguiente();
			String valorCampoJoin= rT1.Significado(campoJoin).dameString();
			if(cT2.definido(valorCampoJoin)){
				Registro rT2= dameRegistroT(cT2,valorCampoJoin);
				Registro rMergeado=merge(rT1,rT2); //X COPIA AMBOS!
				join.agregarRegistro(rMergeado);
				}
			it.Avanzar();	
			}
		}
		
	void generarRegistrosJoinN(Lista<Registro> cr, dicA<Nat,Lista<estrAux> > cT2, NombreCampo campoJoin, tabla join){
		typename::Lista<Registro>::Iterador it=cr.CrearIt();
		while(it.HaySiguiente()){
			Registro rT1=it.Siguiente();
			Nat valorCampoJoin= rT1.Significado(campoJoin).dameNat();
			if(cT2.definido(valorCampoJoin)){
				Registro rT2=dameRegistroN(cT2,valorCampoJoin);
				Registro rMergeado=merge(rT1,rT2); //X COPIA AMBOS!
				join.agregarRegistro(rMergeado);
				}
			it.Avanzar();	
			}
		}	
		
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

BD::BD(){}
	
BD::~BD(){
	
	typename Lista<NombreTabla>::Iterador itT1=tablas_.CrearIt();	
		while(itT1.HaySiguiente()){
			if(joins_.definido(itT1.Siguiente())){
				dicT<tuplaJoin> dTJ=joins_.obtener(itT1.Siguiente());
				typename Lista<NombreTabla>::Iterador itT2=tablas_.CrearIt();	
				while(itT2.HaySiguiente()){
				if(dTJ.definido(itT2.Siguiente())){
					tuplaJoin tJ=dTJ.obtener(itT2.Siguiente());
				//	ELIMINAR(tJ);
					dTJ.borrar(itT2.Siguiente());
					}
				itT2.Avanzar();	
				}
			joins_.borrar(itT1.Siguiente());		
			}
			itT1.Avanzar();
		}
		
	typename Lista<NombreTabla>::Iterador itT=tablas_.CrearIt();
	while(itT.HaySiguiente()){
		tabla t=tablasPuntero.obtener(itT.Siguiente());
	//	ELIMINAR(t);
		itT.Avanzar();
		tablasPuntero.borrar(itT.Anterior());		
		}
	typename Lista<NombreTabla>::Iterador it=tablas_.CrearIt();
	while(it.HaySiguiente()){
		it.Avanzar();
		it.EliminarAnterior();
		}
}
	
void BD::agregarTabla(tabla t){
	tablas_.AgregarAtras(t.nombre());
	tablasPuntero.definir(t.nombre(),t);
	if(tablas_.Longitud()==1){
		tablaMax=t.nombre();
		}
	else{
		if(t.cantDeAccesos()> dameTabla(tablaMaxima())->cantDeAccesos()){
			tablaMax=t.nombre();
			}
		}	
	}
	
void BD::insertarEntrada(Registro r, NombreTabla s){
	tabla* t=dameTabla(s);
	t->agregarRegistro(r);
	tabla* maxima=dameTabla(tablaMaxima());
	if( t->cantDeAccesos()> maxima->cantDeAccesos()){
		tablaMax=s;
		}
	typename::Lista<NombreTabla>::Iterador it=tablas();
	while(it.HaySiguiente()){
		if(hayJoin(s,it.Siguiente())){
			dicT<tuplaJoin> dT=joins_.obtener(s);
			tuplaJoin tJ=dT.obtener(it.Siguiente());
			typename::Lista<modificaciones>::Iterador modif= tJ.mod_.CrearIt();
			modificaciones m=modificaciones(true,r);
			modif.AgregarComoSiguiente(m);
			}
		if(hayJoin(it.Siguiente(),s)){
			dicT<tuplaJoin> dT=joins_.obtener(it.Siguiente());
			tuplaJoin tJ=dT.obtener(s);
			typename::Lista<modificaciones>::Iterador modif= tJ.mod_.CrearIt();
			modificaciones m=modificaciones(true,r);
			modif.AgregarComoSiguiente(m);
			}
		it.Avanzar();
		}
	}	
	
void BD::borrar(Registro r, const NombreTabla s){
	tabla* t=dameTabla(s);
	t->borrarRegistro(r);
	typename::Lista<NombreTabla>::Iterador it=tablas();
	while(it.HaySiguiente()){
	if(hayJoin(s,it.Siguiente())){
			dicT<tuplaJoin> dT=joins_.obtener(s);
			tuplaJoin tJ=dT.obtener(it.Siguiente());
			typename::Lista<modificaciones>::Iterador modif= tJ.mod_.CrearIt();
			modificaciones m=modificaciones(false,r);
			modif.AgregarComoSiguiente(m);
			}
		if(hayJoin(it.Siguiente(),s)){
			dicT<tuplaJoin> dT=joins_.obtener(it.Siguiente());
			tuplaJoin tJ=dT.obtener(s);
			typename::Lista<modificaciones>::Iterador modif= tJ.mod_.CrearIt();
			modificaciones m=modificaciones(false,r);
			modif.AgregarComoSiguiente(m);
			}
		it.Avanzar();
		}
	if(tablaMaxima()!=s){
		if(dameTabla(tablaMaxima())->cantDeAccesos() < dameTabla(s)->cantDeAccesos()){
			tablaMax=s;
		}
	}	
}
	
typename::Lista<Registro>::Iterador BD::generarVistaJoin(NombreTabla s1,NombreTabla s2, NombreCampo c){
	String j="Join";
	tabla* t1=dameTabla(s1);
	tabla* t2=dameTabla(s2);
	Registro columnas;
	crearCamposTablaJoin(columnas,t1->campos(),*t1);
	crearCamposTablaJoin(columnas,t2->campos(),*t2);
	Conj<NombreCampo> clave;
	clave.AgregarRapido(c);
	tabla j1=tabla();
	j1.nuevaTabla(j,columnas,clave);
	
	if(!joins_.definido(s1)){
		dicT<tuplaJoin> dicTJ;
		joins_.definir(s1,dicTJ);
	}
	tuplaJoin t=tuplaJoin(c,j1);
	joins_.obtener(s1).definir(s2,t);
	
	tabla* nuevojoin= &joins_.obtener(s1).obtener(s2).join_;
	(*nuevojoin).indexar(c);
	bool campoJoinIndexadoT1=pertenece(c,t1->indices());
	bool campoJoinIndexadoT2=pertenece(c,t2->indices());
	if(campoJoinIndexadoT1 && campoJoinIndexadoT2){
		if(t1->tipoCampo(c)){
			dicA<Nat,Lista<estrAux> >* columnaT2=t2->dameColumnaNat();
			typename Lista<Registro>::Iterador regis=t1->registros().CrearIt();
			Lista<Registro> registt;
			while(regis.HaySiguiente()){
				Registro r;
				copiarCampos(campos(regis.Siguiente()),r,regis.Siguiente());
				registt.AgregarAtras(r);
			}
			generarRegistrosJoinN(registt,*columnaT2,c,(*nuevojoin));
		}
		else{
			dicT<Lista<estrAux> >* columnaT2=t2->dameColumnaString();
			typename Lista<Registro>::Iterador regis=t1->registros().CrearIt();
			Lista<Registro> registt;
			while(regis.HaySiguiente()){
				Registro r;
				copiarCampos(campos(regis.Siguiente()),r,regis.Siguiente());
				registt.AgregarAtras(r);
			}
			generarRegistrosJoinT(registt, *columnaT2,c,(*nuevojoin));
		}
		}
	else{
		typename::Lista<Registro>::Iterador it=t1->registros().CrearIt();
		while(it.HaySiguiente()){
			typename::Lista<Registro>::Iterador it2=t2->registros().CrearIt();
			while(it2.HaySiguiente()){
				if(it.Siguiente().Significado(c) == it2.Siguiente().Significado(c)){
					Registro r1=Registro(it.Siguiente());
					Registro r2=Registro(it2.Siguiente());
					Registro rMergeado=merge(r1,r2);
					nuevojoin->agregarRegistro(rMergeado);
				}
				it2.Avanzar();
			}
			it.Avanzar();
		}
	}
	typename Lista<Registro>::Iterador itRegistros=(*nuevojoin).registros().CrearIt();
	return itRegistros;
}	
	
void BD::borrarJoin(NombreTabla s1, NombreTabla s2){
	dicT<tuplaJoin> aux=joins_.obtener(s1);
	aux.borrar(s2);
	if(aux.esVacio()) joins_.borrar(s1);
	}	

typename::Lista<NombreTabla>::Iterador BD::tablas(){
	typename::Lista<NombreTabla>::Iterador res=tablas_.CrearIt();
	return res;
	}
	
tabla* BD::dameTabla(NombreTabla s){
	tabla* res=&tablasPuntero.obtener(s);
	return res;
	}	
	
bool BD::hayJoin(NombreTabla s1,NombreTabla s2){
	bool res=joins_.definido(s1);
	if(res){
		res=joins_.obtener(s1).definido(s2);
		}
	return res;	
	}	
NombreCampo BD::campoJoin(NombreTabla s1,NombreTabla s2){
	dicT<tuplaJoin> aux=joins_.obtener(s1);
	tuplaJoin tj=aux.obtener(s2);
	NombreCampo res=tj.campoJ_;
	return res;
	}	
	
typename::Lista<Registro>::Iterador BD::registros(NombreTabla s){
	tabla* t = dameTabla(s);
	typename::Lista<Registro>::Iterador res=t->registros().CrearIt();
	return res;
	}	
/*	
typename::Lista<Registro>::Iterador BD::vistaJoin(NombreTabla s1, NombreTabla s2){
	tabla &t1=dameTabla(s1);
	tabla &t2=dameTabla(s2);
	bool campoJoinIndexadoT1=pertenece((*t1).indices(),c);
	bool campoJoinIndexadoT2=pertenece((*t2).indices(),c);
	Lista<modificaciones> modif=joins_.obtener(s1).obtener(s2).mod_.CrearIt();
	tabla join=joins_.obtener(s1).obtener(s2).join_;
	while(modif.HaySiguiente()){
		bool seAgrego=modif.Siguiente().seAgrego_;
		if(seAgrego){
			Registro registroAgregado=modif.Siguiente().reg_;
			if(campoJoinIndexadoT1 && campoJoinIndexadoT2){
				AUXILIARES PARA NAT Y STRING
			}
		}
	}
	
}
*/	
Nat BD::cantDeAccesos(NombreTabla s){
	tabla* t=dameTabla(s);
	Nat res=t->cantDeAccesos();
	return res;
	}	
	
NombreTabla BD::tablaMaxima(){
	NombreTabla res=tablaMax;
	return res;
	}	
	
//Lista<Registro> BD::buscar(NombreTabla s, Registro criterio){}	
#endif
