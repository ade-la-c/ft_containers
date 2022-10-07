#pragma once

#include <iostream>

namespace	ft {


	template <

		class T1,
		class T2

	> struct	pair {


		public:

			//*	definers

			typedef				T1	first_type;
			typedef				T2	second_type;

			//*	methods

			//	default constructor
			pair( void ) : _first(), _second() {}
			//	copy constructor
			template< class U, class V >
			pair( const pair<U,V> & pr ) { *this = pr; }
			//	assignation operator
			pair &	operator=( pair const & rhs ) {

				this->_first = rhs._first;
				this->_second = rhs._second;
				return *this;
			}
			//	initialization constructor
			pair( const first_type & a, const second_type & b ) : _first(a), _second(b) {}


		private:

			first_type		_first;
			second_type		_second;


	};

	template< class T1, class T2 >
	bool	operator==(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template< class T1, class T2 >
	bool	operator!=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return !(lhs == rhs); }

	template< class T1, class T2 >
	bool	operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template< class T1, class T2 >
	bool	operator<=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return !(rhs < lhs); }

	template< class T1, class T2 >
	bool	operator>(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return rhs < lhs; }

	template< class T1, class T2 >
	bool	operator>=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return !(lhs < rhs); }

}