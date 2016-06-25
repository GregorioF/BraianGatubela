#include "registro.h"
#include "tabla.h"
#include "pair.h"
//#include <tuple>


using namespace aed2;
int main(){
	Registro r;
	Nat x= 3;
	Dato a (43);
	Dato s ("pachorro");
	string str= "hola";
	r.Definir("hola",  a);
	r.Definir("asterix", s);
	tabla t;
	Conj<NombreCampo> claves;
	claves.AgregarRapido("hola");
	claves.AgregarRapido("asterix");
	t.nuevaTabla("t1",claves,r);
	t.agregarRegistro(r);
	bool c= t.tipoCampo("hola")==STR;
	std::cout<< c << std::endl;
	t.indexar("hola");

	//////////////////////////////////////
	

	return 0;
}