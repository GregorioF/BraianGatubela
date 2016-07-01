#include <iostream>
#include "registro.h"
#include "dato.h"

using namespace std;
using namespace aed2;

int main(){

	Registro r;
	String c1 = "LU";
	dato d1;
	d1.nuevoDatoNat(3);

	String c2 ="Nombre";
	dato d2;
	d2.nuevoDatoString("tuvi");

	//cout << d2.tipo() << endl;

	String c3= "Idolo";
	dato d3;
	d3.nuevoDatoString("gregorio");

	r.Definir(c1,d1);
	r.Definir(c2,d2);
	r.Definir(c3,d3);


	cout << r << endl;
	return 0;
}