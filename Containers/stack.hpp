#pragma once

#include <iostream>

namespace	ft {


	template <
	
		class T,
		class Container = deque<T>

	> class stack {

		public:

			typedef 			T						value_type;
			typedef				Container				container_type;
			typedef				size_t					size_type;


			explicit stack( const cotainer_type & ctnr = container_type() ) : _container(ctnr), _size(0) {}

			bool					empty() const { return !_size; }
			size_type				size() const { return _size; }
			value_type &			top();
			const value_type &		top() const;
			void					push( const value_type & val );
			void					pop();



		private:

			container_type	_container;
			size_type		_size;


	};


	template< class T, class Container >
	bool	operator==( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
	{ return lhs._size == rhs._size; }

	template< class T, class Container >
	bool	operator!=( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
	{ return !(lhs._size == rhs._size); }

	template< class T, class Container >
	bool	operator<( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
	{ return lhs < rhs; }

	template< class T, class Container >
	bool	operator<=( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
	{ return lhs <= rhs; }

	template< class T, class Container >
	bool	operator>( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
	{ return lhs > rhs; }

	template< class T, class Container >
	bool	operator>=( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
	{ return lhs >= rhs; }


}