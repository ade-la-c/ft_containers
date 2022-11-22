#include "Containers/map.hpp"
#include "Containers/vector.hpp"
#include "Containers/stack.hpp"

int	main( void ) {
	ft::map<char, int>	first;
	ft::map<char, int>	second;
	first['x'] = 8;
	first['y'] = 16;
	first['z'] = 32;

	second = first;
	first = ft::map<char, int>();

	std::cout << "Size first : " << first.size() << std::endl;
	std::cout << "Size second : " << second.size() << std::endl;
}
