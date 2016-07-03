#include "Driver.h"
#include "BD.h"
#include "tabla.h"

bool aed2::operator == (const aed2::Columna& c1, const aed2::Columna& c2)
{
  return c1.nombre == c2.nombre and c1.tipo == c2.tipo;
}

using namespace aed2;

////////////////////////////////////////////////////////////////////////////////
// Dato
////////////////////////////////////////////////////////////////////////////////

Driver::Dato::Dato(const aed2::Nat& x)
  : tipo_( NAT ), nat_( x )
{}

Driver::Dato::Dato(const aed2::String& x)
  : tipo_( STR ), str_( x )
{}

bool Driver::Dato::esNat() const
{
  return tipo_ == NAT;
}

bool Driver::Dato::esString() const
{
  return tipo_ == STR;
}

TipoCampo Driver::Dato::tipo() const
{
  return tipo_;
}

const aed2::Nat& Driver::Dato::dameNat() const
{
  assert( esNat() );
  return nat_;
}

const aed2::String& Driver::Dato::dameString() const
{
  assert( esString() );
  return str_;
}

bool Driver::Dato::operator == (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ == otro.nat_ ) or
    ( tipo_ == STR and str_ == otro.str_ )
  );
}

bool Driver::Dato::operator != (const Dato& otro) const
{
  return not (*this == otro);
}

////////////////////////////////////////////////////////////////////////////////
// Base de datos
////////////////////////////////////////////////////////////////////////////////

Driver::Driver()
{
	base= BD();
}

Driver::~Driver()
{}



// Tablas

void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves)
{
  tabla t;
  typename Conj<Columna>::const_Iterador it= columnas.CrearIt();
  Registro col;
  while(it.HaySiguiente()){
    dato a;
    if(it.Siguiente().tipo==NAT) a=0;
    else  a="aed2";
    col.Definir(it.Siguiente().nombre,a);
    it.Avanzar();
  }
  t.nuevaTabla(nombre, col, claves);
}

void Driver::insertarRegistro(const NombreTabla& tabla, const registro& registro)
{
	Registro r;
	typename Driver::registro::const_Iterador it=registro.CrearIt();
  while(it.HaySiguiente()){
    dato a;
    if(it.SiguienteSignificado().tipo()==NAT) a=it.SiguienteSignificado().dameNat();
    else a=it.SiguienteSignificado().dameString();
	  r.Definir(it.SiguienteClave(), a);
    it.Avanzar();
	}
  NombreTabla t=tabla;
  base.insertarEntrada(r,t);
}

void Driver::borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor)
{
 Registro r;
 dato d;
 if(valor.esNat()){
	 d.nuevoDatoNat(valor.dameNat());
	 }
else{
	d.nuevoDatoString(valor.dameString());
	}	 
 r.Definir(columna,d);
 NombreTabla t=tabla;
 base.borrar(r,t);
}

aed2::Conj<Columna> Driver::columnasDeTabla(const NombreTabla& tabl) const
{
  tabla* t= base.dameTabla(tabl);
  Lista<Registro> cr=t->registros();
  typename Lista<Registro>::const_Iterador it=cr.CrearIt();
  Conj<Columna> cc;
  while(it.HaySiguiente()){
	  Columna c;
	  c.nombre=it.Siguiente().CrearIt().SiguienteClave();
	  if(it.Siguiente().CrearIt().SiguienteSignificado().tipo()){
		  c.tipo=NAT;
		  }
	else{
		c.tipo=STR;
		}
		cc.AgregarRapido(c);	  
	  it.Avanzar();
	  }
	  return cc;
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabl) const
{
  tabla* t=base.dameTabla(tabl);
  return t->claves();
}

aed2::Conj<Driver::registro> Driver::registrosDeTabla(const NombreTabla& tabl) const
{
  tabla* t=base.dameTabla(tabl);
  Lista<Registro> lr=t->registros();
  typename Lista<Registro>::Iterador it=lr.CrearIt();
  Conj<Driver::registro> cr;
  while(it.HaySiguiente()){
	  Driver::registro r;
	  typename Registro::Iterador itR=it.Siguiente().CrearIt();
	  
	  if(itR.SiguienteSignificado().tipo()){
		  Nat n=itR.SiguienteSignificado().valorNat();
		  Dato d=Dato(n);
		  r.Definir(itR.SiguienteClave(), d);
		  }
	else{
		String s=itR.SiguienteSignificado().valorString();
		  Dato d=Dato(s);
		  r.Definir(itR.SiguienteClave(), d);
		}	  
	  
	  cr.AgregarRapido(r);
	  it.Avanzar();
	  }
	  return cr;
}

aed2::Nat Driver::cantidadDeAccesosDeTabla(const NombreTabla& tabla) const
{
NombreTabla t=tabla;	
 return base.cantDeAccesos(t);
}

Driver::Dato Driver::minimo(const NombreTabla& tabl, const NombreCampo& columna) const
{
  tabla* t=base.dameTabla(tabl);
  dato d;
  d=t->minimo(columna);
  if(d.tipo()){
	  Nat n=d.valorNat();
	  Dato d1=Dato(n);
	  return d1;
	  }
	else{
		 String s=d.valorString();
	  Dato d1=Dato(s);
	  return d1;
		}  
}

Driver::Dato Driver::maximo(const NombreTabla& tabl, const NombreCampo& columna) const
{
  tabla* t=base.dameTabla(tabl);
  dato d;
  d=t->maximo(columna);
  if(d.tipo()){
	  Nat n=d.valorNat();
	  Dato d1=Dato(n);
	  return d1;
	  }
	else{
		String s=d.valorString();
		Dato d1=Dato(s);
		return d1;
		}
}

aed2::Conj<Driver::registro> Driver::buscar(const NombreTabla& tabl, const registro& criterio) const
{
  typename registro::const_Iterador it=criterio.CrearIt();
  Registro crit;
  while(it.HaySiguiente()){
	  dato d;
	  if(it.SiguienteSignificado().tipo() == NAT){
		  d.nuevoDatoNat(it.SiguienteSignificado().dameNat());
		  }
		  else{
			  d.nuevoDatoString(it.SiguienteSignificado().dameString());
			  }
	  crit.Definir(it.SiguienteClave(), d);
	  }
	Lista<Registro> lr=base.buscar(crit, tabl);
	typename Lista<Registro>::Iterador itR=lr.CrearIt();
	Conj<Driver::registro> cr;
	while(itR.HaySiguiente()){
		Driver::registro r;
	  typename Registro::Iterador itReg=itR.Siguiente().CrearIt();
	  
	  if(itReg.SiguienteSignificado().tipo()){
		  Nat n=itReg.SiguienteSignificado().valorNat();
		  Dato d=Dato(n);
		  r.Definir(itReg.SiguienteClave(), d);
		  }
	else{
		String s=itReg.SiguienteSignificado().valorString();
		  Dato d=Dato(s);
		  r.Definir(itReg.SiguienteClave(), d);
		}	  
	  
	  cr.AgregarRapido(r);
	  itR.Avanzar();
		}
		return cr;   
}

aed2::Conj<NombreTabla> Driver::tablas() const
{
 typename Lista<NombreTabla>::const_Iterador itT=base.tablas();
 Conj<NombreTabla> ct;
 while(itT.HaySiguiente()){
	 ct.AgregarRapido(itT.Siguiente());
	 }
	 return ct;
}

const NombreTabla Driver::tablaMaxima() const
{
 return base.tablaMaxima();
}

// Indices

bool Driver::tieneIndiceNat(const NombreTabla& tabl) const
{
  tabla* t=base.dameTabla(tabl);
  return t->hayIndiceNat();
}

bool Driver::tieneIndiceString(const NombreTabla& tabl) const
{
  tabla* t=base.dameTabla(tabl);
  return t->hayIndiceString();
}

const NombreCampo& Driver::campoIndiceNat(const NombreTabla& tabl) const
{
tabla* t=base.dameTabla(tabl);	
  Conj<NombreCampo> ind=t->indices();
  typename Conj<NombreCampo>::Iterador it=ind.CrearIt();
  NombreCampo res;
  while(it.HaySiguiente()){
	  if(t->tipoCampo(it.Siguiente())){
		  res=it.Siguiente();
		  return res;
		  }
	it.Avanzar();	  
	  }
	  
}

const NombreCampo& Driver::campoIndiceString(const NombreTabla& tabla) const
{
  // TODO ...
  assert(false);
}

void Driver::crearIndiceNat(const NombreTabla& tabla, const NombreCampo& campo)
{
  // TODO ...
  assert(false);
}

void Driver::crearIndiceString(const NombreTabla& tabla, const NombreCampo& campo)
{
  // TODO ...
  assert(false);
}

// Joins

bool Driver::hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  // TODO ...
  assert(false);
}

const NombreCampo& Driver::campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  // TODO ...
  assert(false);
}

void Driver::generarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2, const NombreCampo& campo)
{
  // TODO ...
  assert(false);
}

void Driver::borrarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)
{
  // TODO ...
  assert(false);
}

Driver::registro unir(const Driver::registro& reg1, const Driver::registro& reg2, const NombreCampo& clave)
{
  // TODO ...
  assert(false);
}

aed2::Conj<Driver::registro> Driver::vistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  // TODO ...
  assert(false);
}
