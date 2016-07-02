#ifndef PAR_H
#define PAR_H



namespace aed2
{

template <typename K, typename T>
class par{
public:
	par();
	par(const par& otro);
	~par();
	void make_par(const K elem1, const T elem2);
	K& first();
	T& second();


private:
	K first_;
	T second_;
};
template <typename K, typename T>
par<K,T>::par(){}

template <typename K, typename T>
par<K,T>::par(const par& otro){
	first_=otro.first_;
	second_=otro.second_;
	//make_par(otro.first(), otro.second());
}

template <typename K, typename T>
par<K,T>::~par(){}

template <typename K, typename T>
void par<K,T>::make_par(const K elem1, const T elem2){
	first_=elem1;
	second_=elem2;
}

template <typename K, typename T>
K& par<K,T>::first(){
	return first_;
}

template <typename K, typename T>
T& par<K,T>::second(){
	return second_;
}
}

#endif
