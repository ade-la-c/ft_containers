#include "Containers/map.hpp"
#include "Containers/vector.hpp"

// #include "/Users/ade-la-c/goinfre/nathancontainers/vector/vector.hpp"

#include <map>

#define FT ft

int main(void) {

	FT::map<char, int> *	first = new FT::map<char, int>();
std::cerr<<"print"<<std::endl;

	first->insert(FT::pair<char, int>('1', 1));
	first->insert(FT::pair<char, int>('2', 2));
	first->insert(FT::pair<char, int>('3', 3));
	first->insert(FT::pair<char, int>('4', 4));


	FT::map<char, int>::iterator	it;

	first->insert(first->begin(), first->end());

	std::cout<<"first:"<<std::endl;
	for (it = first->begin(); it != first->end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;

	ft::distance(first->begin(), first->end());
	FT::map<char, int> *	second = new FT::map<char, int>(first->begin(), first->end());

	// second->insert(first->begin(), first->end());

	std::cout<<"second:"<<std::endl;
	for (it = second->begin(); it != second->end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;


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
