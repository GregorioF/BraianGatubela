// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>

#include "mini_test.h"
#include "BD.h"
#include "Driver.cpp"

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
  bd.crearTabla("lala", columnas_personas, columnas_clave_personas);
 
 aed2::Driver::Registro pers;
  pers.Definir("DNI", aed2::Driver::Dato(8));
  pers.Definir("nombre", aed2::Driver::Dato("Juana"));
  pers.Definir("apellido", aed2::Driver::Dato("Martin"));

 ASSERT_EQ(bd.tablas().Cardinal(), 2);
 bd.crearTabla("lola", columnas_personas, columnas_clave_personas);
 ASSERT_EQ(bd.tablas().Cardinal(), 3);
 bd.insertarRegistro("lola", persona);
 Conj<aed2::Driver::Registro> cr=bd.registrosDeTabla("lola");
 cout<< cr.Cardinal() <<endl;
 bd.generarVistaJoin("lola", "personas","DNI" );
 bd.insertarRegistro("lola", pers);
 //ASSERT_EQ(bd.cantidadDeAccesosDeTabla("lola"), 2);
 //ASSERT_EQ(bd.registrosDeTabla("lola").Cardinal(), 2);
 bd.vistaJoin("lola", "personas");
 bd.borrarVistaJoin("lola", "personas");
 
}

void DefinirRegistro(registro& r1,  Conj<NombreCampo>& campos ,  dato ds [] ){
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
  registro col;
  dato d;
  String s="perez";
  d.nuevoDatoString(s);
  col.Definir("nombre",d);
  col.Definir("apellido",d);
  dato d1;
  Nat n=1;
  d1.nuevoDatoNat(n);
  col.Definir("LU",d1);
  col.Definir("Materia",d);
  dato d2;
  Nat n1=10;
  d2.nuevoDatoNat(n1);
  col.Definir("Nota",d2);
  col.Definir("eMail",d);
  Conj<NombreCampo> claves;
  claves.Agregar("LU");
  claves.Agregar("eMail");
  tabla t;
  t.nuevaTabla("candidatos_Para_Calesita_Pab2", col, claves);
  ASSERT(t.claves() == claves);
  ASSERT(t.indices().Cardinal() == 0);
  Conj<NombreCampo> campos = t.campos();
  //typename Conj<NombreCampo>::Iterador itCampos= campos.CrearIt();
  /*while(itCampos.HaySiguiente()){
    std::cout << itCampos.Siguiente() << std::endl;
    itCampos.Avanzar();
  }*/  //Andan bien pero no quiero que me los escriba siempre...
  ASSERT(t.cantDeAccesos() ==  0);
  ASSERT(t.registros().Longitud() == 0);

  registro r1;
  dato charo;
  String s1="Charo";
  charo.nuevoDatoString(s1);
  dato olivera;
  String s2="Olivera";
  olivera.nuevoDatoString(s2);
  dato lU;
  Nat n3=11115;
  lU.nuevoDatoNat(n3);
  dato nota;
  Nat n4=5;
  nota.nuevoDatoNat(n4);
  dato materia;
  String s3="AED2";
  materia.nuevoDatoString(s3);
  dato email;
  String s4="laTurraDeSaavedra@turra.com";
  email.nuevoDatoString(s4);
  
  dato arregloDato [6]= {charo, olivera,  lU, materia, nota, email};
  DefinirRegistro(r1,campos, arregloDato);
  
  
  registro r2;
  dato lucia;
  String s5="Lucia";
  lucia.nuevoDatoString(s5);
  dato romero;
  String s6="Romero";
  romero.nuevoDatoString(s6);
  dato lU1;
  Nat n5=27215;
  lU1.nuevoDatoNat(n5);
  dato nota1;
  Nat n6=6;
  nota1.nuevoDatoNat(n6);
  dato materia1;
  String s7="AED2";
  materia1.nuevoDatoString(s7);
  dato email1;
  String s8="siLaVidaTeDaLimones_HaceteUnChurro@fumancha.com";
  email1.nuevoDatoString(s8);
  
  dato arregloDato2 [6]={lucia,romero, lU1, materia1, nota1, email1};
  DefinirRegistro(r2, campos, arregloDato2);
  registro r3;
  
  dato gregorio;
  String s9="Gregorio";
  gregorio.nuevoDatoString(s9);
  dato freidin;
  String s10="Freidin";
  freidin.nuevoDatoString(s10);
  dato lU2;
  Nat n7=43315;
  lU2.nuevoDatoNat(n7);
  dato nota2;
  Nat n8=10;
  nota2.nuevoDatoNat(n8);
  dato materia2;
  String s11="AED2";
  materia2.nuevoDatoString(s11);
  dato email2;
  String s12="tuvieja@tuAbuelatamb.com";
  email2.nuevoDatoString(s12);
  
  dato arregloDato3 [6] = {gregorio, freidin, lU2, materia2, nota2, email2};
  DefinirRegistro(r3, campos, arregloDato3);
  t.agregarRegistro(r1);
  t.agregarRegistro(r2);
  t.agregarRegistro(r3);
  ASSERT(t.cantDeAccesos()== 3);
  ASSERT(t.registros().Longitud()==3);
  registro crit;
  dato d3;
  Nat num=43315;
  d3.nuevoDatoNat(num);
  NombreCampo cc="LU";
  crit.Definir(cc, d3);
  ASSERT(t.tipoCampo("LU")==NAT);
  t.borrarRegistro(crit);
  ASSERT(t.registros().Longitud() == 2);
  t.agregarRegistro(r3);
  t.indexar("LU");
  
  registro r4;
   dato brian;
  String s13="Braian";
  brian.nuevoDatoString(s13);
  dato gatubela;
  String s14="Gatubela";
  gatubela.nuevoDatoString(s14);
  dato lU3;
  Nat n9=43315;
  lU3.nuevoDatoNat(n9);
  dato nota3;
  Nat n10=6;
  nota3.nuevoDatoNat(n10);
  dato materia3;
  String s15="Orga2";
  materia3.nuevoDatoString(s15);
  dato email3;
  String s16="Braian.Gatubela@GroopieDeBatman.com";
  email3.nuevoDatoString(s16);
  dato arregloDato4 [6]={brian,gatubela,lU3,materia3,nota3,email3};
  DefinirRegistro(r4, campos, arregloDato4);
  t.agregarRegistro(r4);
  t.agregarRegistro(r3);
  
}
void agregarRegistroSinIndices(){
registro r;
NombreCampo c="hi";
Nat x=5;
dato d;
d.nuevoDatoNat(x);
r.Definir(c,d);

NombreCampo c1="lala";
String u="lolo";
dato d1;
d1.nuevoDatoString(u);
r.Definir(c1,d1);

NombreCampo c2="d";
Nat y=8;
dato d2;
d2.nuevoDatoNat(y);
r.Definir(c2,d2);

NombreCampo c3="mmm";
String t="toto";
dato d3;
d3.nuevoDatoString(t);
r.Definir(c3,d3);

Conj<NombreCampo> camp=r.campos();
tabla n=tabla();
String t1="TABLA";
n.nuevaTabla(t1,r,camp);
String nombre=n.nombre();
cout<< nombre<<endl;
n.agregarRegistro(r);
Lista<registro> lr=n.registros();
Nat longg=lr.Longitud();
cout << longg<< endl;
registro crit;
crit.Definir(c,d);
registro r1;

r1.Definir(c,d);
r1.Definir(c1,d3);
r1.Definir(c2,d2);
r1.Definir(c3,d1);

n.agregarRegistro(r1);

registro r2;
Nat x1=1;
dato d5;
d5.nuevoDatoNat(x1);
r2.Definir(c,d5);

String u1="lalo";
dato d6;
d6.nuevoDatoString(u1);
r2.Definir(c1,d6);

Nat y1=2;
dato d7;
d7.nuevoDatoNat(y1);
r2.Definir(c2,d7);

String t4="tato";
dato d8;
d8.nuevoDatoString(t4);
r2.Definir(c3,d8);

n.agregarRegistro(r2);
ASSERT(n.registros().Longitud() == 3);
ASSERT(n.cantDeAccesos() ==  3);

registro r3;
Nat x2=1;
dato d9;
d9.nuevoDatoNat(x2);
r3.Definir(c,d9);

String u2="lalo";
dato d10;
d10.nuevoDatoString(u2);
r3.Definir(c1,d10);

Nat y2=2;
dato d11;
d11.nuevoDatoNat(y2);
r3.Definir(c2,d11);

String t5="tato";
dato d12;
d12.nuevoDatoString(t5);
r3.Definir(c3,d12);

n.agregarRegistro(r3);
}

void agregarRegConInd(){
registro r;
NombreCampo c="hi";
Nat x=5;
dato d;
d.nuevoDatoNat(x);
r.Definir(c,d);

NombreCampo c1="lala";
String u="lolo";
dato d1;
d1.nuevoDatoString(u);
r.Definir(c1,d1);

NombreCampo c2="d";
Nat y=8;
dato d2;
d2.nuevoDatoNat(y);
r.Definir(c2,d2);

NombreCampo c3="mmm";
String t="toto";
dato d3;
d3.nuevoDatoString(t);
r.Definir(c3,d3);

Conj<NombreCampo> camp=r.campos();
tabla n=tabla();
String t1="TABLA";
n.nuevaTabla(t1,r,camp);
String nombre=n.nombre();
cout<< nombre<<endl;
n.agregarRegistro(r);

registro r1;

r1.Definir(c,d);
r1.Definir(c1,d3);
r1.Definir(c2,d2);
r1.Definir(c3,d1);

n.agregarRegistro(r1);

registro r2;
Nat x1=1;
dato d5;
d5.nuevoDatoNat(x1);
r2.Definir(c,d5);

String u1="lalo";
dato d6;
d6.nuevoDatoString(u1);
r2.Definir(c1,d6);

Nat y1=2;
dato d7;
d7.nuevoDatoNat(y1);
r2.Definir(c2,d7);

String t4="tato";
dato d8;
d8.nuevoDatoString(t4);
r2.Definir(c3,d8);

n.agregarRegistro(r2);
ASSERT(n.registros().Longitud() == 3);
ASSERT(n.cantDeAccesos() ==  3);

registro r3;
Nat x2=1;
dato d9;
d9.nuevoDatoNat(x2);
r3.Definir(c,d9);

String u2="lalo";
dato d10;
d10.nuevoDatoString(u2);
r3.Definir(c1,d10);

Nat y2=2;
dato d11;
d11.nuevoDatoNat(y2);
r3.Definir(c2,d11);

String t5="tato";
dato d12;
d12.nuevoDatoString(t5);
r3.Definir(c3,d12);

registro crit;
crit.Definir(c,d5);
n.borrarRegistro(crit);

n.agregarRegistro(r3);

ASSERT(n.registros().Longitud() == 3);
ASSERT(n.cantDeAccesos() ==  5);

n.indexar(c1);

registro r4;
Nat x4=78;
dato d13;
d13.nuevoDatoNat(x4);
r4.Definir(c,d13);

String u4="Hola";
dato d14;
d14.nuevoDatoString(u4);
r4.Definir(c1,d14);

Nat y4=24;
dato d15;
d15.nuevoDatoNat(y4);
r4.Definir(c2,d15);

String t6="Mato";
dato d16;
d16.nuevoDatoString(t6);
r4.Definir(c3,d16);

n.agregarRegistro(r4);



registro r5;
Nat x5=75;
dato d17;
d17.nuevoDatoNat(x5);
r5.Definir(c,d17);

String u5="Holita";
dato d18;
d18.nuevoDatoString(u5);
r5.Definir(c1,d18);

Nat y5=25;
dato d19;
d19.nuevoDatoNat(y5);
r5.Definir(c2,d19);

String t7="Mateo";
dato d20;
d20.nuevoDatoString(t7);
r5.Definir(c3,d20);

n.indexar(c);
Conj<NombreCampo> ind;
ind.AgregarRapido(c);
ind.AgregarRapido(c1);
//ASSERT(n.indices()==ind);

n.agregarRegistro(r5); 

}



void BaseDeDatos(){
registro r;
NombreCampo c="hi";
Nat x=5;
dato d;
d.nuevoDatoNat(x);
r.Definir(c,d);

NombreCampo c1="lala";
String u="lolo";
dato d1;
d1.nuevoDatoString(u);
r.Definir(c1,d1);

NombreCampo c2="d";
Nat y=8;
dato d2;
d2.nuevoDatoNat(y);
r.Definir(c2,d2);

NombreCampo c3="mmm";
String t="toto";
dato d3;
d3.nuevoDatoString(t);
r.Definir(c3,d3);

Conj<NombreCampo> camp;
camp.Agregar(c);
tabla n;
String t1="TABLA";
n.nuevaTabla(t1,r,camp);
String nombre=n.nombre();
cout<< nombre<<endl;


registro r1;

r1.Definir(c,d);
r1.Definir(c1,d3);
r1.Definir(c2,d2);
r1.Definir(c3,d1);


registro r2;
Nat x1=1;
dato d5;
d5.nuevoDatoNat(x1);
r2.Definir(c,d5);

String u1="lalo";
dato d6;
d6.nuevoDatoString(u1);
r2.Definir(c1,d6);

Nat y1=2;
dato d7;
d7.nuevoDatoNat(y1);
r2.Definir(c2,d7);

String t4="tato";
dato d8;
d8.nuevoDatoString(t4);
r2.Definir(c3,d8);


registro r3;
Nat x2=89;
dato d9;
d9.nuevoDatoNat(x2);
r3.Definir(c,d9);

String u2="lalo";
dato d10;
d10.nuevoDatoString(u2);
r3.Definir(c1,d10);

Nat y2=25;
dato d11;
d11.nuevoDatoNat(y2);
r3.Definir(c2,d11);

String t5="tato";
dato d12;
d12.nuevoDatoString(t5);
r3.Definir(c3,d12);

registro r4;
Nat x4=778;
dato d13;
d13.nuevoDatoNat(x4);
r4.Definir(c,d13);

String u4="Hola";
dato d14;
d14.nuevoDatoString(u4);
r4.Definir(c1,d14);

Nat y4=249;
dato d15;
d15.nuevoDatoNat(y4);
r4.Definir(c2,d15);

String t6="Mato";
dato d16;
d16.nuevoDatoString(t6);
r4.Definir(c3,d16);


registro r5;
Nat x5=75;
dato d17;
d17.nuevoDatoNat(x5);
r5.Definir(c,d17);

String u5="Holita";
dato d18;
d18.nuevoDatoString(u5);
r5.Definir(c1,d18);

Nat y5=25;
dato d19;
d19.nuevoDatoNat(y5);
r5.Definir(c2,d19);

String t7="Mateo";
dato d20;
d20.nuevoDatoString(t7);
r5.Definir(c3,d20);


ASSERT(n.registros().Longitud() == 0);

BD b;

b.agregarTabla(n);

	//HAGO LA COLUMNA DE REFERENCIA
  registro col;
  
  dato d22;
  d.nuevoDatoString("perez");
  
  col.Definir("nombre",d22);
  col.Definir("apellido",d22);
  dato d23;
  Nat n23=1;
  d23.nuevoDatoNat(n23);
  col.Definir("LU",d23);
  col.Definir("Materia",d22);
  dato d24;
  d24.nuevoDatoNat(10);
  col.Definir("Nota",d24);
  col.Definir("eMail",d22);
  Conj<NombreCampo> claves;
  //DEFINO CAMPOS CLAVE
  claves.Agregar("LU");
  claves.Agregar("eMail");
  
  //cout << "HASTA ACA NO HAY ERROR"<< endl;

  //CREO TABLA 
  tabla t2;
  t2.nuevaTabla("candidatos_Para_Calesita_Pab2", col, claves);
  
  b.agregarTabla(t2);
  b.insertarEntrada(r,"TABLA");
  ASSERT(b.dameTabla("TABLA")->registros().Longitud() == 1);
  ASSERT(n.registros().Longitud() == 0); //COMPROBAMOS QUE SE AGREGA LA TABLA POR COPIA :)
  
  registro r18;
  dato charo;
  String s1="Charo";
  charo.nuevoDatoString(s1);
  dato olivera;
  String s2="Olivera";
  olivera.nuevoDatoString(s2);
  dato lU;
  Nat n3=11115;
  lU.nuevoDatoNat(n3);
  dato nota;
  Nat n4=5;
  nota.nuevoDatoNat(n4);
  dato materia;
  String s3="AED2";
  materia.nuevoDatoString(s3);
  dato email;
  String s4="laTurraDeSaavedra@turra.com";
  email.nuevoDatoString(s4);
  
  dato arregloDato [6]= {charo, olivera,  lU, materia, nota, email};
  Conj<NombreCampo> campos = t2.campos();
  DefinirRegistro(r18,campos, arregloDato);
  
  	b.insertarEntrada(r18,"candidatos_Para_Calesita_Pab2");
	b.insertarEntrada(r2,"TABLA");
	ASSERT(b.tablaMaxima() == "TABLA");
	//cout<< "Cant de accesos a 'candidatos_Para_Calesita_Pab2': " << b.cantDeAccesos("candidatos_Para_Calesita_Pab2")<<endl;	
	//cout<< "Cant de accesos a 'TABLA': " <<b.cantDeAccesos("TABLA")<<endl;	
	registro r19;
	r19.Definir(c1,d6);
	//cout<< "Cant de registros tabla en BD: " << b.dameTabla("TABLA")->registros().Longitud() <<endl;
	//cout<< "Cant de registros tabla fuera de BD: " << n.registros().Longitud() <<endl;
	b.borrar(r19, "TABLA");
	//cout<< "Cantidad de accesos a 'TABLA': " << b.cantDeAccesos("TABLA")<<endl;
	//cout<< "Cant de registros tabla en BD: " <<b.dameTabla("TABLA")->registros().Longitud() <<endl;
	//cout<< "Cant de registros tabla fuera de BD: " << n.registros().Longitud() <<endl;
	
	registro r20;
	dato d45;
	Nat n56=5;
	d45.nuevoDatoNat(n56);
	r20.Definir(c,d45);
	r20.Definir(c1,d6);
	r20.Definir("nombre",charo);
	Conj<NombreCampo> clv;
	clv.Agregar(c);
	

	tabla t3;
	t3.nuevaTabla("Tabla2", r20, clv);

	b.agregarTabla(t3);
	b.insertarEntrada(r20, "Tabla2");
	b.dameTabla("TABLA")->indexar(c);
	b.dameTabla("Tabla2")->indexar(c);
	b.dameTabla("TABLA")->indexar(c1);
	b.dameTabla("candidatos_Para_Calesita_Pab2")->indexar("LU");
    b.dameTabla("candidatos_Para_Calesita_Pab2")->indexar("eMail");
	b.generarVistaJoin("TABLA","Tabla2",c);
	ASSERT(b.hayJoin("TABLA","Tabla2"));
	b.insertarEntrada(r1,"TABLA");
	b.insertarEntrada(r3,"TABLA");
	b.borrar(r1,"TABLA");
	b.vistaJoin("TABLA","Tabla2");
	Lista<registro> cr=b.buscar(r20,"Tabla2");
	cout<< cr<<endl;
	//cout << "HASTA ACA NO HAY ERROR"<< endl;
	cr=b.buscar(r,"TABLA");
	cout<< cr<<endl;
	
}
int main(int argc, char **argv)
{
 RUN_TEST( ejemplo_simple );
	RUN_TEST(testTabla);
  RUN_TEST(agregarRegistroSinIndices);
  RUN_TEST(agregarRegConInd);
  RUN_TEST(BaseDeDatos);
  /********************************************************************
   * TODO: escribir casos de test exhaustivos para todas              *
   * las funcionalidades de cada módulo.                              *
   * La interacción con el TAD principal se debe hacer exclusivamente *
   * a través de la interfaz del driver.                              *
   ********************************************************************/

	return 0;
}
