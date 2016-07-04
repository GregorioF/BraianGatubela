#ifndef BD_H
#define BD_H

#include "Dicc.h"
#include "dicT.h"
#include "dicA.h"
#include "tabla.h"
#include <iostream>
#include "par.h"


using namespace aed2;
using namespace std;


class BD{
public:
	//////////////////////////////////////////////////////////////////////////
	BD();
	//////////////////////////////////////////////////////////////////////////
	void agregarTabla(tabla);	
	//////////////////////////////////////////////////////////////////////////
	~BD();  
	//////////////////////////////////////////////////////////////////////////
	void insertarEntrada(const registro, const NombreTabla);
	//////////////////////////////////////////////////////////////////////////
	void borrar(registro, const NombreTabla);
	//////////////////////////////////////////////////////////////////////////
	typename::Lista<registro>::Iterador generarVistaJoin(NombreTabla, NombreTabla, NombreCampo); 
	//////////////////////////////////////////////////////////////////////////
	void borrarJoin(NombreTabla, NombreTabla);
	//////////////////////////////////////////////////////////////////////////
	typename::Lista<NombreTabla>::const_Iterador tablas() const;
	//////////////////////////////////////////////////////////////////////////
	tabla* dameTabla(NombreTabla) const;
	//////////////////////////////////////////////////////////////////////////
	bool hayJoin(NombreTabla, NombreTabla) const;
	//////////////////////////////////////////////////////////////////////////
	NombreCampo campoJoin(NombreTabla, NombreTabla) const; 
	//////////////////////////////////////////////////////////////////////////
	typename::Lista<registro>::Iterador registros(NombreTabla);
	//////////////////////////////////////////////////////////////////////////
	typename::Lista<registro>::Iterador vistaJoin(NombreTabla, NombreTabla)const;
	//////////////////////////////////////////////////////////////////////////
	Nat cantDeAccesos(NombreTabla) const;
	//////////////////////////////////////////////////////////////////////////
	NombreTabla tablaMaxima() const;
	//////////////////////////////////////////////////////////////////////////
	Lista<registro> buscar(const registro, NombreTabla) const;
	
		
private:
	
	
	struct tuplaJoin
	{
		tuplaJoin(NombreCampo c, tabla j){
		campoJ_=c;
		mod_=Lista< par<bool,registro> >();
		join_=j;			
		}
		tuplaJoin(){}	
		~tuplaJoin(){}
		
		NombreCampo campoJ_;
		Lista< par<bool, registro> > mod_;
		tabla join_;		
		
	};
	
	Lista<NombreTabla> tablas_;
	dicT<tabla> tablasPuntero;
	dicT<dicT<tuplaJoin> > joins_;
	NombreTabla tablaMax;
	









	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//FUNCIONES AUXILIARES--FUNCIONES AUXILIARES--FUNCIONES AUXILIARES--FUNCIONES AUXILIARES--FUNCIONES AUXILIARES
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*	Registro merge(Registro r1, Registro r2){
		Registro res=Registro(r1);
		typename::Registro::Iterador it=r2.CrearIt();
		while(it.HaySiguiente()){
			if(!res.Definido(it.SiguienteClave())) res.DefinirRapido(it.SiguienteClave(),it.SiguienteSignificado());
			it.Avanzar();
			}
		return res;	
	}*/
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	void crearCamposTablaJoin(registro& r, Conj<NombreCampo> c, tabla* t){
		typename::Conj<NombreCampo>::Iterador it=c.CrearIt();	
			
		while(it.HaySiguiente()){
			
			if(t->tipoCampo(it.Siguiente()) == NAT){
				Nat n=0;
				dato d;
				d.nuevoDatoNat(n);
				if(!r.Definido(it.Siguiente())){
				r.DefinirRapido(it.Siguiente(),d);
				
				}
			}
			else{
				String s;
				dato d;
				d.nuevoDatoString(s);
				if(!r.Definido(it.Siguiente())){
				r.DefinirRapido(it.Siguiente(),d);
	
				}
			}
			it.Avanzar();

		}				
	}
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	bool pertenece(NombreCampo c, Conj<NombreCampo> cc) const{
		typename::Conj<NombreCampo>::Iterador it=cc.CrearIt();
		bool res=false;
		while(it.HaySiguiente()){
			if(it.Siguiente()==c) res=true;
			it.Avanzar();
			}
		return res;	
		}
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	bool perteneceR(registro r, Lista<registro> cr){
		typename::Lista<registro>::Iterador it=cr.CrearIt();
		bool res=false;
		while(it.HaySiguiente()){
			if(it.Siguiente()==r) res=true;
			it.Avanzar();
			}
		return res;	
		}	
		
};









////////////////////////////////////////////////////////////////////////////////////
//FUNCIONES BD--FUNCIONES BD--FUNCIONES BD--FUNCIONES BD--FUNCIONES BD--FUNCIONES BD
////////////////////////////////////////////////////////////////////////////////////

BD::BD(){}
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
BD::~BD(){}
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
void BD::insertarEntrada(registro r, NombreTabla s){
	tabla* t=dameTabla(s);
	t->agregarRegistro(r);
	tabla* maxima=dameTabla(tablaMaxima());
	if( t->cantDeAccesos()> maxima->cantDeAccesos()){
		tablaMax=s;
		}
	typename::Lista<NombreTabla>::const_Iterador it=tablas();
	while(it.HaySiguiente()){
		if(hayJoin(s,it.Siguiente())){
			dicT<tuplaJoin>* dT=&joins_.obtener(s);
			tuplaJoin* tJ=&dT->obtener(it.Siguiente());
			typename::Lista<par<bool,registro> >::Iterador modif= tJ->mod_.CrearIt();
			par<bool,registro> m;
			m.make_par(true,r);
			modif.AgregarComoSiguiente(m);
			}
		if(hayJoin(it.Siguiente(),s)){
			dicT<tuplaJoin>* dT=&joins_.obtener(it.Siguiente());
			tuplaJoin* tJ=&dT->obtener(s);
			typename::Lista<par<bool,registro> >::Iterador modif= tJ->mod_.CrearIt();
			par<bool,registro>  m;
			m.make_par(true,r);
			modif.AgregarComoSiguiente(m);
			}
		it.Avanzar();
		}
	}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
void BD::borrar(registro r, const NombreTabla s){
	tabla* t=dameTabla(s);
	t->borrarRegistro(r);
	typename::Lista<NombreTabla>::const_Iterador it=tablas();
	while(it.HaySiguiente()){
	if(hayJoin(s,it.Siguiente())){
			dicT<tuplaJoin>* dT=&joins_.obtener(s);
			tuplaJoin* tJ=&dT->obtener(it.Siguiente());
			typename::Lista<par<bool,registro> >::Iterador modif= tJ->mod_.CrearIt();
			par<bool,registro>  m;
			m.make_par(false,r);
			modif.AgregarComoSiguiente(m);
			}
		if(hayJoin(it.Siguiente(),s)){
			dicT<tuplaJoin>* dT=&joins_.obtener(it.Siguiente());
			tuplaJoin* tJ=&dT->obtener(s);
			typename::Lista<par<bool,registro> >::Iterador modif= tJ->mod_.CrearIt();
			par<bool,registro>  m;
			m.make_par(false,r);
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
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
typename::Lista<registro>::Iterador BD::generarVistaJoin(NombreTabla s1,NombreTabla s2, NombreCampo c){
	
	String j="Join";
	tabla* t1=dameTabla(s1);
	tabla* t2=dameTabla(s2);
	
	registro columnas;
	
	Conj<NombreCampo> c1=t1->campos();
	Conj<NombreCampo> c2=t2->campos();
	
	crearCamposTablaJoin(columnas,c1,t1);
	
	crearCamposTablaJoin(columnas,c2,t2);
	
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
	
	nuevojoin->indexar(c);
	
	bool campoJoinIndexadoT1=pertenece(c,t1->indices());
	bool campoJoinIndexadoT2=pertenece(c,t2->indices());
	
	if(campoJoinIndexadoT1 && campoJoinIndexadoT2){		
		t1->AuxiliarGVJ(t2, nuevojoin, c);
		}
	else{
		Lista<registro> listReg=t1->registros();
		typename::Lista<registro>::Iterador it=listReg.CrearIt();
		while(it.HaySiguiente()){
			
			Lista<registro> listReg2=t2->registros();
					
			typename::Lista<registro>::Iterador it2=listReg2.CrearIt();
					
			while(it2.HaySiguiente()){				
				if(it.Siguiente().Significado(c) == it2.Siguiente().Significado(c)){
					registro r1(it.Siguiente());
					registro r2(it2.Siguiente());
					r1.mergear(r2);
					nuevojoin->agregarRegistro(r1);
				}
				it2.Avanzar();
			}
			
			it.Avanzar();
		}
		
	}
	Lista<registro> lr=nuevojoin->registros();
	typename Lista<registro>::Iterador itRegistros=lr.CrearIt();
	return itRegistros;
	
}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
void BD::borrarJoin(NombreTabla s1, NombreTabla s2){
	dicT<tuplaJoin>* aux=&joins_.obtener(s1);
	aux->borrar(s2);
	if(aux->esVacio()) joins_.borrar(s1);
	}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
typename::Lista<NombreTabla>::const_Iterador BD::tablas() const{
	typename::Lista<NombreTabla>::const_Iterador res=tablas_.CrearIt();
	return res;
	}
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
tabla* BD::dameTabla(NombreTabla s) const{
	tabla* res=&tablasPuntero.obtener(s);
	return res;
	}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
bool BD::hayJoin(NombreTabla s1,NombreTabla s2) const{
	bool res=joins_.definido(s1);
	if(res){
		res=joins_.obtener(s1).definido(s2);
		}
	return res;	
	}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
NombreCampo BD::campoJoin(NombreTabla s1,NombreTabla s2)const{
	dicT<tuplaJoin> aux=joins_.obtener(s1);
	tuplaJoin tj=aux.obtener(s2);
	NombreCampo res=tj.campoJ_;
	return res;
	}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
typename::Lista<registro>::Iterador BD::registros(NombreTabla s){
	tabla* t = dameTabla(s);
	typename::Lista<registro>::Iterador res=t->registros().CrearIt();
	return res;
	}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
typename::Lista<registro>::Iterador BD::vistaJoin(NombreTabla s1, NombreTabla s2) const{
	
	tabla* t1=dameTabla(s1);
	tabla* t2=dameTabla(s2);
	NombreCampo c=campoJoin(s1,s2);
	bool campoJoinIndexadoT1=pertenece(c,t1->indices());
	bool campoJoinIndexadoT2=pertenece(c,t2->indices());
	Lista<par<bool, registro> > modificaciones=joins_.obtener(s1).obtener(s2).mod_;
	tabla* join= &joins_.obtener(s1).obtener(s2).join_;
	Nat i= modificaciones.Longitud();
	 
	while(i>0){
		
		typename Lista<par<bool,registro> >::Iterador modif=joins_.obtener(s1).obtener(s2).mod_.CrearIt();
		par<bool,registro> parBR=modif.Siguiente();
		bool seAgrego = parBR.first();
		if(seAgrego){
			registro registroAgregado=modif.Siguiente().second();
			if(campoJoinIndexadoT1 && campoJoinIndexadoT2){
					join->auxVJ(c, t1, t2, registroAgregado.Significado(c));
			}
			else{
				
				Lista<registro> regT1=t1->registros();
				typename Lista<registro>::Iterador it=regT1.CrearIt();
				while(it.HaySiguiente()){
					if(it.Siguiente().Significado(c) == registroAgregado.Significado(c)){
						Lista<registro> regT2=t2->registros();
						typename Lista<registro>::Iterador it2=regT2.CrearIt();
						while(it2.HaySiguiente()){
							if(it2.Siguiente().Significado(c) == registroAgregado.Significado(c)){
								registro rT1(it.Siguiente());
								registro rT2(it2.Siguiente());
								rT1.mergear(rT2);
								join->agregarRegistro(rT1);
								}
							it2.Avanzar();
							}
						}
					
					it.Avanzar();
					}
				}
		}
		else{
				registro registroABorrar=modif.Siguiente().second();
				if(join->estaValor(registroABorrar.Significado(c))){
					registro crit;
					crit.Definir(c, registroABorrar.Significado(c));
					join->borrarRegistro(crit);
				}
		 }
		modif.EliminarSiguiente();
		i--;
		
	}
	
	Lista<registro> lr=join->registros();
	typename Lista<registro>::Iterador itRegistros=lr.CrearIt();
	
	return itRegistros;
	
	}
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
Nat BD::cantDeAccesos(NombreTabla s) const{
	tabla* t=dameTabla(s);
	Nat res=t->cantDeAccesos();
	return res;
	}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
NombreTabla BD::tablaMaxima()const{
	NombreTabla res=tablaMax;
	return res;
	}	
///////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////
Lista<registro> BD::buscar(registro criterio,NombreTabla s) const{
	Lista<registro> res;
	tabla* t=dameTabla(s);
	typename registro::Iterador itCrit=criterio.CrearIt();
	bool esClave=false;
	NombreCampo criterioClave;
	if(t->indices().Cardinal()>0){
	while(itCrit.HaySiguiente()){
		NombreCampo critActual=itCrit.SiguienteClave();
		if(pertenece(critActual,t->indices()) && pertenece(critActual, t->claves())){
			esClave=true;
			criterioClave=itCrit.SiguienteClave();
		}
		itCrit.Avanzar();
	}
	}
	if(esClave){
		t->AuxBuscar(criterioClave, criterio, res);
		return res;
	}
	else{
		Lista<registro> regT(t->registros());
		return criterio.coincidencias(regT);
	}
  
 }
  
	
#endif
