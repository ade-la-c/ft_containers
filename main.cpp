#include "Containers/map.hpp"
#include "Containers/vector.hpp"
#include "Containers/stack.hpp"

#define FT ft

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

void	map_testing( void );
void	vector_testing( void );
void	stack_testing( void );

//////////*

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

void	printSize(ft::map<char, int> const * mp, bool print_content = 1)
{
	std::cout << "size: " << mp->size() << std::endl;
	std::cout << "max_size: " << mp->max_size() << std::endl;
	if (print_content)
	{
		ft::map<char, int>::const_iterator it = mp->begin(), ite = mp->end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

//* //////

int	main( void ) {

	FT::map<char, int> *	mapp = new FT::map<char, int>();

	mapp->insert(ft::pair<char, int>('1', 1));
	mapp->insert(ft::pair<char, int>('3', 3));
	mapp->insert(ft::pair<char, int>('2', 2));
	mapp->insert(ft::pair<char, int>('5', 5));
	mapp->insert(ft::pair<char, int>('4', 4));
	mapp->insert(ft::pair<char, int>('7', 7));
	mapp->insert(ft::pair<char, int>('6', 6));

	ft::map<char, int>::iterator	it = mapp->begin();
	ft::map<char, int>::iterator	it2 = mapp->begin();

	printSize(mapp, 1);

	++(++(++(++(++(it2)))));

	mapp->erase(it, it2);

	printSize(mapp, 1);

	return 0;
}

// void	map_script(void) {
// 	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
// 	std::cout << "\033[1;34m/* ************** TEST MAP ***************** */\033[0m" << std::endl;
// 	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
// 	std::cout << std::endl;

// 	map_testing();
// }

// void	vector_script(void) {
// 	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
// 	std::cout << "\033[1;34m/* ************** TEST VECTORS ************* */\033[0m" << std::endl;
// 	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
// 	std::cout << std::endl;

// 	vector_testing();
// }

// void	stack_script(void) {
// 	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
// 	std::cout << "\033[1;34m/* ************** TEST STACK *************** */\033[0m" << std::endl;
// 	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
// 	std::cout << std::endl;

// 	stack_testing();
// }

// void	print(std::string str, std::string col, std::string reset) {
// 	std::cout << col << str << reset << std::endl;
// }

// int		main() {
// 	std::string		line;

// 	print("Hello and welcome to FT_CONTAINERS.", GREEN, RESET);
// 	print("What container do you want to see ?", GREEN, RESET);
// 	std::cout << std::endl;
// 	print("1. Stack", RED, RESET);
// 	print("2. Vector", MAGENTA, RESET);
// 	print("3. Map", CYAN, RESET);
// 	print("4. End", BLUE, RESET);
// 	std::cout << std::endl;
// 	while (1) {
// 		print("Select the number (1/2/3/4) :", GREEN, RESET);
// 		if (!getline(std::cin, line))
// 			print("Select the number (1/2/3/4) :", GREEN, RESET);
// 		if (line == "1")
// 			stack_script();
// 		else if (line == "2")
// 			vector_script();
// 		else if (line == "3")
// 			map_script();
// 		else if (line == "4") {
// 			print("Thank you ! See you soon.", BLUE, RESET);
// 			break;
// 		}

// 	}
// 	return (0);
// }



/*.
#include <stack>
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

std::stack<int> i();
std::stack<int> j();
if (i < j) return 1;

	return 0;
}
// */

/*.
int main(void) {

	FT::vector<int> vec;

	for (size_t i = 0; i < 6; i++) {
		vec.push_back(i);
	}

	FT::vector<int>::iterator	it = vec.begin();
	FT::vector<int>::iterator	itb = vec.begin();
	FT::vector<int>::const_iterator	it2 = vec.begin();

	if (it == itb) { std::cout<<"cool cça marchee"<<std::endl; }

}
// */
