#pragma once

#include "vector.hpp"

#include <iostream>
#include <deque>

namespace	ft {


	template <
	
		class T,
		class Container = ft::vector<T>

	> class stack {

		public:

			typedef 			T						value_type;
			typedef				Container				container_type;
			typedef				size_t					size_type;


			explicit stack( const container_type & ctnr = container_type() ) : _container(ctnr) {}

			bool					empty() const { return !(_container.size()); }
			size_type				size() const { return _container.size(); }
			value_type &			top() { return _container.getEnd() - 1; }
			const value_type &		top() const { return _container.getEnd() - 1; }
			void					push( const value_type & val ) { _container.push_back(val); }
			void					pop() { _container.pop_back(val); }

		private:

			template< class T, class Container >
			friend bool	operator==( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
			{ return lhs._size == rhs._size; }

			template< class T, class Container >
			friend bool	operator!=( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
			{ return !(lhs._size == rhs._size); }

			template< class T, class Container >
			friend bool	operator<( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
			{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

			template< class T, class Container >
			friend bool	operator<=( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
			{ return lhs <= rhs; }

			template< class T, class Container >
			friend bool	operator>( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
			{ return lhs > rhs; }

			template< class T, class Container >
			friend bool	operator>=( const stack<T,Container> & lhs, const stack<T,Container> & rhs )
			{ return lhs >= rhs; }


		protected:

			container_type	_container;


	};


}
