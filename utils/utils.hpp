#pragma once


#include <iostream>
#include <cstddef>
#include <limits>
#include <sstream>
#include <typeinfo>



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
	class iterator {

		public:

			typedef Distance					difference_type;
			typedef T							value_type;
			typedef Pointer						pointer;
			typedef Reference					reference;
			typedef Category					iterator_category;
	};

	template<class T>
	class	bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {

			typedef typename bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		private:

			pointer		_content;

	};

	// */

	//*	iterator_traits class defines properties of iterators
	template<class Iterator>
	struct	iterator_traits {

		//*	Type to express the result of subtracting one iterator from another.
		typedef typename Iterator::difference_type		difference_type;

		//*	The type of the element the iterator can point to.
		typedef typename Iterator::value_type			value_type;

		//*	The type of a pointer to an element the iterator can point to.
		typedef typename Iterator::pointer				pointer;

		//* The type of a reference to an element the iterator can point to.
		typedef typename Iterator::reference			reference;

		//*	The Iterator category
		typedef typename Iterator::iterator_category	iterator_category;

	};

	template<class T>
	struct	iterator_traits<T*> {

		typedef ptrdiff_t								difference_type;

		typedef T										value_type;

		typedef T*										pointer;

		typedef T&										reference;

		typedef ft::random_access_iterator_tag			iterator_category;
	};

	template<class T>
	struct	iterator_traits<const T*> {

		typedef ptrdiff_t								difference_type;

		typedef T										value_type;

		typedef const T*								pointer;

		typedef const T&								reference;

		typedef ft::random_access_iterator_tag			iterator_category;
	};
	// */



	//*	difference allows us to quickly calculate the space between two iterators
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
		distance (InputIterator first, InputIterator last) {

			typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
			while (first != last)
			{
				first++;
				rtn++;
			}
			return (rtn);
		}
	// */

	//*	Exceptions
    template <typename T>
    class InvalidIteratorException : public std::exception
    {
        private:
            std::string _msg;
        
        public :
            InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
            InvalidIteratorException (const InvalidIteratorException&) throw() {}
            InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
            virtual ~InvalidIteratorException() throw() {}
            virtual const char* what() const throw() { return (_msg.c_str()); }
    };
	// */



}