#ifndef REGISTRO_H
#define REGISTRO_H

#include "Conj.h"
#include "dato.h"
#include "Tipos.h"


#include <string>
#include <iostream>

using namespace aed2;
using namespace std;

class registro{
public:

	 struct Elem;
    struct const_Elem;

	class Iterador;
    class const_Iterador;

    registro();
    registro(const registro& otro);
    registro& operator=(const registro& otro);

    Iterador Definir(const NombreCampo& clave, const dato& significado);
    Iterador DefinirRapido(const NombreCampo& clave, const dato& significado);

    bool Definido(const NombreCampo& clave) const;
    const dato& Significado(const NombreCampo& clave) const;
    dato& Significado(const NombreCampo& clave);
    void Borrar(const NombreCampo& clave);
    Nat CantClaves() const;
    Iterador CrearIt();
    const_Iterador CrearIt() const;
    void Mostrar(ostream& out) const;
    
    //Estas funciones son utiles para saber si algo esta definido
    //y ver cual es su signficado, sin recorrer dos veces.
    Iterador Buscar(const NombreCampo&);
    const_Iterador Buscar(const NombreCampo&) const;
    Conj<NombreCampo> campos();
	  void copiarCampos(Conj<NombreCampo> c, registro r2);
	  void mergear(registro&);
	  bool coincidenTodos(Conj<NombreCampo>& c, registro& r2);
	  bool borrar(registro crit);
	  Lista<registro> coincidencias(Lista<registro> cr);

    class Iterador
    {
      public:

        Iterador();

        Iterador(const typename registro::Iterador& otro);

        Iterador& operator = (const typename registro::Iterador& otro);

        bool operator == (const typename registro::Iterador&) const;

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

        Iterador(registro* d);

        friend typename registro::Iterador registro::CrearIt();
        friend class registro::const_Iterador;
    };

    class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename registro::Iterador& otro);

        const_Iterador(const typename registro::const_Iterador& otro);

        const_Iterador& operator = (const typename registro::const_Iterador& otro);

        bool operator==(const typename registro::const_Iterador&) const;

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

        const_Iterador(const registro* d);

        friend typename registro::const_Iterador registro::CrearIt() const;
    };

    struct Elem
    {
      public:

        const NombreCampo& clave;
        dato& significado;

        Elem(const NombreCampo& c, dato& s) : clave(c), significado(s) {}
        //Para sacar esto de aca, necesitariamos definir rasgos y otras yerbas
        //Lamentablemente, sino C++ no reconoce bien los tipos

       // friend std::ostream& operator<<(std::ostream& os, const registro::Elem& e) {
        //  return os << e.clave << ":" << e.significado;
        

      private:

        typename registro::Elem& operator=(const registro::Elem&);
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

        typename registro::const_Elem& operator = (const registro::const_Elem&);
    };

	private:

   Lista<NombreCampo> claves_;
    Lista<dato> significados_;

};





///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
ostream& operator << (std::ostream& out, registro r){
  r.Mostrar(out);
  return out;
}
void registro::Mostrar(ostream& out)const{
    typename registro::const_Iterador it = CrearIt();
    while(it.HaySiguiente()){
      if(it.SiguienteSignificado().tipo()){
          out <<"(" << it.SiguienteClave() << ", ";
          out << it.SiguienteSignificado().valorNat_const()<< ") ";
      }
      else{
        out << "("<<it.SiguienteClave() << ", ";
        out << it.SiguienteSignificado().valorString_const()<< ") ";
      }
      it.Avanzar();
    }
    out << "\n";
      
}


bool operator == (const registro& d1, const registro& d2);

  // Implementacion Dicc


registro::registro()
{}


registro::registro(const registro& otro)
  : claves_(otro.claves_), significados_(otro.significados_)
{}


registro& registro::operator = (const registro& otro)
{
  claves_ = otro.claves_;
  significados_ = otro.significados_;

  return *this;
}


typename registro::Iterador registro::Definir(const NombreCampo& clave, const dato& significado)
{
  Iterador it = Buscar(clave);

  if(it.HaySiguiente()) {
    it.SiguienteSignificado() = significado;
  } else {
    it = DefinirRapido(clave, significado);
  }

  return it;
}


typename registro::Iterador registro::DefinirRapido(const NombreCampo& clave, const dato& significado)
{
  #ifdef DEBUG
  assert( not Definido(clave) );
  #endif

  claves_.AgregarAdelante(clave);
  significados_.AgregarAdelante(significado);

  return CrearIt();
}


bool registro::Definido(const NombreCampo& clave) const
{
  return Buscar(clave).HaySiguiente();
}



const dato& registro::Significado(const NombreCampo& clave)const
{
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  return Buscar(clave).SiguienteSignificado();
}


dato& registro::Significado(const NombreCampo& clave)
{
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  return Buscar(clave).SiguienteSignificado();
}


void registro::Borrar(const NombreCampo& clave)
{
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  Buscar(clave).EliminarSiguiente();
}


Nat registro::CantClaves() const
{
  return claves_.Longitud();
}


typename registro::Iterador registro::CrearIt()
{
  return Iterador(this);
}


typename registro::const_Iterador registro::CrearIt() const
{
  return const_Iterador(this);
}

  // Implementacion Iterador


registro::Iterador::Iterador()
{}


registro::Iterador::Iterador(const typename registro::Iterador& otro)
: it_claves_(otro.it_claves_), it_significados_(otro.it_significados_)
{}


typename registro::Iterador& registro::Iterador::operator = (const typename registro::Iterador& otro)
{
  it_claves_ = otro.it_claves_;
  it_significados_ = otro.it_significados_;

  return *this;
}


bool registro::Iterador::HaySiguiente() const
{
  return it_claves_.HaySiguiente();
}


bool registro::Iterador::HayAnterior() const
{
  return it_claves_.HayAnterior();
}


const NombreCampo& registro::Iterador::SiguienteClave() const
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  return it_claves_.Siguiente();
}


dato& registro::Iterador::SiguienteSignificado()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return it_significados_.Siguiente();
}


typename registro::Elem registro::Iterador::Siguiente()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return Elem(SiguienteClave(), SiguienteSignificado());
}


const NombreCampo& registro::Iterador::AnteriorClave() const
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return it_claves_.Anterior();
}


dato& registro::Iterador::AnteriorSignificado()
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  return it_significados_.Anterior();
}


typename registro::Elem registro::Iterador::Anterior()
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  return Elem(AnteriorClave(), AnteriorSignificado());
}


void registro::Iterador::Avanzar()
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  it_claves_.Avanzar();
  it_significados_.Avanzar();
}


void registro::Iterador::Retroceder()
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  it_claves_.Retroceder();
  it_significados_.Retroceder();
}


registro::Iterador::Iterador(registro* d)
: it_claves_(d->claves_.CrearIt()), it_significados_(d->significados_.CrearIt())
{}


void registro::Iterador::EliminarSiguiente()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  it_claves_.EliminarSiguiente();
  it_significados_.EliminarSiguiente();
}


void registro::Iterador::EliminarAnterior()
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  it_claves_.EliminarAnterior();
  it_significados_.EliminarAnterior();
}

  // Implementacion const_Iterador


registro::const_Iterador::const_Iterador()
{}


registro::const_Iterador::const_Iterador(const typename registro::Iterador& otro)
  : it_claves_(otro.it_claves_), it_significados_(otro.it_significados_)
{}


registro::const_Iterador::const_Iterador(const typename registro::const_Iterador& otro)
  : it_claves_(otro.it_claves_), it_significados_(otro.it_significados_)
{}


typename registro::const_Iterador& registro::const_Iterador::operator=(const typename registro::const_Iterador& otro)
{
  it_claves_ = otro.it_claves_;
  it_significados_ = otro.it_significados_;

  return *this;
}


bool registro::const_Iterador::HaySiguiente() const
{
  return it_claves_.HaySiguiente();
}


bool registro::const_Iterador::HayAnterior() const
{
  return it_claves_.HayAnterior();
}


const NombreCampo& registro::const_Iterador::SiguienteClave() const
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  return it_claves_.Siguiente();
}


const dato& registro::const_Iterador::SiguienteSignificado() const
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  return it_significados_.Siguiente();
}


typename registro::const_Elem registro::const_Iterador::Siguiente() const
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return const_Elem(SiguienteClave(), SiguienteSignificado());
}


const NombreCampo& registro::const_Iterador::AnteriorClave() const
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return it_claves_.Anterior();
}


const dato& registro::const_Iterador::AnteriorSignificado() const
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  return it_significados_.Anterior();
}


typename registro::const_Elem registro::const_Iterador::Anterior() const
{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return const_Elem(AnteriorClave(), AnteriorSignificado());
}


void registro::const_Iterador::Avanzar()
{
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  it_claves_.Avanzar();
  it_significados_.Avanzar();
}


void registro::const_Iterador::Retroceder()
{
  #ifdef DEBUG
  assert(HayAnterior());
  #endif

  it_claves_.Retroceder();
  it_significados_.Retroceder();
}


registro::const_Iterador::const_Iterador(const registro* d)
: it_claves_(d->claves_.CrearIt()), it_significados_(d->significados_.CrearIt())
{}


bool registro::const_Iterador::operator == (const typename registro::const_Iterador& otro) const
{
  return it_claves_ == otro.it_claves_ && it_significados_ == otro.it_significados_;
}


bool registro::Iterador::operator == (const typename registro::Iterador& otro) const
{
  return it_claves_ == otro.it_claves_ && it_significados_ == otro.it_significados_;
}

  ///Funciones auxiliares


typename registro::Iterador registro::Buscar(const NombreCampo& clave)
{
  typename registro::Iterador it = CrearIt();
  while(it.HaySiguiente() && !(it.SiguienteClave() == clave)){
    it.Avanzar();
  }
  return it;
}


typename registro::const_Iterador registro::Buscar(const NombreCampo& clave) const
{
  typename registro::const_Iterador it = CrearIt();
  while(it.HaySiguiente() && !(it.SiguienteClave() == clave)){
      it.Avanzar();
  }
  return it;
}



bool operator == (const registro& d1, const registro& d2)
{
  bool retval = d1.CantClaves() == d2.CantClaves();
  typename registro::const_Iterador it1 = d1.CrearIt();
  while(retval and it1.HaySiguiente()){
    typename registro::const_Iterador it2 = d2.Buscar(it1.SiguienteClave());
    retval = it2.HaySiguiente() and it1.SiguienteSignificado() == it2.SiguienteSignificado();
    it1.Avanzar();
  }
  return retval;
}





void registro::mergear(registro& r2){
	typename registro::Iterador itR2= r2.CrearIt();

	while(itR2.HaySiguiente()){
		if(!(Definido(itR2.SiguienteClave()))) 
			Definir(itR2.SiguienteClave(), itR2.SiguienteSignificado());
		itR2.Avanzar();
	}	
}

Conj<NombreCampo> registro::campos(){
	Conj<NombreCampo> res;
	typename registro::Iterador itR1= CrearIt();
	while(itR1.HaySiguiente()){
		res.AgregarRapido(itR1.SiguienteClave());
		itR1.Avanzar();
	}
	return res;
}
	
void registro::copiarCampos(Conj<NombreCampo> c, registro r2){
	typename::Conj<NombreCampo>::Iterador it=c.CrearIt();
	while(it.HaySiguiente()){
		if(!Definido(it.Siguiente())){
			Definir(it.Siguiente(), r2.Significado(it.Siguiente()));
			}
		it.Avanzar();	
		} 
	}
	
bool registro::coincidenTodos(Conj<NombreCampo>& c, registro& r2){
	bool res=true;
	if(!c.EsVacio()){
		typename::Conj<NombreCampo>::Iterador it=c.CrearIt();
		while(it.HaySiguiente() && res==true){
			if(Significado(it.Siguiente()).tipo() != r2.Significado(it.Siguiente()).tipo()){
				res=false;
				}
			else{
				if(Significado(it.Siguiente()).tipo()){
					if(Significado(it.Siguiente()).valorNat() != r2.Significado(it.Siguiente()).valorNat()){res=false;}
					}
				else{
					if(Significado(it.Siguiente()).valorString() != r2.Significado(it.Siguiente()).valorString()){res=false;}
					}	
				}
		
			it.Avanzar();	
			}		
		}
	return res;	
}

bool registro::borrar(registro crit){
	bool res=true;
	Conj<NombreCampo> c=crit.campos();
	res=coincidenTodos(c,crit);
	return res;
}	

Lista<registro> registro::coincidencias(Lista<registro> cr){
	Lista<registro> res;
	typename Lista<registro>::Iterador it=cr.CrearIt();
	while(it.HaySiguiente()){
		registro r(it.Siguiente());
		Conj<NombreCampo> camp=campos();
		if(coincidenTodos(camp,r)){
			res.AgregarAdelante(r);
			}
		it.Avanzar();	
		}
	return res;	
	}
	
#endif
