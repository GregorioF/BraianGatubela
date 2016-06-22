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
		bool SeAgrego_;
		registro reg_;		
	};
	struct TuplaJoin
	{
		NombreCampo CampoJ_;
		Lista<Modificaciones> Mod_;
		tabla Join_;		
	};
	
	BD();
	
	void AgregarTabla(const tabla);	
	
	~BD();  
	
	void InsertarEntrada(const Registro, const String);
	
	void Borrar(const registro, const String);
	
	typename::Lista<registro>::Iterador GenerarVistaJoin(String, String, NombreCampo); 
	
	void BorrarJoin(String, String);
	
	typename::Lista<tabla>::Iterador Tablas();
	
	tabla DameTabla();
	
	bool HayJoin(String, String);
	
	NombreCampo CampoJoin(String, String); 
	
	typename::Lista<registro>::Iterador Registros(String);
	
	typename::Lista<registro>::Iterador VistaJoin(String, String);
	
	Nat CantidadDeAccesos(String);
	
	String TablaMaxima();
	
	Lista<registro> Buscar(const registro, String);
	
		
private:
	
	Lista<tabla> tablas_;
	dicT<String,tabla> TablasPuntero;
	dicT<String,dicT<String,TuplaJoin> > joins;
	String TablaMax;
	
	///////////////////////////////////////////////
	//FUNCIONES AUXILIARES
	///////////////////////////////////////////////
	registro Merge(registro r1, registro r2){
		registro res=registro(r1);
		typename::Lista<registro>::Iterador it=r2.CrearIt();
		while(it.HaySiguiente()){
			if(!res.Definido(it.SiguienteClave())) res.DefinirRapido(it.SiguienteClave(),it.SiguienteSignificado());
			it.Avanzar();
			}
		return res;	
	}
	
	void CrearCamposTablaJoin(registro r, Lista<NombreCampo> c, tabla t){
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
	
	bool Pertenece(NombreCampo c, Lista<NombreCampo> cc){
		typename::Lista<NombreCampo>::Iterador it=cc.CrearIt();
		bool res=false;
		while(it.HaySiguiente()){
			if(it.Siguiente()==c) res=true;
			it.Avanzar();
			}
		return res;	
		}
		
	void GenerarRegistrosJoinT(Lista<registro> cr, dicT<String,estrAux> CT2, NombreCampo campoJoin, tabla Join){
		typename::Lista<registro>::Iterador it=cr.CrearIt();
		while(it.HaySiguiente()){
			registro RT1=it.Siguiente();
			String ValorCampoJoin= (RT1.Significado(campoJoin)).valorString;
			if(CT2.Definido(ValorCampoJoin)){
				registro RT2=CT2.DameRegistro(valorCampoJoin);
				registro Rmergeado=Merge(RT1,RT2); //X COPIA AMBOS!
				Join.AgregarRegistro(Rmergeado);
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
	
void BD::AgregarTabla(Tabla t){
	tablas.AgregarAtras(t.nombre);
	TablasPuntero.Definir(t.nombre,t);
	if(Longitud(tablas)==1){
		TablaMax=t.nombre;
		}
	else{
		if(t.CantidadDeAccesos()>(DameTabla(TablaMaxima())).CantidadDeAccesos){
			TablaMax=t.nombre
			}
		}	
	}
	
void BD::InsertarEntrada(registro r, String s){
	tabla t=DameTabla(s);
	t.AgregarRegistro(r);
	tabla Maxima=DameTabla(TablaMaxima());
	if(t.CantidadDeAccesos()>Maxima.CantidadDeAccesos()){
		TablaMax=s;
		}
	typename::Lista<tabla>::Iterador it=Tablas();
	while(it.HaySiguiente()){
		if(HayJoin(s,it.Siguiente())){
			typename::Lista<Modificaciones>::Iterador modif= (((joins.Significado(s)).Significado(it.Siguiente)).Mod_).CrearIt()
			}
		if(HayJoin(it.Siguiente(),s)){
			
			}	
		}
	
	}	
	
void BD::Borrar(const registro r, const String s){
	tabla t=DameTabla(s);
	BorrarRegistro(r);
	typename::Lista<tabla>::Iterador it=Tablas();
	while(it.HaySiguiente()){
		if(HayJoin(s,it.Siguiente())){
			
			}
		if(HayJoin(it.Siguiente(),s)){
			
			}
		}
	}
	
typename::Lista<registro>::Iterador BD::GenerarVistaJoin(String s1,String s2){}	
	
void BD::BorrarJoin(String s1, String s2){
	dicT<String,TuplaJoin> aux=joins.Significado(s1);
	aux.Borrar(s2);
	if(aux.Vacio?()) joins.Borrar(s1);
	}	

typename::Lista<tabla>::Iterador BD::Tablas(){
	typename::Lista<tabla>::Iterador res=tablas_.CrearIt();
	return res;
	}
	
tabla BD::DameTabla(String s){
	tabla res=TablasPuntero.Significado(s);
	return res;
	}	
	
bool BD::HayJoin(String s1,String s2){
	bool res=joins.Definido(s1);
	if(res){
		res=joins.Significado(s1).Definido(s2);
		}
	return res;	
	}	
NombreCampo BD::CampoJoin(String s1,String s2){
	dicT<String,TuplaJoin> aux=joins.Significado(s1);
	TuplaJoin tj=aux.Significado(s2);
	NombreCampo res=Tj.CampoJ_;
	return res;
	}	
	
typename::Lista<registro>::Iterador BD::Registros(String s){
	tabla t=DameTabla(s);
	typename::Lista<registro>::Iterador res=t.Registros.CrearIt()
	return res;
	}	
	
typename::Lista<registro>::Iterador BD::VistaJoin(String s1, String s2){}
	
Nat BD::CantidadDeAccesos(String s){
	tabla t=DameTabla(s);
	Nat res=t.CantidadDeAccesos();
	return res;
	}	
	
String BD::TablaMaxima(){
	String res=TablaMax;
	}	
	
Lista<registro> BD::Buscar(String s, registro criterio){}	
#endif
