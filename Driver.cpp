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
  base.agregarTabla(t);
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
  Registro crit;
  dato a;
  if(valor.tipo()==NAT) a=valor.dameNat();
  else a=valor.dameString();
  crit.Definir(columna, a);
  base.borrar(crit, tabla);
}

aed2::Conj<Columna> Driver::columnasDeTabla(const NombreTabla& tabla) const
{
  //PAJA DE HACER :/
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabla) const
{
  tabla* t = base.dameTabla(tabla);
  return t->calves();
}

aed2::Conj<Driver::registro> Driver::registrosDeTabla(const NombreTabla& tabla) const
{
  /*tabla* t  = base.dameTabla(tabla);
  Lista<Registro> registro = t->registros();
  typename Lista<Registro>::Iterador = registro.CrearIt();
  Conj<Driver::registro> res;
  while(it.HaySiguiente()){

  }*/
}

aed2::Nat Driver::cantidadDeAccesosDeTabla(const NombreTabla& tabla) const
{
  // TODO ...
  assert(false);
}

Driver::Dato Driver::minimo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  // TODO ...
  assert(false);
}

Driver::Dato Driver::maximo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  // TODO ...
  assert(false);
}

aed2::Conj<Driver::registro> Driver::buscar(const NombreTabla& tabla, const registro& criterio) const
{
  // TODO ...
  assert(false);
}

aed2::Conj<NombreTabla> Driver::tablas() const
{
  // TODO ...
  assert(false);
}

const NombreTabla Driver::tablaMaxima() const
{
  // TODO ...
  assert(false);
}

// Indices

bool Driver::tieneIndiceNat(const NombreTabla& tabla) const
{
  // TODO ...
  assert(false);
}

bool Driver::tieneIndiceString(const NombreTabla& tabla) const
{
  // TODO ...
  assert(false);
}

const NombreCampo& Driver::campoIndiceNat(const NombreTabla& tabla) const
{
  // TODO ...
  assert(false);
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
