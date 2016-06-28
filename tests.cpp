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

int main(int argc, char **argv)
{
  //RUN_TEST( ejemplo_simple );
  RUN_TEST(testTabla);
  /********************************************************************
   * TODO: escribir casos de test exhaustivos para todas              *
   * las funcionalidades de cada módulo.                              *
   * La interacción con el TAD principal se debe hacer exclusivamente *
   * a través de la interfaz del driver.                              *
   ********************************************************************/

	return 0;
}
