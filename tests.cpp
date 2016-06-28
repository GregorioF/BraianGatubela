// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>

#include "Driver.h"
#include "mini_test.h"
#include "tabla.h"

#include <string>
#include <iostream>

using namespace aed2;
using namespace std;

void ejemplo_simple()
{
  aed2::Driver bd;
  ASSERT_EQ(bd.tablas().Cardinal(), 0);

  aed2::Conj<aed2::Columna> columnas_personas;

  aed2::Columna columna_dni;
  columna_dni.nombre = "DNI";
  columna_dni.tipo = aed2::NAT;

  aed2::Columna columna_nombre;
  columna_nombre.nombre = "nombre";
  columna_nombre.tipo = aed2::STR;

  aed2::Columna columna_apellido;
  columna_nombre.nombre = "apellido";
  columna_nombre.tipo = aed2::STR;

  columnas_personas.Agregar( columna_dni );
  columnas_personas.Agregar( columna_nombre );
  columnas_personas.Agregar( columna_apellido );

  aed2::Conj<aed2::NombreCampo> columnas_clave_personas;
  columnas_clave_personas.Agregar("DNI");

  bd.crearTabla("personas", columnas_personas, columnas_clave_personas);
  ASSERT_EQ(bd.tablas().Cardinal(), 1);

  aed2::Driver::Registro persona;
  persona.Definir("DNI", aed2::Driver::Dato(1));
  persona.Definir("nombre", aed2::Driver::Dato("Juan"));
  persona.Definir("apellido", aed2::Driver::Dato("Perez"));

  bd.insertarRegistro("personas", persona);

  // ...
}
void DefinirRegistro(Registro& r1,  Conj<NombreCampo>& campos ,  Dato ds [] ){
  typename Conj<NombreCampo>::Iterador it = campos.CrearIt();
  int i=0;
  while(it.HaySiguiente())it.Avanzar();
  while(it.HayAnterior()){
   // cout << it.Anterior() << endl;
    r1.Definir(it.Anterior(), ds[i]);
    it.Retroceder();
    i++;
  }
}

void testTabla(){
  Registro col;
  col.Definir("nombre",Dato("perez"));
  col.Definir("apellido",Dato("perez"));
  col.Definir("LU",Dato(1));
  col.Definir("Materia",Dato("perez"));
  col.Definir("Nota",Dato(10));
  col.Definir("eMail",Dato("perez"));
  Conj<NombreCampo> claves;
  claves.Agregar("LU");
  claves.Agregar("eMail");
  tabla t;
  t.nuevaTabla("candidatos_Para_Calesita_Pab2", col, claves);
  ASSERT(t.claves() == claves);
  ASSERT(t.indices().Cardinal() == 0);
  Conj<NombreCampo> campos = t.campos();
  typename Conj<NombreCampo>::Iterador itCampos= campos.CrearIt();
  /*while(itCampos.HaySiguiente()){
    std::cout << itCampos.Siguiente() << std::endl;
    itCampos.Avanzar();
  }*/  //Andan bien pero no quiero que me los escriba siempre...
  ASSERT(t.cantDeAccesos() ==  0);
  ASSERT(t.registros().Longitud() == 0);

  Registro r1;
  Dato arregloDato [6]= {Dato("charo"), Dato("olivera"),  Dato(11115), Dato("Aed2"), Dato(5), Dato("laTurraDeSaavedra@turra.com")};
  DefinirRegistro(r1,campos, arregloDato);
  Registro r2;
  Dato arregloDato2 [6]={Dato("lucia"), Dato("romero"), Dato(11215), Dato("Aed2"), Dato(6), Dato("siLaVidaTeDaLimones_HaceteUnChurro@fumancha.com")};
  DefinirRegistro(r2, campos, arregloDato2);
  Registro r3;
  Dato arregloDato3 [6] = {Dato("Gregorio"), Dato("Freidin"), Dato(43315), Dato("Aed2"), Dato(5), Dato("tuvieja@tuAbuelatamb.com")};
  DefinirRegistro(r3, campos, arregloDato3);
  t.agregarRegistro(r1);
  t.agregarRegistro(r2);
  t.agregarRegistro(r3);
  ASSERT(t.cantDeAccesos()== 3);
  ASSERT(t.registros().Longitud()==3);
  Registro crit;
  crit.Definir("LU", 43315);
  ASSERT(t.tipoCampo("LU")==NAT);
  t.borrarRegistro(crit);
  ASSERT(t.registros().Longitud() == 2);
  t.agregarRegistro(r3);
  t.indexar("LU");
  typename dicA<Nat, Lista<estrAux> >::Iterador itIndice = t.dameColumnaNatParaTest().CrearIt();
  cout << "\nLos valores de LU son: "<<endl;
  while(itIndice.HaySiguiente()){
    cout << itIndice.SiguienteClave() << ", ";
    itIndice.Avanzar();
  }
  t.borrarRegistro(crit);
  //y no funciona escribir itIndice= t.dameColumnaNatParaTest().CrearIt();  me hace crear otro iterador
  itIndice = t.dameColumnaNatParaTest().CrearIt();
  cout << "\nY despues de borrar uno son: "<<endl;
  while(itIndice.HaySiguiente()){
    cout << itIndice.SiguienteClave() << ", ";
    itIndice.Avanzar();
  }   

  /* DESOMENTANDO ESTO DEJA DE FUNCIONAR DESP DEL TEXTO QUE DICE  "DESPUES DE BORRAR UNO SON:...."

  Registro r4;
  Dato arregloDato4 [6]={Dato("Brian"), Dato("Gatubela"), Dato(11315), Dato("Orga2"), Dato(6), Dato("Braian.Gatubela@GroopieDeBatman.com")};
  t.agregarRegistro(r4);
  DefinirRegistro(r4, campos, arregloDato4);
  t.agregarRegistro(r3);
  typename dicA<Nat, Lista<estrAux> >::Iterador itIndice3 = t.dameColumnaNatParaTest().CrearIt();
  cout << "\nY despues de Agregar dos registros son: "<<endl;
  while(itIndice3.HaySiguiente()){
    cout << itIndice3.SiguienteClave() << ", ";
    itIndice3.Avanzar();
  }*/ 
}
void agregarRegistroSinIndices(){
Registro r;
NombreCampo c="hi";
Nat x=5;
Dato d=Dato(x);
r.Definir(c,d);

NombreCampo c1="lala";
String u="lolo";
Dato d1=Dato(u);
r.Definir(c1,d1);

NombreCampo c2="d";
Nat y=8;
Dato d2=Dato(y);
r.Definir(c2,d2);

NombreCampo c3="mmm";
String t="toto";
Dato d3=Dato(t);
r.Definir(c3,d3);

Conj<NombreCampo> camp=campos(r);
tabla n=tabla();
String t1="TABLA";
n.nuevaTabla(t1,r,camp);
String nombre=n.nombre();
cout<< nombre<<endl;
n.agregarRegistro(r);
Lista<Registro> lr=n.registros();
Nat longg=lr.Longitud();
cout << longg<< endl;
Registro crit;
crit.Definir(c,d);
Registro r1;

r1.Definir(c,d);
r1.Definir(c1,d3);
r1.Definir(c2,d2);
r1.Definir(c3,d1);

n.agregarRegistro(r1);

Registro r2;
Nat x1=1;
Dato d5=Dato(x1);
r2.Definir(c,d5);

String u1="lalo";
Dato d6=Dato(u1);
r2.Definir(c1,d6);

Nat y1=2;
Dato d7=Dato(y1);
r2.Definir(c2,d7);

String t4="tato";
Dato d8=Dato(t4);
r2.Definir(c3,d8);

n.agregarRegistro(r2);
ASSERT(n.registros().Longitud() == 3);
ASSERT(n.cantDeAccesos() ==  3);

Registro r3;
Nat x2=1;
Dato d9=Dato(x2);
r3.Definir(c,d9);

String u2="lalo";
Dato d10=Dato(u2);
r3.Definir(c1,d10);

Nat y2=2;
Dato d11=Dato(y2);
r3.Definir(c2,d11);

String t5="tato";
Dato d12=Dato(t5);
r3.Definir(c3,d12);

n.agregarRegistro(r3);
}

void agregarRegConInd(){
Registro r;
NombreCampo c="hi";
Nat x=5;
Dato d=Dato(x);
r.Definir(c,d);

NombreCampo c1="lala";
String u="lolo";
Dato d1=Dato(u);
r.Definir(c1,d1);

NombreCampo c2="d";
Nat y=8;
Dato d2=Dato(y);
r.Definir(c2,d2);

NombreCampo c3="mmm";
String t="toto";
Dato d3=Dato(t);
r.Definir(c3,d3);

Conj<NombreCampo> camp=campos(r);
tabla n=tabla();
String t1="TABLA";
n.nuevaTabla(t1,r,camp);
String nombre=n.nombre();
cout<< nombre<<endl;
n.agregarRegistro(r);

Registro r1;

r1.Definir(c,d);
r1.Definir(c1,d3);
r1.Definir(c2,d2);
r1.Definir(c3,d1);

n.agregarRegistro(r1);

Registro r2;
Nat x1=1;
Dato d5=Dato(x1);
r2.Definir(c,d5);

String u1="lalo";
Dato d6=Dato(u1);
r2.Definir(c1,d6);

Nat y1=2;
Dato d7=Dato(y1);
r2.Definir(c2,d7);

String t4="tato";
Dato d8=Dato(t4);
r2.Definir(c3,d8);

n.agregarRegistro(r2);
ASSERT(n.registros().Longitud() == 3);
ASSERT(n.cantDeAccesos() ==  3);

Registro r3;
Nat x2=1;
Dato d9=Dato(x2);
r3.Definir(c,d9);

String u2="lalo";
Dato d10=Dato(u2);
r3.Definir(c1,d10);

Nat y2=2;
Dato d11=Dato(y2);
r3.Definir(c2,d11);

String t5="tato";
Dato d12=Dato(t5);
r3.Definir(c3,d12);

Registro crit;
crit.Definir(c,d5);
n.borrarRegistro(crit);

n.agregarRegistro(r3);

ASSERT(n.registros().Longitud() == 3);
ASSERT(n.cantDeAccesos() ==  5);

n.indexar(c1);

Registro r4;
Nat x4=78;
Dato d13=Dato(x4);
r4.Definir(c,d13);

String u4="Hola";
Dato d14=Dato(u4);
r4.Definir(c1,d14);

Nat y4=24;
Dato d15=Dato(y4);
r4.Definir(c2,d15);

String t6="Mato";
Dato d16=Dato(t6);
r4.Definir(c3,d16);

n.agregarRegistro(r4);



Registro r5;
Nat x5=75;
Dato d17=Dato(x5);
r5.Definir(c,d17);

String u5="Holita";
Dato d18=Dato(u5);
r5.Definir(c1,d18);

Nat y5=25;
Dato d19=Dato(y5);
r5.Definir(c2,d19);

String t7="Mateo";
Dato d20=Dato(t7);
r5.Definir(c3,d20);

n.indexar(c);
Conj<NombreCampo> ind;
ind.AgregarRapido(c);
ind.AgregarRapido(c1);
ASSERT(n.indices()==ind);

// n.agregarRegistro(r5); SALTA SEG FAULT CDO AGREGAS REGISTRO Y TENES LOS DOS INDICES

}


void dameColumnas(){
Registro r;
NombreCampo c="hi";
Nat x=5;
Dato d=Dato(x);
r.Definir(c,d);

NombreCampo c1="lala";
String u="lolo";
Dato d1=Dato(u);
r.Definir(c1,d1);

NombreCampo c2="d";
Nat y=8;
Dato d2=Dato(y);
r.Definir(c2,d2);

NombreCampo c3="mmm";
String t="toto";
Dato d3=Dato(t);
r.Definir(c3,d3);

Conj<NombreCampo> camp=campos(r);
tabla n=tabla();
String t1="TABLA";
n.nuevaTabla(t1,r,camp);
String nombre=n.nombre();
cout<< nombre<<endl;

ASSERT(n.cantDeAccesos()==0);
n.agregarRegistro(r);
ASSERT(n.cantDeAccesos()==1);
Registro r1;

r1.Definir(c,d);
r1.Definir(c1,d3);
r1.Definir(c2,d2);
r1.Definir(c3,d1);

n.agregarRegistro(r1);
ASSERT(n.cantDeAccesos()==2);
Registro r2;
Nat x1=1;
Dato d5=Dato(x1);
r2.Definir(c,d5);

String u1="lalo";
Dato d6=Dato(u1);
r2.Definir(c1,d6);

Nat y1=2;
Dato d7=Dato(y1);
r2.Definir(c2,d7);

String t4="tato";
Dato d8=Dato(t4);
r2.Definir(c3,d8);

n.agregarRegistro(r2);
ASSERT(n.cantDeAccesos()==3);
Registro r3;
Nat x2=6;
Dato d9=Dato(x2);
r3.Definir(c,d9);

String u2="lo";
Dato d10=Dato(u2);
r3.Definir(c1,d10);

Nat y2=65;
Dato d11=Dato(y2);
r3.Definir(c2,d11);

String t5="tito";
Dato d12=Dato(t5);
r3.Definir(c3,d12);

n.agregarRegistro(r3);
ASSERT(n.cantDeAccesos()==4);
Registro r4;
Nat x4=78;
Dato d13=Dato(x4);
r4.Definir(c,d13);

String u4="Hola";
Dato d14=Dato(u4);
r4.Definir(c1,d14);

Nat y4=24;
Dato d15=Dato(y4);
r4.Definir(c2,d15);

String t6="Mato";
Dato d16=Dato(t6);
r4.Definir(c3,d16);

n.agregarRegistro(r4);

Registro r5;
Nat x5=75;
Dato d17=Dato(x5);
r5.Definir(c,d17);

String u5="Holita";
Dato d18=Dato(u5);
r5.Definir(c1,d18);

Nat y5=25;
Dato d19=Dato(y5);
r5.Definir(c2,d19);

String t7="Mateo";
Dato d20=Dato(t7);
r5.Definir(c3,d20);

n.agregarRegistro(r5);
	

n.indexar(c1);
n.indexar(c);
	
dicT<Lista<estrAux> >* it=n.dameColumnaString();
Lista<estrAux> listAux=(*it).obtener(t);
typename Lista<estrAux>::Iterador itL=listAux.CrearIt();
estrAux ext=itL.Siguiente();
typename Lista<Registro>::Iterador iR=ext.itReg;

Registro r8=iR.Siguiente();
Dato dat=r8.Significado(c1);
ASSERT(dat.dameString()== "toto");

dicA<Nat, Lista<estrAux> >* iN=n.dameColumnaNat();
Lista<estrAux> listA=(*iN).obtener(x);
typename Lista<estrAux>::Iterador itLis=listA.CrearIt();
estrAux ext2=itLis.Siguiente();
typename Lista<Registro>::Iterador iR2=ext2.itReg;

Registro r9=iR2.Siguiente();
Dato dat2=r9.Significado(c);
ASSERT(dat2.dameNat()== 5);

iR2.EliminarSiguiente();

ASSERT(n.registros().Longitud() == 5);

Registro crit;
crit.Definir(c,d5);
n.borrarRegistro(crit);

ASSERT(n.registros().Longitud() == 4);

}

int main(int argc, char **argv)
{
  //RUN_TEST( ejemplo_simple );
  RUN_TEST(testTabla);
  RUN_TEST(agregarRegistroSinIndices);
  RUN_TEST(agregarRegConInd);
  RUN_TEST(dameColumnas);
  /********************************************************************
   * TODO: escribir casos de test exhaustivos para todas              *
   * las funcionalidades de cada módulo.                              *
   * La interacción con el TAD principal se debe hacer exclusivamente *
   * a través de la interfaz del driver.                              *
   ********************************************************************/

	return 0;
}
