#include <iostream>
#include "Conj.h"
#include "dicA.h"

using namespace std;
using namespace aed2;

int main(){
	Lista< dicA<int,int> > ld;
	dicA<int, int> j;
	int a =3;
	j.definir(3,a);
	//int a;
	ld.AgregarAtras(j);
	


	return 0;
}