#include <iostream>
#include "registro.h"
#include "dato.h"
#include "Conj.h"

using namespace std;
using namespace aed2;

int main(){

	Registro r3;
Nat x2=1;
dato d9;
d9.nuevoDatoNat(x2);
r3.Definir("campo",d9);

String u2="lalo";
dato d10;
d10.nuevoDatoString(u2);
r3.Definir("campo1",d10);

Nat y2=2;
dato d11;
d11.nuevoDatoNat(y2);
r3.Definir("campo2",d11);

String t5="tato";
dato d12;
d12.nuevoDatoString(t5);
r3.Definir("campo3",d12);

Registro r4;
Nat x4=78;
dato d13;
d13.nuevoDatoNat(x4);
r4.Definir("campo",d13);

String u4="Hola";
dato d14;
d14.nuevoDatoString(u4);
r4.Definir("campo1",d14);

Nat y4=24;
dato d15;
d15.nuevoDatoNat(y4);
r4.Definir("campo2",d15);

String t6="Mato";
dato d16;
d16.nuevoDatoString(t6);
r4.Definir("campo3",d16);


Registro r5;
Nat x5=75;
dato d17;
d17.nuevoDatoNat(x5);
r5.Definir("campo",d17);

String u5="Holita";
dato d18;
d18.nuevoDatoString(u5);
r5.Definir("campo1",d18);

Nat y5=25;
dato d19;
d19.nuevoDatoNat(y5);
r5.Definir("campo2",d19);

String t7="Mateo";
dato d20;
d20.nuevoDatoString(t7);
r5.Definir("campo3",d20);

	Lista<Registro> a;
	a.AgregarAtras(r3);
	a.AgregarAtras(r4);
	a.AgregarAtras(r5);

	cout << a << endl;
	return 0;
}