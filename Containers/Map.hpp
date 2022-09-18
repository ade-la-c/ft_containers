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

		typedef ft::reverse_iterator< value_type >						reverse_iterator;		 //???????
		typedef ft::reverse_iterator< const value_type >				const_reverse_iterator; //???????
		typedef typename std::bidirectional_iterator< value_type >				bidirectional_iterator;
		typedef typename std::bidirectional_iterator< const value_type >		const_bidirectional_iterator;

		map( void ) {}
		explicit	map(const key_compare & comp = key_compare())


	private:




	}



}
