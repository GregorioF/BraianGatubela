#ifndef PAR_H
#define PAR_H



namespace aed2
{

template <typename K, typename T>
class pair{
public:
	pair();
	pair(const pair& otro);
	~pair();
	void make_pair(const K elem1, const T elem2);
	K& first();
	T& second();


private:
	K first_;
	T second_;
};
template <typename K, typename T>
pair<K,T>::pair(){}

template <typename K, typename T>
pair<K,T>::pair(const pair& otro){
	make_pair(otro.first(), otro.second());
}

template <typename K, typename T>
pair<K,T>::~pair(){}

template <typename K, typename T>
void pair<K,T>::make_pair(const K elem1, const T elem2){
	first_=elem1;
	second_=elem2;
}

template <typename K, typename T>
K& pair<K,T>::first(){
	return first_;
}

template <typename K, typename T>
T& pair<K,T>::second(){
	return second_;
}
}

#endif