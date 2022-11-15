#include "Containers/Map.hpp"
#include "Containers/Vector.hpp"

// #include "/Users/ade-la-c/goinfre/nathancontainers/vector/vector.hpp"

#include <map>

#define FT ft

int main(void) {

	FT::map<char, int> *	first = new FT::map<char, int>();
std::cerr<<"print"<<std::endl;

	first->insert(FT::make_pair('5', 5));
	first->insert(FT::pair<char, int>('5', 5));
	

	return 0;
}

// int main(void) {

// 	FT::vector<int> vec;

// 	for (size_t i = 0; i < 6; i++) {
// 		vec.push_back(i);
// 	}

// 	FT::vector<int>::iterator	it = vec.begin();
// 	FT::vector<int>::iterator	itb = vec.begin();
// 	FT::vector<int>::const_iterator	it2 = vec.begin();

// 	if (it == itb) { std::cout<<"cool cça marchee"<<std::endl; }

// }
