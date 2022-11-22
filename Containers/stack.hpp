#pragma once

#include "../Containers/vector.hpp"

#include <iostream>
// #include <deque>
// #include <list>

namespace	ft {


	template <
	
		class T,
		// class Container = std::deque< T >	//* uncomment to test stack compatibility 
		// class Container = std::list< T >		//* uncomment to test stack compatibility 
		class Container = ft::vector< T >

	> class stack {

		public:

			typedef 			T						value_type;
			typedef				Container				container_type;
			typedef				size_t					size_type;


			explicit stack( const container_type & ctnr = container_type() ) : c(ctnr) {}

			bool					empty() const { return !(c.size()); }
			size_type				size() const { return c.size(); }
			value_type &			top() { return c.back(); }
			const value_type &		top() const { return c.back(); }
			void					push( const value_type & val ) { c.push_back(val); }
			void					pop() { c.pop_back(); }

			template< class Tn, class ContainerN >
			friend bool	operator==( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs.c == rhs.c; }

			template< class Tn, class ContainerN >
			friend bool	operator!=( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return !(lhs == rhs); }

			template< class Tn, class ContainerN >
			friend bool	operator<( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs.c < rhs.c; }

			template< class Tn, class ContainerN >
			friend bool	operator<=( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs.c <= rhs.c; }

			template< class Tn, class ContainerN >
			friend bool	operator>( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs.c <= rhs.c; }

			template< class Tn, class ContainerN >
			friend bool	operator>=( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return !(lhs < rhs); }


		protected:

			container_type	c;


	};


}
