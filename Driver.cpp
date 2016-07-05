#include "Driver.h"
#include "BD.h"

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
{}

Driver::~Driver()
{
base=BD();
}

// Tablas

void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves)
{
  tabla t;
  typename Conj<Columna>::const_Iterador it= columnas.CrearIt();
  registro col;
  while(it.HaySiguiente()){
    dato a;
    if(it.Siguiente().tipo==NAT) a=0;
    else  a="aed2";
    col.Definir(it.Siguiente().nombre,a);
    it.Avanzar();
  }
  t.nuevaTabla(nombre, col, claves);
  base.agregarTabla(t);
}

void Driver::insertarRegistro(const NombreTabla& tabla, const Registro& registr)
{
  registro r;
	typename Driver::Registro::const_Iterador it=registr.CrearIt();
  while(it.HaySiguiente()){
    dato a;
    if(it.SiguienteSignificado().tipo()==NAT){
		Nat n=it.SiguienteSignificado().dameNat();
		a.nuevoDatoNat(n);
		r.Definir(it.SiguienteClave(), a);
		}
    else{ 
		String s=it.SiguienteSignificado().dameString();
		a.nuevoDatoString(it.SiguienteSignificado().dameString());
		r.Definir(it.SiguienteClave(), a);
		}
    it.Avanzar();
	}
  NombreTabla t=tabla;
  base.insertarEntrada(r,t);
}

void Driver::borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor)
{
  registro r;
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
  Conj<NombreCampo> campos=t->campos();
  Conj<Columna> cc;
  typename Conj<NombreCampo>::Iterador itC=campos.CrearIt();
  while(itC.HaySiguiente()){
	  Columna c;
	  c.nombre=itC.Siguiente();
	  c.tipo= t->tipoCampo(itC.Siguiente());
	  cc.AgregarRapido(c);
	  itC.Avanzar();
	  }
	  return cc;
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabl) const
{
  tabla* t=base.dameTabla(tabl);
  return t->claves();
}

aed2::Conj<Driver::Registro> Driver::registrosDeTabla(const NombreTabla& tabl) const
{
tabla* t=base.dameTabla(tabl);
  Lista<registro> lr=t->registros();
  typename Lista<registro>::Iterador it=lr.CrearIt();
  Conj<Driver::Registro> cr;
  while(it.HaySiguiente()){
	  Driver::Registro r;
	typename registro::Iterador itR=it.Siguiente().CrearIt();
	while(itR.HaySiguiente()){	  
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
	itR.Avanzar();
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

aed2::Conj<Driver::Registro> Driver::buscar(const NombreTabla& tabl, const Registro& criterio) const
{
typename Registro::const_Iterador it=criterio.CrearIt();
  registro crit;
  while(it.HaySiguiente()){
	  dato d;
	  if(it.SiguienteSignificado().tipo() == NAT){
		  d.nuevoDatoNat(it.SiguienteSignificado().dameNat());
		  }
		  else{
			  d.nuevoDatoString(it.SiguienteSignificado().dameString());
			  }
	  crit.Definir(it.SiguienteClave(), d);
	  it.Avanzar();
	  }
	Lista<registro> lr=base.buscar(crit, tabl);
	typename Lista<registro>::Iterador itR=lr.CrearIt();
	Conj<Driver::Registro> cr;
	while(itR.HaySiguiente()){
		Driver::Registro r;
	  typename registro::Iterador itReg=itR.Siguiente().CrearIt();
	  while(itReg.HaySiguiente()){
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
	  itReg.Avanzar();
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
	 itT.Avanzar();
	 }
	 return ct;
}

NombreTabla Driver::tablaMaxima() const
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

NombreCampo Driver::campoIndiceNat(const NombreTabla& tabl) const
{
  tabla* t=base.dameTabla(tabl);	
  Conj<NombreCampo> ind=t->indices();
  typename Conj<NombreCampo>::Iterador it=ind.CrearIt();
  NombreCampo res;
  while(it.HaySiguiente()){
	  if(t->tipoCampo(it.Siguiente()) == NAT){
		  res=it.Siguiente();
		  return res;
		  }
	it.Avanzar();	  
	  }
}

NombreCampo Driver::campoIndiceString(const NombreTabla& tabl) const
{
   tabla* t=base.dameTabla(tabl);	
  Conj<NombreCampo> ind=t->indices();
  typename Conj<NombreCampo>::Iterador it=ind.CrearIt();
  NombreCampo res;
  while(it.HaySiguiente()){
	  if(t->tipoCampo(it.Siguiente()) == STR){
		  res=it.Siguiente();
		  return res;
		  }
	it.Avanzar();	  
	  }
}

void Driver::crearIndiceNat(const NombreTabla& tabl, const NombreCampo& campo)
{
  tabla* t=base.dameTabla(tabl);
   t->indexar(campo);
}

void Driver::crearIndiceString(const NombreTabla& tabl, const NombreCampo& campo)
{
tabla* t=base.dameTabla(tabl);
  t->indexar(campo);
}

// Joins

bool Driver::hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
   return base.hayJoin(tabla1, tabla2);
}

NombreCampo Driver::campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  return base.campoJoin(tabla1, tabla2);
}

void Driver::generarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2, const NombreCampo& campo)
{
  base.generarVistaJoin(tabla1, tabla2, campo);
}

void Driver::borrarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)
{
  base.borrarJoin(tabla1,tabla2);
}

aed2::Conj<Driver::Registro> Driver::vistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)/* const*/
{
  Lista<registro> lr=base.vistaJoin(tabla1, tabla2);
  Conj<Driver::Registro> res;
  typename Lista<registro>::Iterador it=lr.CrearIt();
  while(it.HaySiguiente()){
	
	  Driver::Registro r;
	  typename registro::Iterador itR=it.Siguiente().CrearIt();
	  while(itR.HaySiguiente()){
		 
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
	  
	  itR.Avanzar();
  }
	  res.AgregarRapido(r);
	  it.Avanzar();
	  }
	  return res;
}
