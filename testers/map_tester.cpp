#include "../Containers/map.hpp"
// #include "/Users/ade-la-c/Desktop/cont_namenega/map/map.hpp"
#include <iostream>
#include <map>

#ifndef FT
 #define FT ft
#endif

void map_testing( void );

/* ************************************************************************** */
/* *********************** Constructors, Destructors ************************ */
/* ************************************************************************** */

void	map_constructor_test(void) {
	FT::map<char, int>	first;
	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 17;
	std::cout << "Map first contains :\n";
	for (FT::map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ], ";
	std::cout << std::endl << std::endl;

	FT::map<char, int>	second(first.begin(), first.end());
	std::cout << "Map second contains :\n";
	for (FT::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ], ";
	std::cout << std::endl << std::endl;

	FT::map<char, int>	third(second);
	std::cout << "Map third contains :\n";
	for (FT::map<char, int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ], ";
	std::cout << std::endl;
}

void	real_map_constructor_test(void) {
	std::map<char, int>	first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 17;
	std::cout << "Map first contains :\n";
	for (std::map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ], ";
	std::cout << std::endl << std::endl;

	std::map<char, int>	second(first.begin(), first.end());
	std::cout << "Map second contains :\n";
	for (std::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ], ";
	std::cout << std::endl << std::endl;

	std::map<char, int>	third(second);
	std::cout << "Map third contains :\n";
	for (std::map<char, int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ], ";
	std::cout << std::endl;
}

/* ************************************************************************** */

void	map_operator_test(void) {
	FT::map<char, int>	first;
	FT::map<char, int>	second;

	first['x'] = 8;
	first['y'] = 16;
	first['z'] = 32;

	second = first;
	first = FT::map<char, int>();

	std::cout << "Size first : " << first.size() << std::endl;
	std::cout << "Size second : " << second.size() << std::endl;
}

void	real_map_operator_test(void) {
	std::map<char, int>	first;
	std::map<char, int>	second;

	first['x'] = 8;
	first['y'] = 16;
	first['z'] = 32;

	second = first;
	first = std::map<char, int>();

	std::cout << "Size first : " << first.size() << std::endl;
	std::cout << "Size second : " << second.size() << std::endl;
}

/* ************************************************************************** */
/* ******************************** Iterators ******************************* */
/* ************************************************************************** */

void	map_begin_end_test(void) {
	FT::map<char, int>	mapp;

	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;
	std::cout << "Mapp contains :\n";
	for (FT::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); ++it) {
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	}
}

void	real_map_begin_end_test(void) {
	std::map<char, int>	mapp;

	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;
	std::cout << "Mapp contains :\n";
	for (std::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); ++it)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

/* ************************************************************************** */

void	map_rbegin_rend_test(void) {
	FT::map<char, int>	mapp;

	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;
	std::cout << "Mapp contains :\n";
	for (FT::map<char, int>::reverse_iterator rit = mapp.rbegin(); rit != mapp.rend(); ++rit)
		std::cout << "[ " << rit->first << " : " << rit->second << " ]" << std::endl;
}

void	real_map_rbegin_rend_test(void) {
	std::map<char, int>	mapp;

	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;
	std::cout << "Mapp contains :\n";
	for (std::map<char, int>::reverse_iterator rit = mapp.rbegin(); rit != mapp.rend(); ++rit)
		std::cout << "[ " << rit->first << " : " << rit->second << " ]" << std::endl;
}

/* ************************************************************************** */
/* ******************************** Capacity ******************************** */
/* ************************************************************************** */

void	map_empty_test(void) {
	FT::map<char, int>	mapp;

	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;
	while (!mapp.empty()) {
		std::cout << "[ " << mapp.begin()->first << " : " << mapp.begin()->second << " ]" << std::endl;
		mapp.erase(mapp.begin());
	}
}

void	real_map_empty_test(void) {
	std::map<char, int>	mapp;

	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;
	while (!mapp.empty()) {
		std::cout << "[ " << mapp.begin()->first << " : " << mapp.begin()->second << " ]" << std::endl;
		mapp.erase(mapp.begin());
	}
}

/* ************************************************************************** */

void	map_size_test(void) {
	FT::map<char, int>	mapp;

	mapp['w'] = 4;
	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;

	std::cout << "Map.size = " << mapp.size() << std::endl;
}

void	real_map_size_test(void) {
	std::map<char, int>	mapp;

	mapp['w'] = 4;
	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;

	std::cout << "Map.size = " << mapp.size() << std::endl;
}

/* ************************************************************************** */

void	map_max_size_test(void) {
	FT::map<char, int>	mapp;

	mapp['w'] = 4;
	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;

	std::cout << "Map.max_size = " << mapp.max_size() << std::endl;
}

void	real_map_max_size_test(void) {
	std::map<char, int>	mapp;

	mapp['w'] = 4;
	mapp['x'] = 8;
	mapp['y'] = 16;
	mapp['z'] = 32;

	std::cout << "Map.max_size = " << mapp.max_size() << std::endl;
}

/* ************************************************************************** */
/* **************************** Elements Access ***************************** */
/* ************************************************************************** */

void	map_element_access_operator_test(void) {
	FT::map<char, std::string>	mapp;

	mapp['x'] = "pikachu";
	mapp['y'] = "charmander";
	mapp['z'] = mapp['y'];
	std::cout << "[ " << mapp['x'] << " ]" << std::endl;
	std::cout << "[ " << mapp['y'] << " ]" << std::endl;
	std::cout << "[ " << mapp['z'] << " ]" << std::endl;
	std::cout << "[ " << mapp['w'] << " ]" << std::endl;
	std::cout << "Mapp contains : [ " << mapp.size() << " ] elements." << std::endl;
}

void	real_map_element_access_operator_test(void) {
	std::map<char, std::string>	mapp;

	mapp['x'] = "pikachu";
	mapp['y'] = "charmander";
	mapp['z'] = mapp['y'];
	std::cout << "[ " << mapp['x'] << " ]" << std::endl;
	std::cout << "[ " << mapp['y'] << " ]" << std::endl;
	std::cout << "[ " << mapp['z'] << " ]" << std::endl;
	std::cout << "[ " << mapp['w'] << " ]" << std::endl;
	std::cout << "Mapp contains : [ " << mapp.size() << " ] elements." << std::endl;
}

/* ************************************************************************** */
/* ******************************* Modifiers ******************************** */
/* ************************************************************************** */

void	map_insert_test(void) {
	FT::map<char, int>	mapp;

	mapp.insert(FT::pair<char, int>('a', 100));
	mapp.insert(FT::pair<char, int>('z', 200));

	FT::pair<FT::map<char, int>::iterator, bool>	ret;
	ret = mapp.insert(FT::pair<char, int>('z', 500));
	if (ret.second == false) {
		std::cout << "1. Element 'z' already existed with a value of " << ret.first->second
			<< std::endl << std::endl;
	}

	FT::map<char, int>::iterator	it = mapp.begin();
	mapp.insert(it, FT::pair<char, int>('b', 300));
	mapp.insert(it, FT::pair<char, int>('c', 400));
	std::cout << "2. Map size : " << mapp.size() << std::endl << std::endl;

	FT::map<char, int>	mapp2;
	mapp2.insert(mapp.begin(), mapp.find('c'));
	std::cout << "3. Mapp contains :" << std::endl;
	for (it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl << "   Mapp2 contains :" << std::endl;
	for (it = mapp2.begin(); it != mapp2.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

void	real_map_insert_test(void) {
	std::map<char, int>	mapp;

	mapp.insert(std::pair<char, int>('a', 100));
	mapp.insert(std::pair<char, int>('z', 200));

	std::pair<std::map<char, int>::iterator, bool>	ret;
	ret = mapp.insert(std::pair<char, int>('z', 500));
	if (ret.second == false) {
		std::cout << "1. Element 'z' already existed with a value of " << ret.first->second
			<< std::endl << std::endl;
	}

	std::map<char, int>::iterator	it = mapp.begin();
	mapp.insert(it, std::pair<char, int>('b', 300));
	mapp.insert(it, std::pair<char, int>('c', 400));
	std::cout << "2. Map size : " << mapp.size() << std::endl << std::endl;

	std::map<char, int>	mapp2;
	mapp2.insert(mapp.begin(), mapp.find('c'));
	std::cout << "3. Mapp contains :" << std::endl;
	for (it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl << "   Mapp2 contains :" << std::endl;
	for (it = mapp2.begin(); it != mapp2.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

/* ************************************************************************** */

void	map_erase_test(void) {
	FT::map<char, int>				mapp;
	FT::map<char, int>::iterator	it;

	mapp['a'] = 4;
	mapp['b'] = 8;
	mapp['c'] = 16;
	mapp['d'] = 32;
	mapp['e'] = 64;
	mapp['f'] = 128;

	it = mapp.find('b');
	mapp.erase(it);
	mapp.erase('c');

	std::cout << std::endl << "Mapp contains :" << std::endl;
	for (it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

void	real_map_erase_test(void) {
	std::map<char, int>				mapp;
	std::map<char, int>::iterator	it;

	mapp['a'] = 4;
	mapp['b'] = 8;
	mapp['c'] = 16;
	mapp['d'] = 32;
	mapp['e'] = 64;
	mapp['f'] = 128;

	it = mapp.find('b');
	mapp.erase(it);
	mapp.erase('c');

	std::cout << std::endl << "Mapp contains :" << std::endl;
	for (it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

/* ************************************************************************** */

void	map_swap_test(void) {
	FT::map<char, int>	mapp, mapp2;

	mapp['x'] = 100;
	mapp['y'] = 200;
	mapp2['a'] = 10;
	mapp2['b'] = 11;
	mapp2['c'] = 12;

	mapp.swap(mapp2);
	std::cout << std::endl << "Mapp contains :" << std::endl;
	for (FT::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl << "Mapp2 contains :" << std::endl;
	for (FT::map<char, int>::iterator it = mapp2.begin(); it != mapp2.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

void	real_map_swap_test(void) {
	std::map<char, int>	mapp, mapp2;

	mapp['x'] = 100;
	mapp['y'] = 200;
	mapp2['a'] = 10;
	mapp2['b'] = 11;
	mapp2['c'] = 12;

	mapp.swap(mapp2);
	std::cout << std::endl << "Mapp contains :" << std::endl;
	for (std::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl << "Mapp2 contains :" << std::endl;
	for (std::map<char, int>::iterator it = mapp2.begin(); it != mapp2.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

/* ************************************************************************** */

void	map_clear_test(void) {
	FT::map<char, int>	mapp;

	mapp['x'] = 100;
	mapp['y'] = 200;
	mapp['z'] = 300;

	std::cout << "Mapp contains :" << std::endl;
	for (FT::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl;

	mapp.clear();
	mapp['a'] = 500;
	mapp['b'] = 600;

	std::cout << "Mapp contains :" << std::endl;
	for (FT::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

void	real_map_clear_test(void) {
	std::map<char, int>	mapp;

	mapp['x'] = 100;
	mapp['y'] = 200;
	mapp['z'] = 300;

	std::cout << "Mapp contains :" << std::endl;
	for (std::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	std::cout << std::endl;
mapp.erase(mapp.begin(), mapp.end());
	mapp.clear();
	mapp['a'] = 500;
	mapp['b'] = 600;

	std::cout << "Mapp contains :" << std::endl;
	for (std::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

/* ************************************************************************** */
/* ******************************* Observers ******************************** */
/* ************************************************************************** */

void	map_key_comp_test(void) {
	FT::map<char, int>	mapp;
	FT::map<char, int>::key_compare	compp = mapp.key_comp();

	mapp['x'] = 100;
	mapp['y'] = 200;
	mapp['z'] = 300;
	std::cout << "Mapp contains :" << std::endl;
	char	highest = mapp.rbegin()->first;
	FT::map<char, int>::iterator it = mapp.begin();
	do {
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	} while (compp((*it++).first, highest));
}

void	real_map_key_comp_test(void) {
	std::map<char, int>	mapp;
	std::map<char, int>::key_compare	compp = mapp.key_comp();

	mapp['x'] = 100;
	mapp['y'] = 200;
	mapp['z'] = 300;
	std::cout << "Mapp contains :" << std::endl;
	char	highest = mapp.rbegin()->first;
	std::map<char, int>::iterator it = mapp.begin();
	do {
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	} while (compp((*it++).first, highest));
}

/* ************************************************************************** */

void	map_value_comp_test(void) {
	FT::map<char, int>	mapp;

	mapp['x'] = 100;
	mapp['y'] = 200;
	mapp['z'] = 300;
	std::cout << "Mapp contains :" << std::endl;
	FT::pair<char, int>				highest = *mapp.rbegin();
	FT::map<char, int>::iterator	it = mapp.begin();
	do {
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	} while (mapp.value_comp()(*it++, highest));
}

void	real_map_value_comp_test(void) {
	std::map<char, int>	mapp;

	mapp['x'] = 100;
	mapp['y'] = 200;
	mapp['z'] = 300;
	std::cout << "Mapp contains :" << std::endl;
	std::pair<char, int>				highest = *mapp.rbegin();
	std::map<char, int>::iterator	it = mapp.begin();
	do {
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
	} while (mapp.value_comp()(*it++, highest));
}

/* ************************************************************************** */

void	map_find_test(void) {
	FT::map<char, int>				mapp;
	FT::map<char, int>::iterator	it;

	mapp['a'] = 100;
	mapp['b'] = 200;
	mapp['c'] = 300;
	mapp['d'] = 400;
	mapp['e'] = 500;
	mapp['f'] = 600;
	it = mapp.find('b');
	if (it != mapp.end())
		mapp.erase(it);
	std::cout << "Mapp contains :" << std::endl;
	for (it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

void	real_map_find_test(void) {
	std::map<char, int>				mapp;
	std::map<char, int>::iterator	it;

	mapp['a'] = 100;
	mapp['b'] = 200;
	mapp['c'] = 300;
	mapp['d'] = 400;
	mapp['e'] = 500;
	mapp['f'] = 600;
	it = mapp.find('b');
	if (it != mapp.end())
		mapp.erase(it);
	std::cout << "Mapp contains :" << std::endl;
	for (it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

/* ************************************************************************** */

void	map_count_test(void) {
	FT::map<char, int>	mapp;

	mapp['a'] = 100;
	mapp['d'] = 200;
	mapp['f'] = 300;
	mapp['j'] = 400;
	for (char c = 'a'; c < 'n'; c++) {
		std::cout << c;
		if (mapp.count(c) == 1)
			std::cout << " is an element of mapp." << std::endl;
		else
			std::cout << " is not an element of mapp." << std::endl;
	}
}

void	real_map_count_test(void) {
	std::map<char, int>	mapp;

	mapp['a'] = 100;
	mapp['d'] = 200;
	mapp['f'] = 300;
	mapp['j'] = 400;
	for (char c = 'a'; c < 'n'; c++) {
		std::cout << c;
		if (mapp.count(c) == 1)
			std::cout << " is an element of mapp." << std::endl;
		else
			std::cout << " is not an element of mapp." << std::endl;
	}
}

/* ************************************************************************** */

void	map_lower_upper_bound_test(void) {
	FT::map<char, int>				mapp;

	mapp['a'] = 100;
	mapp['b'] = 200;
	mapp['c'] = 300;
	mapp['d'] = 400;
	mapp['e'] = 500;
	
	FT::map<char, int>::iterator	lowit = mapp.lower_bound('b');
	FT::map<char, int>::iterator	upit = mapp.upper_bound('d');
	mapp.erase(lowit, upit);
	std::cout << "Mapp contains :" << std::endl;
	for (FT::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;
}

void	real_map_lower_upper_bound_test(void) {
	std::map<char, int>				mapp;

	mapp['a'] = 100;
	mapp['b'] = 200;
	mapp['c'] = 300;
	mapp['d'] = 400;
	mapp['e'] = 500;
	
	std::map<char, int>::iterator	lowit = mapp.lower_bound('b');
	std::map<char, int>::iterator	upit = mapp.upper_bound('d');
	mapp.erase(lowit, upit);
	std::cout << "Mapp contains :" << std::endl;
	for (std::map<char, int>::iterator it = mapp.begin(); it != mapp.end(); it++)
		std::cout << "[ " << it->first << " : " << it->second << " ]" << std::endl;

}

/* ************************************************************************** */

void	map_equal_range_test(void) {
	FT::map<char, int>	mapp;

	mapp['a'] = 100;
	mapp['b'] = 200;
	mapp['c'] = 300;
	mapp['d'] = 400;
	mapp['e'] = 500;
	mapp['f'] = 600;
	FT::pair<FT::map<char, int>::iterator, FT::map<char, int>::iterator>	ret;
	ret = mapp.equal_range('d');

	std::cout << "Lower bound points to :" << std::endl;
	std::cout << "[ " << ret.first->first << " : " << ret.first->second << " ]" << std::endl;
	std::cout << "Upper bound points to :" << std::endl;
	std::cout << "[ " << ret.second->first << " : " << ret.second->second << " ]" << std::endl;
}

void	real_map_equal_range_test(void) {
	std::map<char, int>	mapp;

	mapp['a'] = 100;
	mapp['b'] = 200;
	mapp['c'] = 300;
	mapp['d'] = 400;
	mapp['e'] = 500;
	mapp['f'] = 600;
	std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator>	ret;
	ret = mapp.equal_range('d');

	std::cout << "Lower bound points to :" << std::endl;
	std::cout << "[ " << ret.first->first << " : " << ret.first->second << " ]" << std::endl;
	std::cout << "Upper bound points to :" << std::endl;
	std::cout << "[ " << ret.second->first << " : " << ret.second->second << " ]" << std::endl;
}

/* ************************************************************************** */

void	map_get_allocator_test(void) {
	int							psize;
	FT::map<char, int>			mapp;
	FT::pair<const char, int>	*p;

	p = mapp.get_allocator().allocate(5);
	psize = sizeof(FT::map<char, int>::value_type) * 5;

	std::cout << "The allocated array has a size of " << psize << " bytes." << std::endl;
	mapp.get_allocator().deallocate(p, 5);
}

void	real_map_get_allocator_test(void) {
	int							psize;
	std::map<char, int>			mapp;
	std::pair<const char, int>	*p;

	p = mapp.get_allocator().allocate(5);
	psize = sizeof(std::map<char, int>::value_type) * 5;

	std::cout << "The allocated array has a size of " << psize << " bytes." << std::endl;
	mapp.get_allocator().deallocate(p, 5);
}
// */
/* ************************************************************************** */

void	map_testing(void) {
	std::cout << "\033[1;36m/* ******** Map Constructor Test *********** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_constructor_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_constructor_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Operators Test ************* */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_operator_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_operator_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Begin/End Test ************* */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_begin_end_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_begin_end_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Rbegin/Rend Test *********** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_rbegin_rend_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_rbegin_rend_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Empty Test ***************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_empty_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_empty_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Size Test ****************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_size_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_size_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Max_size Test ************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_max_size_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_max_size_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Operator[] Test ************ */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_element_access_operator_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_element_access_operator_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Insert Test **************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_insert_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_insert_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Erase Test ***************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_erase_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_erase_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Swap Test ****************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_swap_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_swap_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Clear Test ***************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_clear_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_clear_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Key_comp Test ************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_key_comp_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_key_comp_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Value_comp Test ************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_value_comp_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_value_comp_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Find Test ****************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_find_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_find_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Count Test ***************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_count_test();
	
	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_count_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Lower/Upper_bond Test ****** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_lower_upper_bound_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_lower_upper_bound_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Equal_range Test *********** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_equal_range_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_equal_range_test();

	std::cout << std::endl;
	std::cout << "\033[1;36m/* ******** Map Get_allocator Test *********** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;36mMINE\033[0m :" << std::endl;
	map_get_allocator_test();

	std::cout << std::endl;
	std::cout << "\033[1;36mREAL\033[0m :" << std::endl;
	real_map_get_allocator_test();
}

// int		main( void ) {
// 	/* ********************************************************************** */
// 	/* ****************************** TESTS MAP ***************************** */
// 	/* ********************************************************************** */
// 	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
// 	std::cout << "\033[1;34m/* **************** TESTS MAP ************** */\033[0m" << std::endl;
// 	std::cout << "\033[1;34m/* ***************************************** */\033[0m" << std::endl;
// 	std::cout << std::endl;

// 	map_testing();
// 	return 0;
// }
