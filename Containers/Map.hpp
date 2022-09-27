#pragma once

#include <iostream>
#include <limits>
#include <memory>
#include <iterator>				//! must be replaced by bidirectional_iterator
#include <functional>

#include "../utils/utils.hpp"
#include "../utils/reverse_iterator.hpp"

namespace   ft {


	template <

		class Key,																//*	key_type
		class T,																//*	mapped_type
		class Compare = std::less< std::pair< const Key, T> >,					//*	key_compare
		class Allocator = std::allocator< std::pair< const Key, T > >			//*	allocator_type

	> class map {


	public:


//	/*.
//	########  ######## ######## #### ##    ## ######## ########   ######
//	##     ## ##       ##        ##  ###   ## ##       ##     ## ##    ##
//	##     ## ##       ##        ##  ####  ## ##       ##     ## ##
//	##     ## ######   ######    ##  ## ## ## ######   ########   ######
//	##     ## ##       ##        ##  ##  #### ##       ##   ##         ##
//	##     ## ##       ##        ##  ##   ### ##       ##    ##  ##    ##
//	########  ######## ##       #### ##    ## ######## ##     ##  ######
//	*/

		typedef T																mapped_type;
		typedef Key																key_type;
		typedef Allocator														allocator_type;
		typedef Compare															key_compare;

		typedef typename std::pair<const Key, T>								value_type;		//TODO Replace with ft::pair
		typedef size_t															size_type;
		typedef typename std::ptrdiff_t											difference_type;
		typedef typename allocator_type::reference								reference;
		typedef typename allocator_type::const_reference						const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;

		class	value_compare : public std::binary_function<  > {

			public:

				typedef value_type	first_value;

				value_compare() {}

				operator() ();


			protected:



		};

		typedef ft::reverse_iterator< value_type >								reverse_iterator;		 //???????
		typedef ft::reverse_iterator< const value_type >						const_reverse_iterator; //???????
		typedef typename std::bidirectional_iterator< value_type >				iterator;
		typedef typename std::bidirectional_iterator< const value_type >		const_iterator;			//??????

		//	methods		//

		//*	empty
		explicit	map( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() ) : _size(0), _alloc(NULL) {


		}
		//*	range
		template <class InputIterator>
		map( InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() ) : _size(0), _alloc(alloc) {

			_size = ft::distance(first, last);

		}
		//*	copy
		map( const map & x );
		//*	assignation operator
		map &		operator=( const map & x );
		//*	destructor
		~map( void );

		// iterators

		iterator				begin( void );
		const_iterator			begin( void ) const;
		iterator				end( void );
		const_iterator			end( void ) const;
		reverse_iterator		rbegin( void );
		const_reverse_iterator	rbegin( void ) const;
		reverse_iterator		rend( void );
		const_reverse_iterator	rend( void ) const;

		// size

		bool			empty( void ) const { return !_size; }	//! allowed ?
		size_type		size( void ) const { return _size; }
		size_type		max_size( void ) const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

		// element access

		mapped_type &	operator[]( const key_type & k );

		// modifiers

		//*	single element
		pair<iterator, bool>	insert( const value_type & val );
		//*	fill
		iterator				insert( iterator position, value_type & val );
		//*	range
		template<class InputIterator>
		void					insert( InputIterator first, InputIterator last );
		void					erase( iterator position );
		size_type				erase( const key_compare & k );
		void					erase( iterator first, iterator last );
		void					swap( map & x );
		void					clear( void );

		// observers

		key_compare				key_comp( void ) const;
		value_compare			value_comp( void ) const;//TODO class to write

		// operations

		iterator				find( const key_type & k );
		const_iterator			find( const key_type &k ) const;

		size_type				count( const key_type & k ) const;

		iterator				lower_bond( const key_type & k );
		const_iterator			lower_bond( const key_type & k ) const;

		iterator				upper_bond( const key_type & k );
		const_iterator			upper_bond( const key_type & k ) const;

		pair<const_iterator, const_iterator>	equal_range( const key_type & k );
		pair<iterator, iterator>				equal_range( const key_type & k );

		// allocator

		allocator_type	get_allocator( void ) const { return _alloc; }



	private:

		size_type					_size;
		allocator_type				_alloc;


	}



}
