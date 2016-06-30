#ifndef REGISTRO_H
#define REGISTRO_H

#include "Conj.h"
#include "dato.h"
#include "Tipos.h"


#include <string>
#include <iostream>

using namespace aed2;
using namespace std;

class Registro{
public:

	 struct Elem;
    struct const_Elem;

	class Iterador;
    class const_Iterador;

    Registro();
    Registro(const Registro& otro);
    Registro& operator=(const Registro& otro);

    Iterador Definir(const NombreCampo& clave, const dato& significado);
    Iterador DefinirRapido(const NombreCampo& clave, const dato& significado);

    bool Definido(const NombreCampo& clave) const;
    const dato& Significado(const NombreCampo& clave) const;
    dato& Significado(const NombreCampo& clave);
    void Borrar(const NombreCampo& clave);
    Nat CantClaves() const;
    Iterador CrearIt();
    const_Iterador CrearIt() const;

    //Estas funciones son utiles para saber si algo esta definido
    //y ver cual es su signficado, sin recorrer dos veces.
    Iterador Buscar(const NombreCampo&);
    const_Iterador Buscar(const NombreCampo&) const;
    Conj<NombreCampo> campos();
	void copiarCampos(Conj<NombreCampo> c, Registro r2);
	void mergear(Registro&);

    class Iterador
    {
      public:

        Iterador();

        Iterador(const typename Registro::Iterador& otro);

        Iterador& operator = (const typename Registro::Iterador& otro);

        bool operator == (const typename Registro::Iterador&) const;

        bool HaySiguiente() const;
        bool HayAnterior() const;
        const NombreCampo& SiguienteClave() const;
        dato& SiguienteSignificado();
        const NombreCampo& AnteriorClave() const;
        dato& AnteriorSignificado();
        Elem Siguiente();
        Elem Anterior();
        void Avanzar();
        void Retroceder();
        void EliminarSiguiente();
        void EliminarAnterior();

      private:

        typename Lista<NombreCampo>::Iterador it_claves_;
        typename Lista<dato>::Iterador it_significados_;

        Iterador(Registro* d);

        friend typename Registro::Iterador Registro::CrearIt();
        friend class Registro::const_Iterador;
    };

    class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename Registro::Iterador& otro);

        const_Iterador(const typename Registro::const_Iterador& otro);

        const_Iterador& operator = (const typename Registro::const_Iterador& otro);

        bool operator==(const typename Registro::const_Iterador&) const;

        bool HaySiguiente() const;
        bool HayAnterior() const;
        const NombreCampo& SiguienteClave() const;
        const dato& SiguienteSignificado() const;
        const NombreCampo& AnteriorClave() const;
        const dato& AnteriorSignificado() const;
        const_Elem Siguiente() const;
        const_Elem Anterior() const;
        void Avanzar();
        void Retroceder();

    private:

        typename Lista<NombreCampo>::const_Iterador it_claves_;
        typename Lista<dato>::const_Iterador it_significados_;

        const_Iterador(const Registro* d);

        friend typename Registro::const_Iterador Registro::CrearIt() const;
    };

    struct Elem
    {
      public:

        const NombreCampo& clave;
        dato& significado;

        Elem(const NombreCampo& c, dato& s) : clave(c), significado(s) {}
        //Para sacar esto de aca, necesitariamos definir rasgos y otras yerbas
        //Lamentablemente, sino C++ no reconoce bien los tipos

       // friend std::ostream& operator<<(std::ostream& os, const Registro::Elem& e) {
        //  return os << e.clave << ":" << e.significado;
        

      private:

        typename Registro::Elem& operator=(const Registro::Elem&);
    };

    struct const_Elem
    {
      public:

        const NombreCampo& clave;
        const dato& significado;

        const_Elem(const NombreCampo& c, const dato& s) : clave(c), significado(s) {}

        //Para sacar esto de aca, necesitariamos definir rasgos y otras yerbas
        //Lamentablemente, sino C++ no reconoce bien los tipos
       // friend std::ostream& operator << (std::ostream& os, const Registro::const_Elem& e) {
         // return os << e.clave << ":" << e.significado;
        

      private:

        typename Registro::const_Elem& operator = (const Registro::const_Elem&);
    };

	private:

   Lista<NombreCampo> claves_;
    Lista<dato> significados_;
	//AUXILIARES
	
	bool coincidenTodos(Registro& r1, Conj<NombreCampo>& c, Registro& r2){
	bool res=true;
	if(!c.EsVacio()){
		typename::Conj<NombreCampo>::Iterador it=c.CrearIt();
		while(it.HaySiguiente() && res==true){
			if(r1.Significado(it.Siguiente()).tipo() != r2.Significado(it.Siguiente()).tipo()){
				res=false;
				}
			else{
				if(r1.Significado(it.Siguiente()).tipo()){
					if(r1.Significado(it.Siguiente()).valorNat() != r2.Significado(it.Siguiente()).valorNat()){res=false;}
					}
				else{
					if(r1.Significado(it.Siguiente()).valorString() != r2.Significado(it.Siguiente()).valorString()){res=false;}
					}	
				}
		
			it.Avanzar();	
			}		
		}
	return res;	
}

	bool borrar(Registro crit, Registro reg){
	bool res=true;
	Conj<NombreCampo> c=crit.campos();
	res=coincidenTodos(crit, c, reg);
	return res;
}

};


//std::ostream& operator << (std::ostream &os, const Dicc<NombreCampo,S>& d);


bool operator == (const Registro& d1, const Registro& d2);

  // Implementacion Dicc


Registro::Registro()
{}


Registro::Registro(const Registro& otro)
  : claves_(otro.claves_), significados_(otro.significados_)
{}


Registro& Registro::operator = (const Registro& otro)
{
  claves_ = otro.claves_;
  significados_ = otro.significados_;

  return *this;
}


typename Registro::Iterador Registro::Definir(const NombreCampo& clave, const dato& significado)
{
  Iterador it = Buscar(clave);

  if(it.HaySiguiente()) {
    it.SiguienteSignificado() = significado;
  } else {
    it = DefinirRapido(clave, significado);
  }

  return it;
}


typename Registro::Iterador Registro::DefinirRapido(const NombreCampo& clave, const dato& significado)
{
  #ifdef DEBUG
  assert( not Definido(clave) );
  #endif

  claves_.AgregarAdelante(clave);
  significados_.AgregarAdelante(significado);

  return CrearIt();
}


bool Registro::Definido(const NombreCampo& clave) const
{
  return Buscar(clave).HaySiguiente();
}



const dato& Registro::Significado(const NombreCampo& clave)const
{
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  return Buscar(clave).SiguienteSignificado();
}


dato& Registro::Significado(const NombreCampo& clave)
{
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  return Buscar(clave).SiguienteSignificado();
}


void Registro::Borrar(const NombreCampo& clave)
{
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  Buscar(clave).EliminarSiguiente();
}


Nat Registro::CantClaves() const
{
  return claves_.Longitud();
}


typename Registro::Iterador Registro::CrearIt()
{
  return Iterador(this);
}


typename Registro::const_Iterador Registro::CrearIt() const
{
  return const_Iterador(this);
}

  // Implementacion Iterador


Registro::Iterador::Iterador()
{}


Registro::Iterador::Iterador(const typename Registro::Iterador& otro)
: it_claves_(otro.it_claves_), it_significados_(otro.it_significados_)
{}


typename Registro::Iterador& Registro::Iterador::operator = (const typename Registro::Iterador& otro)
{
  it_claves_ = otro.it_claves_;
  it_significados_ = otro.it_significados_;

  return *this;
}


bool Registro::Iterador::HaySiguiente() const
{
  return it_claves_.HaySiguiente();
}


bool Registro::Iterador::HayAnterior() const
{
  return it_claves_.HayAnterior();
}


const NombreCampo& Registro::Iterador::SiguienteClave() const
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  return it_claves_.Siguiente();
}


dato& Registro::Iterador::SiguienteSignificado()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return it_significados_.Siguiente();
}


typename Registro::Elem Registro::Iterador::Siguiente()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return Elem(SiguienteClave(), SiguienteSignificado());
}


const NombreCampo& Registro::Iterador::AnteriorClave() const
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return it_claves_.Anterior();
}


dato& Registro::Iterador::AnteriorSignificado()
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  return it_significados_.Anterior();
}


typename Registro::Elem Registro::Iterador::Anterior()
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  return Elem(AnteriorClave(), AnteriorSignificado());
}


void Registro::Iterador::Avanzar()
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  it_claves_.Avanzar();
  it_significados_.Avanzar();
}


void Registro::Iterador::Retroceder()
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  it_claves_.Retroceder();
  it_significados_.Retroceder();
}


Registro::Iterador::Iterador(Registro* d)
: it_claves_(d->claves_.CrearIt()), it_significados_(d->significados_.CrearIt())
{}


void Registro::Iterador::EliminarSiguiente()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  it_claves_.EliminarSiguiente();
  it_significados_.EliminarSiguiente();
}


void Registro::Iterador::EliminarAnterior()
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  it_claves_.EliminarAnterior();
  it_significados_.EliminarAnterior();
}

  // Implementacion const_Iterador


Registro::const_Iterador::const_Iterador()
{}


Registro::const_Iterador::const_Iterador(const typename Registro::Iterador& otro)
  : it_claves_(otro.it_claves_), it_significados_(otro.it_significados_)
{}


Registro::const_Iterador::const_Iterador(const typename Registro::const_Iterador& otro)
  : it_claves_(otro.it_claves_), it_significados_(otro.it_significados_)
{}


typename Registro::const_Iterador& Registro::const_Iterador::operator=(const typename Registro::const_Iterador& otro)
{
  it_claves_ = otro.it_claves_;
  it_significados_ = otro.it_significados_;

  return *this;
}


bool Registro::const_Iterador::HaySiguiente() const
{
  return it_claves_.HaySiguiente();
}


bool Registro::const_Iterador::HayAnterior() const
{
  return it_claves_.HayAnterior();
}


const NombreCampo& Registro::const_Iterador::SiguienteClave() const
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  return it_claves_.Siguiente();
}


const dato& Registro::const_Iterador::SiguienteSignificado() const
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  return it_significados_.Siguiente();
}


typename Registro::const_Elem Registro::const_Iterador::Siguiente() const
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return const_Elem(SiguienteClave(), SiguienteSignificado());
}


const NombreCampo& Registro::const_Iterador::AnteriorClave() const
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return it_claves_.Anterior();
}


const dato& Registro::const_Iterador::AnteriorSignificado() const
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  return it_significados_.Anterior();
}


typename Registro::const_Elem Registro::const_Iterador::Anterior() const
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return const_Elem(AnteriorClave(), AnteriorSignificado());
}


void Registro::const_Iterador::Avanzar()
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  it_claves_.Avanzar();
  it_significados_.Avanzar();
}


void Registro::const_Iterador::Retroceder()
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  it_claves_.Retroceder();
  it_significados_.Retroceder();
}


Registro::const_Iterador::const_Iterador(const Registro* d)
: it_claves_(d->claves_.CrearIt()), it_significados_(d->significados_.CrearIt())
{}


bool Registro::const_Iterador::operator == (const typename Registro::const_Iterador& otro) const
{
  return it_claves_ == otro.it_claves_ && it_significados_ == otro.it_significados_;
}


bool Registro::Iterador::operator == (const typename Registro::Iterador& otro) const
{
  return it_claves_ == otro.it_claves_ && it_significados_ == otro.it_significados_;
}

  ///Funciones auxiliares


typename Registro::Iterador Registro::Buscar(const NombreCampo& clave)
{
  typename Registro::Iterador it = CrearIt();
  while(it.HaySiguiente() && !(it.SiguienteClave() == clave)){
    it.Avanzar();
  }
  return it;
}


typename Registro::const_Iterador Registro::Buscar(const NombreCampo& clave) const
{
  typename Registro::const_Iterador it = CrearIt();
  while(it.HaySiguiente() && !(it.SiguienteClave() == clave)){
      it.Avanzar();
  }
  return it;
}



bool operator == (const Registro& d1, const Registro& d2)
{
  bool retval = d1.CantClaves() == d2.CantClaves();
  typename Registro::const_Iterador it1 = d1.CrearIt();
  while(retval and it1.HaySiguiente()){
    typename Registro::const_Iterador it2 = d2.Buscar(it1.SiguienteClave());
    retval = it2.HaySiguiente() and it1.SiguienteSignificado() == it2.SiguienteSignificado();
    it1.Avanzar();
  }
  return retval;
}





void Registro::mergear(Registro& r2){
	typename Registro::Iterador itR2= r2.CrearIt();

	while(itR2.HaySiguiente()){
		if(!(Definido(itR2.SiguienteClave()))) 
			Definir(itR2.SiguienteClave(), itR2.SiguienteSignificado());
		itR2.Avanzar();
	}	
}

Conj<NombreCampo> Registro::campos(){
	Conj<NombreCampo> res;
	typename Registro::Iterador itR1= CrearIt();
	while(itR1.HaySiguiente()){
		res.AgregarRapido(itR1.SiguienteClave());
		itR1.Avanzar();
	}
	return res;
}
	
void Registro::copiarCampos(Conj<NombreCampo> c, Registro r2){
	typename::Conj<NombreCampo>::Iterador it=c.CrearIt();
	while(it.HaySiguiente()){
		if(!Definido(it.Siguiente())){
			Definir(it.Siguiente(), r2.Significado(it.Siguiente()));
			}
		it.Avanzar();	
		} 
	}
	
#endif
