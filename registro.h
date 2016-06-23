#ifndef REGISTRO_H
#define REGISTRO_H

#include "Conj.h"
#include "../Driver.h"

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

#endif