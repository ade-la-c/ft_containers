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


			explicit stack( const container_type & ctnr = container_type() ) : container(ctnr) {}

			bool					empty() const { return !(container.size()); }
			size_type				size() const { return container.size(); }
			value_type &			top() { return container.back(); }
			const value_type &		top() const { return container.back(); }
			void					push( const value_type & val ) { container.push_back(val); }
			void					pop() { container.pop_back(); }

			template< class Tn, class ContainerN >
			friend bool	operator==( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs.size() == rhs.size(); }

			template< class Tn, class ContainerN >
			friend bool	operator!=( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return !(lhs.size() == rhs.size()); }

			template< class Tn, class ContainerN >
			friend bool	operator<( const stack<Tn,ContainerN> & lhs, const stack<Tn,ContainerN> & rhs )
			{ return lhs.container < rhs.container; }

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

			container_type	container;


	};


}
// void stack_testing( void );
