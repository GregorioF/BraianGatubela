#include <iostream>
#include <stdlib.h>
#include "registro.h"
#include "tabla.h"
#include "pair.h"
//#include <tuple>


int main(){

	aed2::pair<int, int> a;
	a.make_pair(2,3);

	std::cout << a.first()<<std::endl;
	a.first()= 5;
	std::cout << a.first()<< std::endl;

	return 0;
}