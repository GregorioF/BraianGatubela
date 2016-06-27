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
	t.indexar("asterix");
	Conj<NombreCampo> indices= t.indices();
	typename Conj<NombreCampo>::Iterador it = indices.CrearIt();
	while(it.HaySiguiente()){
		std::cout << it.Siguiente() << std::endl;
		it.Avanzar();
	}

	//dicA<Nat, Lista<tabla::estrAux> > indiceNat = t.dameColumnaNat();
	
	Conj<Nat> claveDeINat= t.dameColumnaNat().claves();
	typename Conj<Nat>::Iterador itINat= claveDeINat.CrearIt();
	while(itINat.HaySiguiente()){
		std::cout << itINat.Siguiente()<< std::endl;
		itINat.Avanzar();
	}

	//////////////////////////////////////
	

	return 0;
}