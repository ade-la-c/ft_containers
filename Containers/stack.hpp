#pragma once

#include "../Containers/vector.hpp"

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
			value_type &			top() { return _container.back(); }
			const value_type &		top() const { return _container.back(); }
			void					push( const value_type & val ) { _container.push_back(val); }
			void					pop() { _container.pop_back(); }

			template< class Tn, class ContainerN >
			friend bool	operator==( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs.size() == rhs.size(); }

			template< class Tn, class ContainerN >
			friend bool	operator!=( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return !(lhs.size() == rhs.size()); }

			template< class Tn, class ContainerN >
			friend bool	operator<( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

			template< class Tn, class ContainerN >
			friend bool	operator<=( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs <= rhs; }

			template< class Tn, class ContainerN >
			friend bool	operator>( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs > rhs; }

			template< class Tn, class ContainerN >
			friend bool	operator>=( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs >= rhs; }


		protected:

			container_type	_container;


	};


}

void stack_testing( void );