#pragma once

#include <iostream>
#include <limits>
#include <memory>
#include <iterator>				//! must be replaced by bidirectional_iterator
#include <functional>

#include "../utils/utils.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/rbt.hpp"
#include "../utils/pair.hpp"

namespace   ft {


	template <

		class Key,																//*	key_type
		class T,																//*	mapped_type
		class Compare = std::less< ft::pair< const Key, T> >,					//*	key_compare
		class Allocator = std::allocator< ft::pair< const Key, T > >			//*	allocator_type

	> class map {


//	/*.
//	########  ######## ######## #### ##    ## ######## ########   ######
//	##     ## ##       ##        ##  ###   ## ##       ##     ## ##    ##
//	##     ## ##       ##        ##  ####  ## ##       ##     ## ##
//	##     ## ######   ######    ##  ## ## ## ######   ########   ######
//	##     ## ##       ##        ##  ##  #### ##       ##   ##         ##
//	##     ## ##       ##        ##  ##   ### ##       ##    ##  ##    ##
//	########  ######## ##       #### ##    ## ######## ##     ##  ######
//	*/

	private:

		typedef 			ft::RBtree< key_type, mapped_type >						Tree;
		typedef typename	Allocator::template rebind<Tree>::other					tree_allocator;


	public:

		typedef				T														mapped_type;		//*	DEFINITION
		typedef				Key														key_type;			//*	KEY
		typedef				Allocator												allocator_type;
		typedef				Compare													key_compare;

		typedef typename	ft::pair<const Key, T>									value_type;		//TODO Replace with ft::pair
		typedef				size_t													size_type;
		typedef typename	std::ptrdiff_t											difference_type;
		typedef typename	allocator_type::reference								reference;
		typedef typename	allocator_type::const_reference							const_reference;
		typedef typename	allocator_type::pointer									pointer;
		typedef typename	allocator_type::const_pointer							const_pointer;

		typedef				ft::reverse_iterator< value_type >						reverse_iterator;		   //???????
		typedef				ft::reverse_iterator< const value_type >				const_reverse_iterator;	  //???????
		typedef typename	std::bidirectional_iterator< value_type >				iterator;				 //???????
		typedef typename	std::bidirectional_iterator< const value_type >			const_iterator;			//???????


//*	.##....##.########..######..########.########.########......######..##..........###.....######...######.
//*	.###...##.##.......##....##....##....##.......##.....##....##....##.##.........##.##...##....##.##....##
//*	.####..##.##.......##..........##....##.......##.....##....##.......##........##...##..##.......##......
//*	.##.##.##.######....######.....##....######...##.....##....##.......##.......##.....##..######...######.
//*	.##..####.##.............##....##....##.......##.....##....##.......##.......#########.......##.......##
//*	.##...###.##.......##....##....##....##.......##.....##....##....##.##.......##.....##.##....##.##....##
//*	.##....##.########..######.....##....########.########......######..########.##.....##..######...######.

		class	value_compare : public std::binary_function< value_type, key_type, bool > {
			friend class	map< class key_type, class mapped_type, class key_compare, class allocator_type >;

			public:

				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				typedef bool		result_type;

				bool	operator() ( const value_type & x, const value_type & y ) const { return comp(x.first, y.first); }

			protected:

				Compare				comp;

				value_compare( Compare c ) : comp(c) {}

		};

//*	.##.....##.########.########.##.....##..#######..########...######.
//*	.###...###.##..........##....##.....##.##.....##.##.....##.##....##
//*	.####.####.##..........##....##.....##.##.....##.##.....##.##......
//*	.##.###.##.######......##....#########.##.....##.##.....##..######.
//*	.##.....##.##..........##....##.....##.##.....##.##.....##.......##
//*	.##.....##.##..........##....##.....##.##.....##.##.....##.##....##
//*	.##.....##.########....##....##.....##..#######..########...######.

		//*	empty
		explicit	map( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() )
		: _size(0), _alloc(alloc), _treeAlloc(alloc) {

			this->_rbt = _treeAlloc.allocate(1);
		}
		//*	range
		template <class InputIterator>
		map( InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() )
		: _size(0), _alloc(alloc), _treeAlloc(alloc) {		//todo add kv_compare

			this->insert(first, last);
		}
		//*	copy
		map( const map & x ) { *this = x; }
		//*	assignation operator
		map &		operator=( const map & rhs ) {

			if (*this == rhs) {

				this->_size = rhs._size;
				this->_alloc = rhs._alloc;
				this->_treeAlloc = rhs._treeAlloc;

				this->_treeAlloc.destroy(this->_rbt);
				this->_treeAlloc.allocate(this->rbt, 1);
				this->insert(rhs.begin(), rhs.end());
			}
			return *this;
		}
		//*	destructor
		~map( void ) {

			this->_treeAlloc.destroy(tree);
			this->_treeAlloc.deallocate(tree, 1);
		}

		// iterators

		iterator				begin( void ) { return _rbt.begin(); }
		const_iterator			begin( void ) const { return _rbt.begin() }
		iterator				end( void ) { return _rbt.end(); }
		const_iterator			end( void ) const { return _rbt.end(); }
		reverse_iterator		rbegin( void ) { return _rbt.rbegin(); }
		const_reverse_iterator	rbegin( void ) const { return _rbt.rbegin(); }
		reverse_iterator		rend( void ) { return _rbt.rend(); }
		const_reverse_iterator	rend( void ) const { return _rbt.rend(); }

		// size

		bool			empty( void ) const { return !_size; }	//! allowed ?
		size_type		size( void ) const { return _size; }
		size_type		max_size( void ) const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

		// element access

		mapped_type &	operator[]( const key_type & k ) {

			
		}

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
		value_compare			value_comp( void ) const;

		// operations

		iterator				find( const key_type & k );
		const_iterator			find( const key_type &k ) const;

		size_type				count( const key_type & k ) const;

		iterator				lower_bound( const key_type & k );
		const_iterator			lower_bound( const key_type & k ) const;

		iterator				upper_bound( const key_type & k );
		const_iterator			upper_bound( const key_type & k ) const;

		pair<const_iterator, const_iterator>	equal_range( const key_type & k );
		pair<iterator, iterator>				equal_range( const key_type & k );

		// allocator

		allocator_type	get_allocator( void ) const { return _alloc; }



	private:


		size_type					_size;
		allocator_type				_alloc;
		tree_allocator				_treeAlloc;
		Tree *						_rbt;


	};



}
