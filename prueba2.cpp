#include "registro.h"
#include "tabla.h"
#include "pair.h"
//#include <tuple>


using namespace aed2;
int main(){
	Lista <int> a;
	int i=0;
	while(i<10){
		a.AgregarAtras(i);
		i++;
	}
	typename Lista<int>::Iterador it = a.CrearIt();
	while(it.HaySiguiente()){
		cout << it.Siguiente() << " ,";
		it.Avanzar();
	}

	cout << "\n"<<endl;
	it=a.CrearItUlt();
	it.Retroceder();
	it.AgregarComoSiguiente(10);
	it.Avanzar();
	while(it.HayAnterior()){
		cout << it.Anterior() << " ,";
		it.Retroceder();
	} 



	cout << "\n"<<endl;
	return 0;
}