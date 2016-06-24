#ifndef REGISTRO_H
#define REGISTRO_H

#include "aed2/Conj.h"
#include "Driver.cpp"

using namespace aed2;

typedef Driver::Registro Registro;
typedef Driver::Dato Dato;

//MODIFICA R1!
void mergear(Registro& r1, Registro& r2){
	typename Dicc<NombreCampo, Dato>::Iterador itR2= r2.CrearIt();

	while(itR2.HaySiguiente()){
		if(!(r1.Definido(itR2.SiguienteClave()))) 
			r1.Definir(itR2.SiguienteClave(), itR2.SiguienteSignificado());
		itR2.Avanzar();
	}	
}

Conj<NombreCampo> campos(Registro& r1){
	Conj<NombreCampo> res;
	typename Dicc<NombreCampo, Dato>::Iterador itR1= r1.CrearIt();
	while(itR1.HaySiguiente()){
		res.AgregarRapido(itR1.SiguienteClave());
		itR1.Avanzar();
	}
	return res;
}

bool coincidenTodos(Registro& r1, Conj<NombreCampo>& c, Registro& r2){
	bool res=true;
	if(!c.EsVacio()){
		typename::Conj<NombreCampo>::Iterador it=c.CrearIt();
		while(it.HaySiguiente() && res==true){
			if(r1.Significado(it.Siguiente()).tipo() != r2.Significado(it.Siguiente()).tipo()){
				res=false;
				}
			else{
				if(r1.Significado(it.Siguiente()).esNat()){
					if(r1.Significado(it.Siguiente()).dameNat() != r2.Significado(it.Siguiente()).dameNat()){res=false;}
					}
				else{
					if(r1.Significado(it.Siguiente()).dameString() != r2.Significado(it.Siguiente()).dameString()){res=false;}
					}	
				}
		
			it.Avanzar();	
			}		
		}
	return res;	
}

bool borrar(Registro crit, Registro reg){
	bool res=true;
	Conj<NombreCampo> c=campos(crit);
	res=coincidenTodos(crit, c, reg);
	return res;
}
	

void copiarCampos(Conj<NombreCampo> c, Registro& r1, Registro r2){
	typename::Conj<NombreCampo>::Iterador it=c.CrearIt();
	while(it.HaySiguiente()){
		if(!r1.Definido(it.Siguiente())){
			r1.Definir(it.Siguiente(), r2.Significado(it.Siguiente()));
			}
		it.Avanzar();	
		} 
	}
	
#endif
