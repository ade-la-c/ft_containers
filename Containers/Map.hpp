#pragma once

#include <iostream>
#include <limits>
#include <memory>
#include <iterator>				//! must be replaced by bidirectional_iterator

#include "../utils/utils.hpp"
#include "../utils/reverse_iterator.hpp"

namespace   ft {


	template <

		class Key,																//
		class T,																
		class Compare = std::less,												
		class Allocator = std::allocator< std::pair< const Key, T > >			

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

		typedef ft::reverse_iterator< value_type >								reverse_iterator;		 //???????
		typedef ft::reverse_iterator< const value_type >						const_reverse_iterator; //???????
		typedef typename std::bidirectional_iterator< value_type >				iterator;
		typedef typename std::bidirectional_iterator< const value_type >		const_iterator;

		//	methods		//

		//*	empty
		explicit	map( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() );
		//*	range
		template <class InputIterator>
		map( InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() );
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
		iterator				insert( iterator position, value_type & val );
		template<class InputIterator>
		void					insert( InputIterator first, InputIterator last );



	private:

		size_type		_size;


	}



}
