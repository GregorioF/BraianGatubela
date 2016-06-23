#include <iostream>
#include "Conj.h"
#include "dicA.h"
#include "dicT.h"

using namespace std;
using namespace aed2;

int main(){
	Lista< dicT<int> > ld;
	dicA<int, int> da;
	int a=3;
	da.definir(a,a);

	dicT<int> dt;
	dt.definir("hola", a);

	ld.AgregarAtras(dt);

	return 0;
}