#include "Containers/Map.hpp"
#include <map>

#define FT std

// void	print_map(ft::map) {

// }

int main(void) {

	FT::map<char, int> *	first = new FT::map<char, int>();
std::cerr<<"print"<<std::endl;

	first->insert(FT::make_pair('5', 5));
	first->insert(FT::pair<char, int>('5', 5));
	

	return 0;
}
