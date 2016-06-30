// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>

#include "Driver.h"
#include "mini_test.h"
#include "tabla.h"
#include "BD.h"
#include <string>
#include <iostream>

using namespace std;
using namespace aed2;

int main(){
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

BD b=BD();
b.agregarTabla(n);


Registro crit;
crit.Definir(c,d);

Registro r1;

r1.Definir(c,d);
r1.Definir(c1,d3);
r1.Definir(c2,d2);
r1.Definir(c3,d1);



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




}
