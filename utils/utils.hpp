#pragma once


#include <iostream>
#include <cstddef>
#include <limits>
#include <sstream>
#include <typeinfo>

#include "iterator_traits.hpp"



namespace	ft {




	//* enable_if structures
	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };
	// */

	//* is_integral

	template<bool is_integral, typename T>
	struct	is_integral_res {

		typedef T			type;
		static const bool	value = is_integral;
	};

	template<typename>
	struct	is_integral_type : public is_integral_res<false, bool> {};
	template<>
	struct	is_integral_type<bool> : public is_integral_res<true, bool> {};
	template<>
	struct	is_integral_type<char> : public is_integral_res<true, char> {};
	template<>
	struct	is_integral_type<signed char> : public is_integral_res<true, signed char> {};
	template<>
	struct	is_integral_type<short int> : public is_integral_res<true, short int> {};
	template<>
	struct	is_integral_type<int> : public is_integral_res<true, int> {};
	template<>
	struct	is_integral_type<long int> : public is_integral_res<true, long int> {};
	template<>
	struct	is_integral_type<long long int> : public is_integral_res<true, long long int> {};
	template<>
	struct	is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
	template<>
	struct	is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
	template<>
	struct	is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
	template<>
	struct	is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
	template<>
	struct	is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template<typename T>
	struct	is_integral : public is_integral_type<T> {};

	// */

	//*	Iterator classes
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {


		typedef Distance					difference_type;
		typedef T							value_type;
		typedef Pointer						pointer;
		typedef Reference					reference;
		typedef Category					iterator_category;
	};

	// */


	//*	difference allows us to quickly calculate the space between two iterators
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance( InputIterator first, InputIterator last ) {

		typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
		while (first != last) {

			first++;
			rtn++;
		}
		return rtn;
	}
	// */

	//*	Exceptions
	template <typename T>
	class	InvalidIteratorException : public std::exception {


		private:

			std::string _msg;


		public:

			InvalidIteratorException( void ) throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
			InvalidIteratorException( const InvalidIteratorException& ) throw() {}
			InvalidIteratorException& operator=( const InvalidIteratorException & ) throw() {}
			virtual ~InvalidIteratorException( void ) throw() {}
			virtual const char* what( void ) const throw() { return _msg.c_str(); }


	};
	// */


	//*	lexicographical compare

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2 ) {

		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) {
				return false;
			} else if (*first1 < *first2) {
				return true;
			}
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	// */




}