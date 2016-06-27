#include "registro.h"
#include "tabla.h"
#include "pair.h"
//#include <tuple>


using namespace aed2;
int main(){
/*	Registro r;
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
	t.nuevaTabla("t1",r, claves);
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
*/
	//dicA<Nat, Lista<tabla::estrAux> > indiceNat = t.dameColumnaNat();
	
	int arreglo [5]= {1,2,3,4,5};
	//////////////////////////////////////
	Registro col;
  	col.Definir("nombre",Dato("perez"));
  	col.Definir("apellido",Dato("perez"));
  	col.Definir("LU",Dato(1));
  	col.Definir("Materia",Dato("perez"));
  	col.Definir("Nota",Dato(10));
  	col.Definir("eMail",Dato("perez"));
  	Conj<NombreCampo> campos;
  	typename Registro::Iterador it = col.CrearIt();
	while(it.HaySiguiente()){
		campos.AgregarRapido(it.SiguienteClave());
		it.Avanzar();
	}
	typename Conj<NombreCampo>::Iterador it1= campos.CrearIt();
	while(it1.HaySiguiente()){
		std::cout<< it1.Siguiente() << std::endl;
		it1.Avanzar();
	}

	return 0;
}