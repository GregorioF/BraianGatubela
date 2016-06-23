#ifndef BD
#define BD

#include "dato.h"
#include "Conj.h"
#include "Dicc.h"
#include "dicT.h"
#include "dicA.h"
#include "Lista.h"
#include "tabla.h"
#include "registro.h"
#include <iostream>

using namespace aed2;
using namespace std;


class BD{
public:

	struct Modificaciones
	{
		Modificaciones(bool b, registro r)
			: seAgrego_(b), reg_(r){}
		bool seAgrego_;
		registro reg_;		
	};
	struct TuplaJoin
	{
		TuplaJoin(NombreCampo c, tabla j){
		campoJ_=c;
		mod_=Vacia();
		join_=j;
			
		}
		
		NombreCampo campoJ_;
		Lista<Modificaciones> mod_;
		tabla join_;		
	};
	
	BD();
	
	void agregarTabla(const tabla);	
	
	~BD();  
	
	void insertarEntrada(const registro, const NombreTabla);
	
	void borrar(const registro, const NombreTabla);
	
	typename::Lista<registro>::Iterador generarVistaJoin(NombreTabla, NombreTabla, NombreCampo); 
	
	void borrarJoin(NombreTabla, NombreTabla);
	
	typename::Lista<tabla>::Iterador tablas();
	
	tabla dameTabla();
	
	bool hayJoin(NombreTabla, NombreTabla);
	
	NombreCampo campoJoin(NombreTabla, NombreTabla); 
	
	typename::Lista<registro>::Iterador registros(NombreTabla);
	
	typename::Lista<registro>::Iterador vistaJoin(NombreTabla, NombreTabla);
	
	Nat cantidadDeAccesos(NombreTabla);
	
	NombreTabla tablaMaxima();
	
	Lista<registro> buscar(const registro, NombreTabla);
	
		
private:
	
	Lista<tabla> tablas_;
	dicT<NombreTabla,tabla> tablasPuntero;
	dicT<NombreTabla,dicT<NombreTabla,TuplaJoin> > joins_;
	NombreTabla tablaMax;
	
	///////////////////////////////////////////////
	//FUNCIONES AUXILIARES
	///////////////////////////////////////////////
	registro merge(registro r1, registro r2){
		registro res=registro(r1);
		typename::Lista<registro>::Iterador it=r2.CrearIt();
		while(it.HaySiguiente()){
			if(!res.Definido(it.SiguienteClave())) res.DefinirRapido(it.SiguienteClave(),it.SiguienteSignificado());
			it.Avanzar();
			}
		return res;	
	}
	
	void crearCamposTablaJoin(registro r, Lista<NombreCampo> c, tabla t){
		typename::Lista<NombreCampo>::Iterador it=c.CrearIt();
		while(it.HaySiguiente()){
			if(t.TipoCampo(it.Siguiente())){
				Dato d=<true,0,Vacio()>;
				if(!r.Definido(it.Siguiente())){
				r.DefinirRapido(it.Siguiente(),d);
				}
			}
			else{
				Dato d=<false,0,Vacio()>;
				if(!r.Definido(it.Siguiente())){
				r.DefinirRapido(it.Siguiente(),d);
				}
			}
			it.Avanzar();
		}				
	}
	
	bool pertenece(NombreCampo c, Lista<NombreCampo> cc){
		typename::Lista<NombreCampo>::Iterador it=cc.CrearIt();
		bool res=false;
		while(it.HaySiguiente()){
			if(it.Siguiente()==c) res=true;
			it.Avanzar();
			}
		return res;	
		}
		
	void generarRegistrosJoinT(Lista<registro> cr, dicT<String,estrAux> CT2, NombreCampo campoJoin, tabla join){
		typename::Lista<registro>::Iterador it=cr.CrearIt();
		while(it.HaySiguiente()){
			registro RT1=it.Siguiente();
			NombreTabla ValorCampoJoin= (RT1.Significado(campoJoin)).valorNombreTabla;
			if(CT2.Definido(ValorCampoJoin)){
				registro RT2=CT2.DameRegistro(valorCampoJoin);
				registro Rmergeado=Merge(RT1,RT2); //X COPIA AMBOS!
				join.agregarRegistro(Rmergeado);
				}
			it.Avanzar();	
			}
		}
		
	void generarRegistrosJoinN(Lista<registro> cr, dicA<Nat,estrAux> CT2, NombreCampo campoJoin, tabla join){
		typename::Lista<registro>::Iterador it=cr.CrearIt();
		while(it.HaySiguiente()){
			registro RT1=it.Siguiente();
			NombreTabla ValorCampoJoin= (RT1.Significado(campoJoin)).valorNombreTabla;
			if(CT2.Definido(ValorCampoJoin)){
				registro RT2=CT2.DameRegistro(valorCampoJoin);
				registro Rmergeado=Merge(RT1,RT2); //X COPIA AMBOS!
				join.agregarRegistro(Rmergeado);
				}
			it.Avanzar();	
			}
		}	
		
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

BD::BD(){
	tablas=Vacia();
	TablasPuntero=Vacio();
	joins=Vacio();
	TablaMax=Vacio();
	}
	
BD::~BD(){
	tablas=Vacia();
	TablasPuntero=Vacio();
	joins=Vacio();
	TablaMax=Vacio();
	}	
	
void BD::agregarTabla(Tabla t){
	tablas.AgregarAtras(t.nombre());
	tablasPuntero.Definir(t.nombre(),t);
	if(Longitud(tablas)==1){
		tablaMax=t.nombre();
		}
	else{
		if(t.cantidadDeAccesos()>((*dameTabla(TablaMaxima()))).cantidadDeAccesos){
			tablaMax=t.nombre();
			}
		}	
	}
	
void BD::insertarEntrada(registro r, NombreTabla s){
	tabla &t=dameTabla(s);
	t.agregarRegistro(r);
	tabla &maxima=dameTabla(tablaMaxima());
	if((*t).cantidadDeAccesos()>(*maxima).cantidadDeAccesos()){
		tablaMax=s;
		}
	typename::Lista<tabla>::Iterador it=tablas();
	while(it.HaySiguiente()){
		if(HayJoin(s,it.Siguiente())){
			typename::Lista<Modificaciones>::Iterador modif= (((joins_.obtener(s)).obtener(it.Siguiente)).mod_).CrearIt();
			Modificaciones m=Modificaciones(true,r);
			modif.AgregarComoSiguiente(m);
			}
		if(HayJoin(it.Siguiente(),s)){
			typename::Lista<Modificaciones>::Iterador modif= (((joins_.obtener(it.Siguiente)).obtener(s)).mod_).CrearIt();
			Modificaciones m=Modificaciones(true,r);
			modif.AgregarComoSiguiente(m);
			}
		it.Avanzar();
		}
	}	
	
void BD::borrar(const registro r, const NombreTabla s){
	borrarRegistro(r);
	typename::Lista<tabla>::Iterador it=tablas();
	while(it.HaySiguiente()){
	if(HayJoin(s,it.Siguiente())){
			typename::Lista<Modificaciones>::Iterador modif= (((joins_.obtener(s)).obtener(it.Siguiente)).mod_).CrearIt();
			Modificaciones m=Modificaciones(false,r);
			modif.AgregarComoSiguiente(m);
			}
		if(HayJoin(it.Siguiente(),s)){
			typename::Lista<Modificaciones>::Iterador modif= (((joins_.obtener(it.Siguiente)).obtener(s)).mod_).CrearIt();
			Modificaciones m=Modificaciones(false,r);
			modif.AgregarComoSiguiente(m);
			}
		it.Avanzar();
		}
	if(tablaMaxima()!=s){
		if(tablaMaxima().cantidadDeAccesos() < (*dameTabla(s)).cantidadDeAccesos()){
			tablaMax=s;
		}
	}	
}
	
typename::Lista<registro>::Iterador BD::generarVistaJoin(NombreTabla s1,NombreTabla s2){
	String j="Join";
	tabla &t1=dameTabla(s1);
	tabla &t2=dameTabla(s2);
	registro columnas=Vacio();
	crearCamposTablaJoin(columnas,(*t1).campos(),(*t1));
	crearCamposTablaJoin(columnas,(*t2).campos(),(*t2));
	tabla j1=nuevaTabla(j,claves(columnas),columnas);
		Lista<Modificaciones> modd=Vacia();
	if(!joins_.definido(s1)){
		joins_.definir(s1,Vacio());
	}
	TuplaJoin t=TuplaJoin(c,modd,j1);
	joins_.obtener(s1).definir(s2,t);
	}
	tabla* nuevojoin= (joins_.obtener(s1)).obtener(s2).tablaJoin_;
	(*nuevojoin).Indexar(c);
	bool campoJoinIndexadoT1=pertenece((*t1).indices(),c);
	bool campoJoinIndexadoT2=pertenece((*t2).indices(),c);
	if(campoJoinIndexadoT1 && campoJoinIndexadoT2){
		if((*t1).tipoCampo(c)){
			dicA<Nat,estrAux> columnaT2=(*t2).dameColumnaNat;
			Lista<registro> regis=Lista((*t1).registros);
			generarRegistrosJoin(regis,columnaT2,c,(*nuevojoin));
		}
		else{
			dicT<String,estrAux> columnaT2=(*t2).dameColumnaString;
			Lista<registro> regis=Lista((*t1).registros);
			generarRegistrosJoin(regis,ColumnaT2,c,(*nuevojoin));
		}
	else{
		typename::Lista<registro>::Iterador it=(*t1).registros().CrearIt();
		while(it.HaySiguiente()){
			typename::Lista<registro>::Iterador it2=(*t2).registros().CrearIt();
			while(it2.HaySiguiente()){
				if(it.Siguiente().Significado(c) == it2.Siguiente().Significado(c)){
					registro r1=registro(it.Siguiente());
					registro r2=registro(it2.Siguiente());
					(*nuevojoin).agregarRegistro(merge(r1,r2));
				}
				it2.Avanzar();
			}
			it.Avanzar();
		}
	}
}	
	
void BD::borrarJoin(NombreTabla s1, NombreTabla s2){
	dicT<NombreTabla,TuplaJoin> aux=joins_.obtener(s1);
	aux.borrar(s2);
	if(aux.Vacio?()) joins_.borrar(s1);
	}	

typename::Lista<tabla>::Iterador BD::tablas(){
	typename::Lista<tabla>::Iterador res=tablas_.CrearIt();
	return res;
	}
	
tabla& BD::dameTabla(NombreTabla s){
	tabla res=tablasPuntero.Significado(s);
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
	dicT<NombreTabla,TuplaJoin> aux=joins_.obtener(s1);
	TuplaJoin tj=aux.obtener(s2);
	NombreCampo res=tj.CampoJ_;
	return res;
	}	
	
typename::Lista<registro>::Iterador BD::registros(NombreTabla s){
	tabla &t = dameTabla(s);
	typename::Lista<registro>::Iterador res=(*t).registros.CrearIt() //fijarse si hay que desrefernciarlo o no
	return res;
	}	
	
typename::Lista<registro>::Iterador BD::vistaJoin(NombreTabla s1, NombreTabla s2){
	tabla &t1=dameTabla(s1);
	tabla &t2=dameTabla(s2);
	bool campoJoinIndexadoT1=pertenece((*t1).indices(),c);
	bool campoJoinIndexadoT2=pertenece((*t2).indices(),c);
	Lista<Modificaciones> modif=joins_.obtener(s1).obtener(s2).mod_.CrearIt();
	tabla join=joins_.obtener(s1).obtener(s2).join_;
	while(modif.HaySiguiente()){
		bool seAgrego=modif.Siguiente().seAgrego_;
		if(seAgrego){
			registro registroAgregado=modif.Siguiente().reg_;
			if(campoJoinIndexadoT1 && campoJoinIndexadoT2){
				AUXILIARES PARA NAT Y STRING
			}
		}
	}
	
}
	
Nat BD::cantidadDeAccesos(NombreTabla s){
	tabla &t=dameTabla(s);
	Nat res=(*t).cantidadDeAccesos();
	return res;
	}	
	
NombreTabla BD::tablaMaxima(){
	NombreTabla res=tablaMax;
	}	
	
Lista<registro> BD::buscar(NombreTabla s, registro criterio){}	
#endif
