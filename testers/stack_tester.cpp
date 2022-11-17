#include "../Containers/stack.hpp"

#include <iostream>
#include <stack>

#ifndef FT
 #define FT ft
#endif

void	stack_empty_test(void) {
	FT::stack<int>		st;
	int					sum = 0;

	for (int i = 1; i <= 10; i++)
		st.push(i);
	while (!st.empty()) {
		sum += st.top();
		st.pop();
	}
	std::cout << "Total: " << sum << std::endl;
}

void	real_stack_empty_test(void) {
	std::stack<int>		st;
	int					sum = 0;

	for (int i = 1; i <= 10; i++)
		st.push(i);
	while (!st.empty()) {
		sum += st.top();
		st.pop();
	}
	std::cout << "Total: " << sum << std::endl;
}

/* ************************************************************************** */

void	stack_size_test(void) {
	FT::stack<int>		tab;

	std::cout << "0. Size : " << tab.size() << std::endl;
	for (int i = 0; i < 5; i++)
		tab.push(i);
	std::cout << "1. Size : " << tab.size() << std::endl;
	tab.pop();
	std::cout << "2. Size : " << tab.size() << std::endl;
}

void	real_stack_size_test(void) {
	std::stack<int>		tab;

	std::cout << "0. Size : " << tab.size() << std::endl;
	for (int i = 0; i < 5; i++)
		tab.push(i);
	std::cout << "1. Size : " << tab.size() << std::endl;
	tab.pop();
	std::cout << "2. Size : " << tab.size() << std::endl;
}

/* ************************************************************************** */

void	stack_top_test(void) {
	FT::stack<int>		tab;

	tab.push(10);
	tab.push(50);

	tab.top() -= 5;
	std::cout << "Tab.top() is now " << tab.top() << std::endl;
}

void	real_stack_top_test(void) {
	std::stack<int>		tab;

	tab.push(10);
	tab.push(50);

	tab.top() -= 5;
	std::cout << "Tab.top() is now " << tab.top() << std::endl << std::endl;
}

/* ************************************************************************** */

void	stack_testing(void) {
	std::cout << "\033[1;31m/* ******** Stack Empty Test *************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;31mMINE\033[0m :" << std::endl;
	std::cout << std::endl;
	stack_empty_test();
	std::cout << std::endl;
	std::cout << "\033[1;31mREAL\033[0m :" << std::endl;
	std::cout << std::endl;
	real_stack_empty_test();

	std::cout << std::endl;
	std::cout << "\033[1;31m/* ******** Stack Size Test **************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;31mMINE\033[0m :" << std::endl;
	std::cout << std::endl;
	stack_size_test();
	std::cout << std::endl;
	std::cout << "\033[1;31mREAL\033[0m :" << std::endl;
	std::cout << std::endl;
	real_stack_size_test();

	std::cout << std::endl;
	std::cout << "\033[1;31m/* ******** Stack Top Test ***************** */\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "\033[1;31mMINE\033[0m :" << std::endl;
	std::cout << std::endl;
	stack_top_test();
	std::cout << std::endl;
	std::cout << "\033[1;31mREAL\033[0m :" << std::endl;
	std::cout << std::endl;
	real_stack_top_test();
}

int main() {
	stack_testing();
}
